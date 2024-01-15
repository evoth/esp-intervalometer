<script>
  import { state, socket, isLoading } from "../stores.js";
  import Section from "./Section.svelte";
  let cameraIP, isConnecting;

  state.subscribe((value) => (cameraIP = value.cameraIP || cameraIP));
  isLoading.subscribe((value) => (isConnecting = value && isConnecting));

  const connect = () => {
    $socket.send(JSON.stringify({ command: "connect", cameraIP }));
    isConnecting = $isLoading = true;
  };
</script>

<Section name="connect-camera">
  <h2 slot="heading">Connect camera</h2>
  <input bind:value={cameraIP} placeholder="Camera IP address" />
  <button on:click={connect}> Connect </button>
  {#if isConnecting}
    <p>Connecting...</p>
  {:else if $state.cameraConnected}
    <p class="success">Connected to {$state.cameraIP}</p>
  {:else}
    <p class="error">Disconnected</p>
  {/if}
</Section>
