<script>
  import { espIP, isConnected, isLoading, socket, state } from "../stores.js";
  import Section from "./Section.svelte";
  let espIPInput = $espIP,
    isConnecting;

  const connect = () => {
    $espIP = espIPInput;
    $socket?.close();
    $socket = new WebSocket(`ws://${$espIP}:81`);
    $socket.addEventListener("message", (event) => {
      $state = JSON.parse(event.data);
      $isLoading = false;
    });
    $socket.addEventListener("open", (event) => {
      $isConnected = true;
      isConnecting = false;
    });
    $socket.addEventListener("close", (event) => {
      $isConnected = false;
      isConnecting = false;
    });
    isConnecting = true;
  };

  const disconnect = () => {
    $socket?.close();
  };

  connect();
</script>

<Section name="connect-esp">
  <h2 slot="heading">Connect to ESP8266</h2>
  <label>
    <span>IP address:</span>
    <input bind:value={espIPInput} placeholder="ESP8266 IP address" />
  </label>
  {#if !$isConnected || espIPInput != $espIP}
    <button class="inverse" on:click={connect}> Connect </button>
  {:else}
    <button class="inverse" on:click={disconnect}> Disconnect </button>
  {/if}
  {#if isConnecting}
    <p>Connecting...</p>
  {:else if $isConnected}
    <p class="success">Connected to {$espIP}</p>
  {:else}
    <p class="error">Disconnected</p>
  {/if}
</Section>
