<script lang="ts">
  import { state } from "../stores.js";
  import Section from "./Section.svelte";

  let timeReceived = Date.now();
  let timeUntilNext = 0;
  let timeNow = Date.now();
  let interval: number | undefined;
  state.subscribe((value) => {
    timeReceived = Date.now();
    clearInterval(interval);
    if (value.isRunning) {
      interval = setInterval(() => {
        timeNow = Date.now();
        timeUntilNext =
          ($state.timeUntilNext - (Date.now() - timeReceived)) / 1000;
      }, 100);
    } else {
      timeUntilNext = 0;
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
    Next action index: {$state.actionIndex == -1
      ? 1
      : $state.actionIndex + 1}/{$state.actions.length}
    Time until next action: {timeUntilNext.toFixed(1)}
  </p>
  {#each $state.loops as loop}
    <p>
      <strong>Loop {loop.startIndex}</strong>
      Time in loop: {((timeNow - loop.startTime) / 1000).toFixed(
        1
      )}{#if loop.duration > 0}/{loop.duration}{/if}
      Time in cycle: {((timeNow - loop.startTime) / 1000).toFixed(1)}
      Number of cycles: {loop.completedReps}{#if loop.repetitions > 0}/{loop.repetitions}{/if}
    </p>
  {/each}
</Section>
