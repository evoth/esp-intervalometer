<script>
  import { espIP } from "../stores.js";
  let intervalSec = 35;
  let status = "";
  let isError = false;
  let isRunning = false;
  let isLoading = false;
  const start = async () => {
    isLoading = true;
    try {
      const response = await fetch(`${$espIP}/start`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({
          intervalSec: intervalSec,
        }),
      });
      if (response.ok) {
        status = await response.text();
        isRunning = true;
        isError = false;
      } else {
        status = `${response.status} error, ${await response.text()}`;
        isError = true;
      }
    } catch {
      status = `No response from ESP`;
      isError = true;
    }
    isLoading = false;
  };

  const stop = async () => {
    isLoading = true;
    try {
      const response = await fetch(`${$espIP}/stop`, {
        method: "GET",
      });
      if (response.ok) {
        status = await response.text();
        isRunning = false;
        isError = false;
      } else {
        status = `${response.status} error, ${await response.text()}`;
        isError = true;
      }
    } catch {
      status = `No response from ESP`;
      isError = true;
    }
    isLoading = false;
  };

  const refresh = async () => {
    isLoading = true;
    try {
      const response = await fetch(`${$espIP}/getStatus`, {
        method: "GET",
      });
      if (response.ok) {
        const data = await response.json();
        status = `Number of shots: ${data.numShots}\nStatus code: ${data.errorCode}\nStatus message: ${data.errorMsg}`;
        isError = false;
      } else {
        status = `${response.status} error, ${await response.text()}`;
        isError = true;
      }
    } catch {
      status = `No response from ESP`;
      isError = true;
    }
    isLoading = false;
  };
</script>

<div class="section">
  <h2>Intervalometer</h2>
  <input
    type="number"
    bind:value={intervalSec}
    placeholder="Interval in seconds"
  />
  {#if isRunning}
    <button on:click={stop}> Stop </button>
  {:else}
    <button on:click={start}> Start </button>
  {/if}
  <button on:click={refresh}> Refresh status </button>

  {#if isLoading}
    <p>Loading...</p>
  {:else if isError}
    <p class="warning">{status}</p>
  {:else}
    <p class="success">{status}</p>
  {/if}
</div>
