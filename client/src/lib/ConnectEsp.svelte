<script>
  import { state, socket, isLoading, espIP, isConnected } from "../stores.js";
  let espIPInput = $espIP, isConnecting;
  
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

  connect();
</script>
  
<div class="section">
  <h2>Connect to ESP8266</h2>
  <input bind:value={espIPInput} placeholder="ESP8266 IP address" />
  <button on:click={connect}> Connect </button>
  {#if isConnecting}
    <p>Connecting...</p>
  {:else if $isConnected}
    <p class="success">Connected to {$espIP}</p>
  {:else}
    <p class="warning">Disconnected</p>
  {/if}
</div>
  