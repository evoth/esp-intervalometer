<script lang="ts">
  import { state } from "../stores.js";
  import Section from "./Section.svelte";

  let timeReceived = Date.now();
  let timeUntilNext = 0;
  let timeUntilCompletion = 0;
  let interval: number | undefined;
  state.subscribe((value) => {
    timeReceived = Date.now();
    clearInterval(interval);
    if (value.isRunning) {
      interval = setInterval(() => {
        timeUntilNext =
          ($state.timeUntilNext - (Date.now() - timeReceived)) / 1000;
        timeUntilCompletion =
          ($state.timeUntilCompletion - (Date.now() - timeReceived)) / 1000;
      }, 100);
    } else {
      timeUntilNext = 0;
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
  <p>
    Completed repetitions: {$state.numShots}{#if $state.repetitions > 0}/{$state.repetitions}{/if}
    Next action index: {$state.actionIndex == -1
      ? 1
      : $state.actionIndex + 1}/{$state.actions.length}
    Time until next action: {timeUntilNext.toFixed(1)}
    {#if timeUntilCompletion > 0}
      <br />Time until completion: {timeUntilCompletion.toFixed(1)}
    {/if}
  </p>
</Section>
