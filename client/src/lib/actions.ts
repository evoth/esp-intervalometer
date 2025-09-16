type ActionDef = {
  endpointUrl: string;
  httpMethod: "POST" | "PUT";
  body: any;
  fields: Record<string, { key: string; options: string[] }>;
};

// export type ActionKey = keyof typeof ACTIONS_DEF;

// export type Action<K extends ActionKey> = {
//   action: K;
//   fields: Record<keyof (typeof ACTIONS_DEF)[K]["fields"], string>;
//   time: number;
//   timeMode: "from start" | "after previous";
// };

export type Action = {
  action: string;
  fields: Record<string, string>;
  time: number;
  timeMode: "from start" | "after previous";
};

// export type AnyAction = {
//   [K in ActionKey]: Action<K>;
// }[ActionKey];

export const ACTIONS_DEF: Record<string, ActionDef> = {
  "Trigger shutter": {
    endpointUrl: "/ver100/shooting/control/shutterbutton",
    httpMethod: "POST",
    body: {
      af: false,
    },
    fields: {},
  },
  "Control shutter": {
    endpointUrl: "/ver100/shooting/control/shutterbutton/manual",
    httpMethod: "POST",
    body: {
      action: "full_press",
      af: false,
    },
    fields: {
      Action: {
        key: "action",
        options: ["full_press", "release"],
      },
    },
  },
  "Set ISO": {
    endpointUrl: "/ver100/shooting/settings/iso",
    httpMethod: "PUT",
    body: {
      value: "400",
    },
    fields: {
      ISO: {
        key: "value",
        options: [
          "auto",
          "100",
          "125",
          "160",
          "200",
          "250",
          "320",
          "400",
          "500",
          "640",
          "800",
          "1000",
          "1250",
          "1600",
          "2000",
          "2500",
          "3200",
          "4000",
          "5000",
          "6400",
          "8000",
          "10000",
          "12800",
          "16000",
          "20000",
          "25600",
        ],
      },
    },
  },
  "Set aperture": {
    endpointUrl: "/ver100/shooting/settings/av",
    httpMethod: "PUT",
    body: {
      value: "f8.0",
    },
    fields: {
      Aperture: {
        key: "value",
        options: [
          "f3.5",
          "f4.0",
          "f4.5",
          "f5.0",
          "f5.6",
          "f6.3",
          "f7.1",
          "f8.0",
          "f9.0",
          "f10",
          "f11",
          "f13",
          "f14",
          "f16",
          "f18",
          "f20",
          "f22",
        ],
      },
    },
  },
  "Set shutter speed": {
    endpointUrl: "/ver100/shooting/settings/tv",
    httpMethod: "PUT",
    body: {
      value: "1/125",
    },
    fields: {
      "Shutter speed": {
        key: "value",
        options: [
          "1/4000",
          "1/3200",
          "1/2500",
          "1/2000",
          "1/1600",
          "1/1250",
          "1/1000",
          "1/800",
          "1/640",
          "1/500",
          "1/400",
          "1/320",
          "1/250",
          "1/200",
          "1/160",
          "1/125",
          "1/100",
          "1/80",
          "1/60",
          "1/50",
          "1/40",
          "1/30",
          "1/25",
          "1/20",
          "1/15",
          "1/13",
          "1/10",
          "1/8",
          "1/6",
          "1/5",
          "1/4",
          '0"3',
          '0"4',
          '0"5',
          '0"6',
          '0"8',
          '1"',
          '1"3',
          '1"6',
          '2"',
          '2"5',
          '3"2',
          '4"',
          '5"',
          '6"',
          '8"',
          '10"',
          '13"',
          '15"',
          '20"',
          '25"',
          '30"',
          "bulb",
        ],
      },
    },
  },
  "Set exposure compensation": {
    endpointUrl: "/ver100/shooting/settings/exposure",
    httpMethod: "PUT",
    body: {
      value: "+0.0",
    },
    fields: {
      EV: {
        key: "value",
        options: [
          "-3.0",
          "-2_2/3",
          "-2_1/3",
          "-2.0",
          "-1_2/3",
          "-1_1/3",
          "-1.0",
          "-0_2/3",
          "-0_1/3",
          "+0.0",
          "+0_1/3",
          "+0_2/3",
          "+1.0",
          "+1_1/3",
          "+1_2/3",
          "+2.0",
          "+2_1/3",
          "+2_2/3",
          "+3.0",
        ],
      },
    },
  },
  "Set shooting mode": {
    endpointUrl: "/ver100/shooting/settings/shootingmode",
    httpMethod: "PUT",
    body: {
      value: "m",
    },
    fields: {
      Mode: {
        key: "value",
        options: ["m", "av", "tv", "p", "auto"],
      },
    },
  },
};
