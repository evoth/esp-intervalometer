import { readable, writable } from "svelte/store";

export const isConnected = writable(false);
export const espIP = writable("192.168.4.1");
export const state = writable({
  statusCode: 0,
  statusMsg: "Page loaded.",
  sec: 0,
  ms: 0,
  cameraConnected: false,
  intervalSec: 35.0,
  isRunning: false,
  cameraIP: "192.168.4.7",
  numShots: 0,
  timeUntilNext: 0,
  bulbMode: false,
  bulbSec: 30.0,
  timeUntilRelease: 0,
  duration: 0,
  timeUntilCompletion: 0,
  shutterIsPressed: false,
});
export const isLoading = writable(false);
export const socket = writable();
