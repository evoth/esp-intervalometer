<script lang="ts">
  import { clickoutside } from "@svelte-put/clickoutside";
  import { fade } from "svelte/transition";

  export let closeCondition = false;
  export let align: "top" | "bottom" = "bottom";
  export let showOptions = false;
  export let fullWidth = false;
  export let lighter = false;

  const toggleDropdown = () => (showOptions = !showOptions);

  // Disables showOptions when closeCondition is true
  $: showOptions = !closeCondition && showOptions;
</script>

<div
  class="options-container"
  use:clickoutside
  on:clickoutside={() => (showOptions = false)}
  style:flex={fullWidth ? "1" : undefined}
>
  <slot name="button" {toggleDropdown} />
  {#if showOptions}
    <div
      class="menu-container"
      transition:fade={{ duration: 100 }}
      style:top={align === "top" ? "0.5rem" : "100%"}
      style:width={fullWidth ? "100%" : undefined}
    >
      <div
        class="options-menu"
        style:width={fullWidth ? "100%" : undefined}
        style:background-color={lighter ? "var(--gray-85)" : "var(--gray-90)"}
      >
        <slot name="buttons" {toggleDropdown} />
      </div>
    </div>
  {/if}
  <slot />
</div>

<style>
  .options-container {
    position: relative;
  }

  .menu-container {
    position: absolute;
    left: 0;
    z-index: 1;
    white-space: pre;
  }

  .options-menu {
    display: inline-flex;
    flex-direction: column;
    padding: 0.5rem;
    border-radius: 0.7rem;
    border: var(--border-style);
    box-shadow:
      0 10px 15px -3px var(--shadow),
      0 4px 6px -4px var(--shadow);
  }

  .options-menu > :global(button) {
    font-size: 1.2rem;
    padding: 0.3rem;
    text-align: start;
  }
</style>
