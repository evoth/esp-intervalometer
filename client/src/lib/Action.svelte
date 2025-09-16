<script lang="ts">
  import SelectDropdown from "../util/SelectDropdown.svelte";
  import { ACTIONS_DEF, type Action } from "./actions";

  export let action: Action;
  export let index;
  export let deleteAction;

  const actionSpec = ACTIONS_DEF[action.action];
</script>

<div class="container">
  <div class="heading">
    <h3>{index + 1}. {action.action}</h3>
    <button class="delete-container" on:click={deleteAction}>
      <svg
        xmlns="http://www.w3.org/2000/svg"
        width="24"
        height="24"
        viewBox="0 0 24 24"
        fill="none"
        stroke="currentColor"
        stroke-width="2"
        stroke-linecap="round"
        stroke-linejoin="round"
        ><line x1="18" y1="6" x2="6" y2="18"></line><line
          x1="6"
          y1="6"
          x2="18"
          y2="18"
        ></line></svg
      >
    </button>
  </div>
  <label>
    Time:
    <input
      type="number"
      step="any"
      min="0"
      bind:value={action.time}
      placeholder="Time offset in seconds"
    />
    seconds
  </label>
  <div>
    <SelectDropdown
      label={"Offset"}
      buttonTitle={"Choose time offset mode"}
      bind:value={action.timeMode}
      options={["from start", "after previous"]}
    />
  </div>
  {#each Object.keys(action.fields) as fieldKey}
    <div>
      <SelectDropdown
        label={fieldKey}
        buttonTitle={"Choose value for" + fieldKey}
        bind:value={action.fields[fieldKey]}
        options={actionSpec.fields[fieldKey].options}
      />
    </div>
  {/each}
</div>

<style>
  .heading {
    all: unset;
    display: flex;
    flex-direction: row;
    justify-content: space-between;
    align-items: center;
  }

  .container {
    display: flex;
    flex-direction: column;
    gap: 12px;
    background-color: var(--gray-90);
    padding: 10px 16px;
    border-radius: 8px;
    transition: background-color 0.2s;
  }

  .delete-container {
    padding: 4px 4px;
    display: flex;
    align-items: center;
  }

  label {
    padding: 0px;
  }
</style>
