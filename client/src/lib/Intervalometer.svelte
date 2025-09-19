<script lang="ts">
  import { actions, isLoading, socket, state } from "../stores.js";
  import { ACTIONS_DEF } from "./actions.js";
  import Section from "./Section.svelte";
  let isUpdating: boolean | undefined;

  isLoading.subscribe((value) => (isUpdating = value && isUpdating));

  const start = () => {
    const sequence = [];
    for (const action of $actions) {
      const actionDef = ACTIONS_DEF[action.action];
      const body = JSON.parse(JSON.stringify(actionDef.body));
      for (const fieldName in action.fields) {
        body[actionDef.fields[fieldName].key] = action.fields[fieldName];
      }
      sequence.push({
        actionName: action.action,
        actionType: actionDef.actionType,
        time: action.time,
        timeMode: action.timeMode,
        body,
        ...actionDef.staticFields,
      });
    }

    $socket.send(
      JSON.stringify({
        command: "start",
        sequence,
        actions: $actions,
      })
    );
    isUpdating = $isLoading = true;
  };

  const stop = () => {
    $socket.send(JSON.stringify({ command: "stop" }));
    isUpdating = $isLoading = true;
  };
</script>

<Section name="intervalometer">
  <h2 slot="heading">Intervalometer</h2>
  {#if $state.isStopping}
    <button class="inverse" on:click={stop}> Stop immediately </button>
  {:else if $state.isRunning}
    <button class="inverse" on:click={stop}> Stop </button>
  {:else}
    <!-- TODO: Add some basic validation -->
    <button class="inverse" on:click={start}> Start </button>
  {/if}

  {#if isUpdating}
    <p>Loading...</p>
  {:else if $state.isStopping}
    <p>Intervalometer stopping after last action...</p>
  {:else if $state.isRunning}
    <p>Intervalometer running...</p>
  {:else}
    <p>Intervalometer stopped.</p>
  {/if}
</Section>
