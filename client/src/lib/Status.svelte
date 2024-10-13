<script>
  import { state } from "../stores.js";
  import Section from "./Section.svelte";

  let timeReceived;
  let timeUntilNext = 0;
  let timeUntilRelease = 0;
  let timeUntilCompletion = 0;
  let interval;
  state.subscribe((value) => {
    timeReceived = Date.now();
    clearInterval(interval);
    if (value.isRunning) {
      interval = setInterval(() => {
        timeUntilNext =
          ($state.timeUntilNext - (Date.now() - timeReceived)) / 1000;
        timeUntilRelease =
          ($state.timeUntilRelease - (Date.now() - timeReceived)) / 1000;
        timeUntilCompletion =
          ($state.timeUntilCompletion - (Date.now() - timeReceived)) / 1000;
      }, 100);
    } else {
      timeUntilNext = 0;
      timeUntilRelease = 0;
      timeUntilCompletion = 0;
    }
  });
</script>

<Section name="status">
  <h2 slot="heading">Status</h2>
  <p
    class:success={$state.statusCode == 200}
    class:warning={$state.statusCode == 0}
    class:error={$state.statusCode != 200 && $state.statusCode != 0}
  >
    Status code: {$state.statusCode}
    Status message: {$state.statusMsg}
  </p>
  {#if $state.cameraConnected}
    <p>
      Number of shots: {$state.numShots}
      Time until next shot: {timeUntilNext.toFixed(1)}
      Time until shutter release: {timeUntilRelease.toFixed(1)}
      {#if timeUntilCompletion > 0}
        Time until completion: {timeUntilCompletion.toFixed(1)}
      {/if}
    </p>
  {/if}
</Section>
