<script>
  import { state, isLoading, socket } from "../stores.js";
  import Section from "./Section.svelte";
  let intervalSec, isUpdating;

  state.subscribe((value) => (intervalSec = value.intervalSec || intervalSec));
  isLoading.subscribe((value) => (isUpdating = value && isUpdating));

  const start = () => {
    $socket.send(
      JSON.stringify({ command: "start", body: { intervalSec: intervalSec } })
    );
    isUpdating = $isLoading = true;
  };

  const stop = () => {
    $socket.send(JSON.stringify({ command: "stop", body: {} }));
    isUpdating = $isLoading = true;
  };
</script>

<Section name="intervalometer">
  <h2 slot="heading">Intervalometer</h2>
  <input
    type="number"
    bind:value={intervalSec}
    placeholder="Interval in seconds"
  />
  {#if $state.isRunning}
    <button on:click={stop}> Stop </button>
  {:else}
    <button on:click={start}> Start </button>
  {/if}

  {#if isUpdating}
    <p>Loading...</p>
  {:else if $state.isRunning}
    <p>Intervalometer running...</p>
  {:else}
    <p>Intervalometer stopped.</p>
  {/if}
</Section>
