<script>
  import { slide } from "svelte/transition";
  export let name;

  const storageKey = `${name}-expanded`;
  let isExpanded;
  if (localStorage.getItem(storageKey)) {
    isExpanded = localStorage.getItem(storageKey) == String(true);
  } else {
    isExpanded = true;
  }

  const toggle = () => {
    isExpanded = !isExpanded;
    if (name) {
      localStorage.setItem(storageKey, String(isExpanded));
    }
  };
</script>

<div class="section">
  <div class="heading">
    <slot name="heading" />
    <button on:click={toggle}>
      <svg
        class={isExpanded ? "rotated" : ""}
        xmlns="http://www.w3.org/2000/svg"
        width="24"
        height="24"
        viewBox="0 0 24 24"
        fill="none"
        stroke="currentColor"
        stroke-width="2"
        stroke-linecap="round"
        stroke-linejoin="round"><path d="M15 18l-6-6 6-6" /></svg
      >
    </button>
  </div>
  {#if isExpanded}
    <div class="body" transition:slide={{ duration: 300 }}>
      <slot />
    </div>
  {/if}
</div>

<style>
  .section {
    border-style: solid;
    border-width: 2px;
    border-color: var(--gray-50);
    border-radius: 16px;
    display: flex;
    flex-direction: column;
    padding: 16px;
    padding-bottom: 0px;
    transition: border-color 0.2s;
  }
  .body {
    display: flex;
    flex-direction: column;
    row-gap: 16px;
    padding-bottom: 16px;
  }
  .heading {
    display: flex;
    flex-direction: row;
    justify-content: space-between;
    align-items: center;
    padding-bottom: 16px;
  }
  button {
    color: inherit;
    background-color: transparent;
    padding: 4px 4px;
    display: flex;
    align-items: center;
  }
  button:hover {
    background-color: var(--gray-65);
  }
  svg {
    transition: transform 0.3s;
  }
  svg.rotated {
    transform: rotate(-90deg);
  }
</style>
