<script>
  import ThemeToggle from "./lib/ThemeToggle.svelte";
  import ConnectCamera from "./lib/ConnectCamera.svelte";
  import ConnectEsp from "./lib/ConnectEsp.svelte";
  import Intervalometer from "./lib/Intervalometer.svelte";
  import Status from "./lib/Status.svelte";
  import { state, isConnected } from "./stores.js";
</script>

<main>
  <div>
    <h1>ESP8266 Intervalometer</h1>
    <ThemeToggle />
  </div>
  <Status />
  <ConnectEsp />
  {#if $isConnected}
    <ConnectCamera />
    {#if $state.cameraConnected}
      <Intervalometer />
    {/if}
  {/if}
</main>

<style>
  div {
    display: flex;
    flex-direction: row;
    justify-content: space-between;
    column-gap: 8px;
  }

  main {
    display: flex;
    flex-direction: column;
    row-gap: 32px;
  }
</style>
