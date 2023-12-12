<script>
  import ThemeToggle from "./lib/ThemeToggle.svelte";
  import Connect from "./lib/Connect.svelte";
  import Intervalometer from "./lib/Intervalometer.svelte";
  import { isConnected } from "./stores.js";
</script>

<main>
  <div
    style="display: flex; flex-direction: row; justify-content: space-between; column-gap: 8px"
  >
    <h1>ESP8266 Intervalometer</h1>
    <ThemeToggle />
  </div>
  <Connect />
  {#if $isConnected}
    <Intervalometer />
  {/if}
</main>
