<script lang="ts">
  import { isLoading, socket, state } from "../stores.js";
  import Section from "./Section.svelte";
  let isUpdating: boolean | undefined;

  isLoading.subscribe((value) => (isUpdating = value && isUpdating));

  const triggerShutter = () => {
    $socket.send(JSON.stringify({ command: "triggerShutter" }));
    isUpdating = $isLoading = true;
  };

  const pressShutter = () => {
    $socket.send(JSON.stringify({ command: "pressShutter" }));
    isUpdating = $isLoading = true;
  };

  const releaseShutter = () => {
    $socket.send(JSON.stringify({ command: "releaseShutter" }));
    isUpdating = $isLoading = true;
  };

  const triggerIR = () => {
    $socket.send(JSON.stringify({ command: "triggerIR" }));
    isUpdating = $isLoading = true;
  };
</script>

<Section name="shutter">
  <h2 slot="heading">Shutter</h2>

  <button class="inverse" on:click={triggerShutter}> Trigger shutter </button>
  {#if $state.shutterIsPressed}
    <button class="inverse" on:click={releaseShutter}> Release shutter </button>
  {:else}
    <button class="inverse" on:click={pressShutter}> Press shutter </button>
  {/if}
  <button class="inverse" on:click={triggerIR}> Trigger IR release </button>

  {#if isUpdating}
    <p>Loading...</p>
  {:else if $state.shutterIsPressed}
    <p>Shutter is pressed...</p>
  {:else}
    <p>Shutter is not pressed.</p>
  {/if}
</Section>
