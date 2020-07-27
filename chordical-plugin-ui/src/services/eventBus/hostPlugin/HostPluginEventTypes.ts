import {IMidiNoteData} from "../../../models/IMidiNoteData";

export interface IMessageToHost {
  type: "messageToHost";
  data: string; //json string with value { type: "someMessage", data: {x: y} }
}

export interface IWebAppLoaded{
  type: "webAppLoaded";
  data: string;
}


export interface IRequestToPlayMidiNotesMessage{
  type: "requestToPlayMidiNotesMessage";
  data: IMidiNoteData[];
}

export interface IRequestToStopMidiNotesMessage{
  type: "requestToStopMidiNotesMessage";
  data: IMidiNoteData[];
}

export type ToHostPluginMessageTypes = IMessageToHost | IWebAppLoaded | IRequestToPlayMidiNotesMessage | IRequestToStopMidiNotesMessage;



export interface IMidiNotePlayed{
  type: "midiNotePlayed";
  data : { midiNumber: number; velocity: number; }
}

export interface ITestMessage{
  type: "testMessage";
  data: string;
}

export type FromHostPluginMessageTypes = IMidiNotePlayed | ITestMessage;


export type HostPluginEventTypes = ToHostPluginMessageTypes | FromHostPluginMessageTypes;