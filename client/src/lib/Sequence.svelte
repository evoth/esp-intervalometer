<script lang="ts">
  import { actions } from "../stores";
  import SelectDropdown from "../util/SelectDropdown.svelte";
  import Action from "./Action.svelte";
  import { ACTIONS_DEF, type Action as ActionType } from "./actions";
  import Section from "./Section.svelte";

  let newActionType = "Trigger shutter";
  let fileInput: HTMLInputElement;

  function exportJson(): void {
    const blob = new Blob([JSON.stringify($actions, null, 2)], {
      type: "application/json",
    });
    const url = URL.createObjectURL(blob);
    const a = document.createElement("a");
    a.href = url;
    const timestamp = new Date().toISOString().replace(/[:.]/g, "-");
    a.download = `sequence-${timestamp}.json`;
    document.body.appendChild(a);
    a.click();
    a.remove();
    URL.revokeObjectURL(url);
  }

  function triggerImport(): void {
    fileInput.click();
  }

  function handleFile(e: Event): void {
    const input = e.target as HTMLInputElement;
    const file = input.files?.[0];
    if (!file) return;

    const reader = new FileReader();
    reader.onload = () => {
      const parsed = JSON.parse(reader.result as string);
      $actions = parsed;
    };
    reader.readAsText(file);
    input.value = "";
  }

  const newAction = () => {
    const newActionDef = ACTIONS_DEF[newActionType];
    $actions.push({
      action: newActionType,
      fields: Object.fromEntries(
        Object.entries(newActionDef.fields).map(([key, field]) => {
          return [key, newActionDef.body[field.key]];
        })
      ),
      time: 0,
      timeMode: "after previous",
    });
    $actions = $actions;
  };

  const moveAction = (action: ActionType, offset: number) => {
    const index = $actions.findIndex((a) => a === action);
    const newIndex = index + offset;
    if (newIndex < 0 || newIndex >= $actions.length) return;
    const [moveAction] = $actions.splice(index, 1);
    $actions.splice(newIndex, 0, moveAction);
    $actions = $actions;
  };
</script>

<Section name="sequence">
  <h2 slot="heading">Sequence</h2>
  {#each $actions as action, index (action)}
    <Action
      {action}
      {index}
      deleteAction={() => {
        $actions = $actions.filter((x) => x !== action);
      }}
      {moveAction}
    />
  {/each}

  <SelectDropdown
    label="New action"
    buttonTitle={"Choose new action type"}
    bind:value={newActionType}
    options={Object.keys(ACTIONS_DEF)}
  />
  <button class="inverse" on:click={newAction}>Add action</button>
  <button class="inverse" on:click={triggerImport}>Import JSON</button>
  <button class="inverse" on:click={exportJson}>Export JSON</button>
  <input
    type="file"
    bind:this={fileInput}
    accept="application/json,application/geo+json,text/json"
    on:change={handleFile}
    style="display:none"
  />
</Section>
