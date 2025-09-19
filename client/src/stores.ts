import { writable } from "svelte/store";
import type { Action } from "./lib/actions";

export const isConnected = writable(false);
export const espIP = writable("192.168.4.1");
export const state = writable({
  statusCode: 0,
  statusMsg: "Page loaded.",
  sec: 0,
  ms: 0,
  millis: 0,
  cameraConnected: false,
  cameraIP: "192.168.4.7",
  isRunning: false,
  isStopping: false,
  timeUntilNext: 0,
  shutterIsPressed: false,
  actions: [],
  actionIndex: 0,
  loops: [] as {
    startIndex: number;
    startTime: number;
    cycleTime: number;
    duration: number;
    repetitions: number;
    completedReps: number;
  }[],
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
