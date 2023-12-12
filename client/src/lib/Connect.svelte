<script>
  import { cameraIP, isConnected, espIP } from "../stores.js";
  let cameraIPInput = $cameraIP;
  let error = "";
  let isLoading = false;
  const connect = async () => {
    $cameraIP = cameraIPInput;
    isLoading = true;
    try {
      const response = await fetch(`${$espIP}/connect`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({
          cameraIP: $cameraIP,
        }),
      });
      if (response.ok) {
        $isConnected = true;
      } else {
        error = `${response.status} error, ${await response.text()}`;
        $isConnected = false;
      }
    } catch {
      error = `No response from ESP`;
      $isConnected = false;
    }
    isLoading = false;
  };
</script>

<div class="section">
  <h2>Connect camera</h2>
  <input bind:value={cameraIPInput} placeholder="Camera IP address" />
  <button on:click={connect}> Connect </button>
  {#if isLoading}
    <p>Connecting...</p>
  {:else if $isConnected}
    <p class="success">Connected to {$cameraIP}</p>
  {:else if error != ""}
    <p class="warning">Disconnected ({error})</p>
  {:else}
    <p class="warning">Disconnected</p>
  {/if}
</div>
