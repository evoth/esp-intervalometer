<script>
  import { state, isLoading, socket } from "../stores.js";
  import Section from "./Section.svelte";
  let intervalSec, isUpdating, bulbSec, duration;

  state.subscribe((value) => {
    intervalSec = value.intervalSec || intervalSec;
    bulbSec = value.bulbSec || bulbSec;
    duration = value.duration || duration;
  });
  isLoading.subscribe((value) => (isUpdating = value && isUpdating));

  const start = () => {
    $socket.send(JSON.stringify({ command: "start", intervalSec, bulbSec, duration }));
    isUpdating = $isLoading = true;
  };

  const stop = () => {
    $socket.send(JSON.stringify({ command: "stop" }));
    isUpdating = $isLoading = true;
  };

  const toggleBulb = () => {
    if ($state.bulbMode) {
      $socket.send(JSON.stringify({ command: "disableBulb" }));
    } else {
      $socket.send(JSON.stringify({ command: "enableBulb" }));
    }
    isUpdating = $isLoading = true;
  };
</script>

<Section name="intervalometer">
  <h2 slot="heading">Intervalometer</h2>
  <label>
    Interval:
    <input
      type="number"
      step="any"
      min="1"
      bind:value={intervalSec}
      placeholder="Interval in seconds"
    />
    seconds
  </label>

  <button on:click={toggleBulb}>
    {$state.bulbMode ? "Disable bulb mode" : "Enable bulb mode"}
  </button>
  {#if $state.bulbMode}
    <label>
      Bulb:
      <input
        type="number"
        step="any"
        min="1"
        bind:value={bulbSec}
        placeholder="Exposure time in seconds"
      />
      seconds
    </label>
  {/if}
  <label>
    Duration:
    <input
      type="number"
      step="any"
      min="0"
      bind:value={duration}
      placeholder="Duration in seconds"
    />
    seconds
  </label>
  {#if $state.isRunning}
    <button on:click={stop}> Stop </button>
  {:else}
    <!-- TODO: Add some basic validation -->
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
