<script>
  import { state, isLoading, socket } from "../stores.js";
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

<div class="section">
  <h2>Intervalometer</h2>
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
  {:else if $state.statusCode != 200}
    <p class="error">{`${$state.statusCode} error, ${$state.statusMsg}`}</p>
  {:else}
    <p class="success">
      {`Number of shots: ${$state.numShots}\nStatus code: ${$state.statusCode}\nStatus message: ${$state.statusMsg}`}
    </p>
  {/if}
</div>
