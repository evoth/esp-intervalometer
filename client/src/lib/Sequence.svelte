<script lang="ts">
  import { actions } from "../stores";
  import SelectDropdown from "../util/SelectDropdown.svelte";
  import Action from "./Action.svelte";
  import { ACTIONS_DEF, type Action as ActionType } from "./actions";
  import Section from "./Section.svelte";

  let newActionType = "Trigger shutter";

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
  <button class="inverse" on:click={newAction}> Add action </button>
</Section>
