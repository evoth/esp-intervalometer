import { writable } from "svelte/store";
import type { Action } from "./lib/actions";

export const isConnected = writable(false);
export const espIP = writable("192.168.4.1");
export const state = writable({
  statusCode: 0,
  statusMsg: "Page loaded.",
  sec: 0,
  ms: 0,
  cameraConnected: false,
  isRunning: false,
  isStopping: false,
  cameraIP: "192.168.4.7",
  timeUntilNext: 0,
  shutterIsPressed: false,
  actions: [],
  loops: [],
  actionIndex: 0,
});
export const isLoading = writable(false);
export const socket = writable<WebSocket>();
export const actions = writable<Action[]>([
  {
    action: "Trigger shutter",
    fields: {},
    time: 0,
    timeMode: "from start",
  },
]);
