<script lang="ts">
  import {
    actions,
    espIP,
    isConnected,
    isLoading,
    socket,
    state,
  } from "../stores.js";
  import Section from "./Section.svelte";
  let espIPInput = $espIP;
  let isConnecting: boolean | undefined;

  let numUpdates = 0;

  const connect = () => {
    $espIP = espIPInput;
    $socket?.close();
    $socket = new WebSocket(`ws://${$espIP}:81`);
    $socket.addEventListener("message", (event) => {
      numUpdates++;
      $state = JSON.parse(event.data);
      if (numUpdates == 1) $actions = $state.actions;
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
