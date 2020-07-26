
export interface IMessageToHost {
    type: "messageToHost";
    data: string; //json string with value { type: "someMessage", data: {x: y} }
}

export interface IWebAppLoaded{
    type: "webAppLoaded";
    data: string;
}

export interface IMidiNotePlayed{
    type: "midiNotePlayed";
    data : { midiNumber: number; velocity: number; }
}

export type FromHostPluginMessageTypes = IMidiNotePlayed;

export type ToHostPluginMessageTypes = IMessageToHost | IWebAppLoaded;

export type HostPluginEventTypes = ToHostPluginMessageTypes | FromHostPluginMessageTypes;