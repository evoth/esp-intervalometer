import { readable, writable } from "svelte/store";

export const isConnected = writable(false);
export const espIP = writable("192.168.4.1");
export const state = writable({
  statusCode: 0,
  statusMsg: "Page loaded.",
  sec: 0,
  ms: 0,
  cameraConnected: false,
  intervalSec: 35,
  isRunning: false,
  cameraIP: "192.168.4.7",
  numShots: 0,
});
export const isLoading = writable(false);
export const socket = writable();
