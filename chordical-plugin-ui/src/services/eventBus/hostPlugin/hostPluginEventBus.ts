import {HostPluginEventTypes, ToHostPluginMessageTypes, IMessageToHost} from './HostPluginEventTypes';
import {Subject} from 'rxjs';
import {IMidiNoteData} from "../../../models/IMidiNoteData";

const subject = new Subject<HostPluginEventTypes>();

export function subscribeToHostPluginEvents(callback: (message: HostPluginEventTypes) => void){
  function protectedCallback(message: HostPluginEventTypes) {
    try{
        callback(message);
    }catch(e){
        console.error(`error in host plugin event subscriber: `, e);
    }
  }
  const subscription = subject.subscribe(protectedCallback);
  return subscription.unsubscribe.bind(subscription);
}

export function sendMessageToHost(data: string){
  subject.next({type: "messageToHost", data});
}

function sendMessageObjToHost(messageObj: ToHostPluginMessageTypes){
  sendMessageToHost(messageToString(messageObj));
}

export function webAppLoaded(data: string){
  sendMessageObjToHost({type: "webAppLoaded", data});
}

export function requestToPlayMidiNotes(data: IMidiNoteData[]){
  sendMessageObjToHost({type: "requestToPlayMidiNotesMessage", data});
}

function messageToString(message: any){
  return JSON.stringify(message);
}