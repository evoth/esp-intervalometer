<script>
  export let theme =
    localStorage.getItem("theme") ||
    (window.matchMedia("(prefers-color-scheme: dark)").matches
      ? "dark"
      : "light");

  const update = () => {
    const classList = window.document.documentElement.classList;
    if (theme == "dark") {
      classList.add("dark");
    } else {
      classList.remove("dark");
    }
  };

  const toggle = () => {
    theme = theme == "light" ? "dark" : "light";
    localStorage.setItem("theme", theme);
    update();
  };

  update();
</script>

<button on:click={toggle} title="Switch theme">
  <img src="/icon.svg" alt="Crescent icon" />
</button>

<style>
  button {
    background-color: transparent;
    padding: 8px 8px;
    min-width: 48px;
    display: flex;
    align-items: center;
  }
  button:hover {
    background-color: var(--gray-65);
  }
</style>
