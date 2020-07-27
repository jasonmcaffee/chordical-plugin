import {IMidiNoteData} from "../../../models/IMidiNoteData";

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

export interface IRequestToPlayMidiNotesMessage{
  type: "requestToPlayMidiNotesMessage";
  data: IMidiNoteData[];
}

export interface IRequestToStopMidiNotesMessage{
  type: "requestToStopMidiNotesMessage";
  data: IMidiNoteData[];
}

export type FromHostPluginMessageTypes = IMidiNotePlayed;

export type ToHostPluginMessageTypes = IMessageToHost | IWebAppLoaded | IRequestToPlayMidiNotesMessage | IRequestToStopMidiNotesMessage;

export type HostPluginEventTypes = ToHostPluginMessageTypes | FromHostPluginMessageTypes;