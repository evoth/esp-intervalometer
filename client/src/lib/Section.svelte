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
  <button
    class="heading"
    on:click={toggle}
    title={isExpanded ? "Collapse section" : "Expand section"}
    aria-expanded={isExpanded}
    aria-controls={`${name}-body`}
  >
    <slot name="heading" />
    <div class="arrow-container">
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
    </div>
  </button>
  {#if isExpanded}
    <div id={`${name}-body`} class="body" transition:slide={{ duration: 300 }}>
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
    all: unset;
    display: flex;
    flex-direction: row;
    justify-content: space-between;
    align-items: center;
    padding-bottom: 16px;
  }

  .arrow-container {
    transition: background-color 0.2s;
    background-color: transparent;
    border-radius: 8px;
    padding: 4px 4px;
    display: flex;
    align-items: center;
  }
  .arrow-container:hover {
    background-color: var(--gray-65);
  }

  svg {
    transition: transform 0.3s;
    color: inherit;
  }
  svg.rotated {
    transform: rotate(-90deg);
  }
</style>
