<script lang="ts">
  import { actions } from "../stores";
  import SelectDropdown from "../util/SelectDropdown.svelte";
  import Action from "./Action.svelte";
  import { ACTIONS_DEF } from "./actions";
  import Section from "./Section.svelte";

  let newActionType = "Trigger shutter";

  const newAction = () => {
    $actions.push({
      action: newActionType,
      // @ts-ignore
      fields: Object.fromEntries(
        Object.entries(ACTIONS_DEF[newActionType].fields).map(
          ([key, field]) => {
            return [key, ACTIONS_DEF[newActionType].body[field.key]];
          }
        )
      ),
      time: 0,
      timeMode: "after previous",
    });
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
