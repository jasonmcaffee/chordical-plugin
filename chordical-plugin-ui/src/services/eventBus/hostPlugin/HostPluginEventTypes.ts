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

export interface IRequestToChangeWindowSizeMessage {
  type: "requestToChangeWindowSizeMessage";
  data: {
    windowHeight: number;
    windowWidth: number;
  }
}

export interface IRequestToSaveAppStateMessage{
  type: "requestToSaveAppStateMessage";
  data: string;
}

export interface IRequestToGetAppStateMessage {
  type: "requestToGetAppStateMessage";
}

export type ToHostPluginMessageTypes = IMessageToHost | IWebAppLoaded | IRequestToPlayMidiNotesMessage | IRequestToStopMidiNotesMessage | IRequestToSaveAppStateMessage | IRequestToGetAppStateMessage | IRequestToChangeWindowSizeMessage;

export interface IMidiNotePlayed{
  type: "midiNotePlayed";
  data : IMidiNoteData;
}

export interface IMidiNoteStopped{
  type: "midiNoteStopped";
  data : IMidiNoteData;
}
export interface ITestMessage{
  type: "testMessage";
  data: string;
}

export interface IAppStateLoaded {
  type: "appStateLoaded";
  state: string;
}

export type FromHostPluginMessageTypes = IMidiNotePlayed | ITestMessage | IMidiNoteStopped | IAppStateLoaded;


export type HostPluginEventTypes = ToHostPluginMessageTypes | FromHostPluginMessageTypes;