import { writable } from "svelte/store";

export const isConnected = writable(false);
export const cameraIP = writable("192.168.4.7");
export const espIP = writable("http://192.168.4.1");
