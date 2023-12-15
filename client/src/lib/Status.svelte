<script>
  import { state, isLoading, isConnected } from "../stores.js";
  import Section from "./Section.svelte";

  const statusString = () =>
    `Status code: ${$state.statusCode}\nStatus message: ${$state.statusMsg}`;

  let timeReceived = Date.now();
  let timeUntilNext = "0";
  let interval;
  state.subscribe((value) => {
    timeReceived = Date.now();
    clearInterval(interval);
    if (value.isRunning) {
      interval = setInterval(() => {
        timeUntilNext = (
          ($state.timeUntilNext - (Date.now() - timeReceived)) /
          1000
        ).toFixed(1);
      }, 100);
    } else {
      timeUntilNext = "0";
    }
  });
</script>

<Section name="status">
  <h2 slot="heading">Status</h2>
  {#if $state.statusCode == 200}
    <p class="success">{statusString()}</p>
  {:else if $state.statusCode == 0}
    <p class="warning">{statusString()}</p>
  {:else}
    <p class="error">{statusString()}</p>
  {/if}
  {#if $state.cameraConnected}
    <p>
      Number of shots: {$state.numShots}
      Time until next shot: {timeUntilNext}
    </p>
  {/if}
</Section>
