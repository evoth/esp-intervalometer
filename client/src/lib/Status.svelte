<script>
  import { state, isLoading } from "../stores.js";
</script>

<div class="section">
  <h2>Status</h2>
  {#if $state.statusCode == 200}
    <p class="success">{$state.statusMsg}</p>
  {:else if $state.statusCode == 0}
    <p class="warning">{$state.statusMsg}</p>
  {:else}
    <p class="error">{`${$state.statusCode} error, ${$state.statusMsg}`}</p>
  {/if}
</div>
