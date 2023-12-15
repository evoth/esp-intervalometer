<script>
  let theme =
    localStorage.getItem("theme") ||
    (window.matchMedia("(prefers-color-scheme: dark)").matches
      ? "dark"
      : "light");

  const toggle = () => {
    theme = theme == "light" ? "dark" : "light";
    localStorage.setItem("theme", theme);
  };
</script>

<button on:click={toggle} title="Switch theme">
  <img src="/icon.svg" alt="Crescent icon" />
</button>
{#if theme == "light"}
  <style>
    :root {
      --gray-5: var(--black);
      --gray-15: var(--darker);
      --gray-35: var(--dark);
      --gray-50: var(--medium);
      --gray-65: var(--light);
      --gray-85: var(--lighter);
      --gray-95: var(--white);
      --green-5: var(--dark-green);
      --green-95: var(--light-green);
      --red-5: var(--dark-red);
      --red-95: var(--light-red);
      --yellow-5: var(--dark-yellow);
      --yellow-95: var(--light-yellow);
    }
  </style>
{:else}
  <style>
    :root {
      --gray-5: var(--white);
      --gray-15: var(--lighter);
      --gray-35: var(--light);
      --gray-50: var(--medium);
      --gray-65: var(--dark);
      --gray-85: var(--darker);
      --gray-95: var(--black);
      --green-5: var(--light-green);
      --green-95: var(--dark-green);
      --red-5: var(--light-red);
      --red-95: var(--dark-red);
      --yellow-5: var(--light-yellow);
      --yellow-95: var(--dark-yellow);
    }
  </style>
{/if}

<style>
  :root {
    --black: #121212;
    --white: #e6e6e6;
    --dark: #4c4c4c;
    --light: #a5a5a5;
    --darker: #2d2d2d;
    --lighter: #c5c5c5;
    --medium: #888888;
    --light-red: #ff8484;
    --dark-red: #b70000;
    --light-green: #87ff85;
    --dark-green: #028100;
    --light-yellow: #fffd85;
    --dark-yellow: #768500;
  }

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
