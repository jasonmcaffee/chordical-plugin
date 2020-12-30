import {HostPluginEventTypes, ToHostPluginMessageTypes, IMessageToHost} from './HostPluginEventTypes';
import {Subject} from 'rxjs';
import {IMidiNoteData} from "../../../models/IMidiNoteData";

const toHostSubject = new Subject<ToHostPluginMessageTypes>();

export function subscribeToHostPluginEvents(callback: (message: ToHostPluginMessageTypes) => void){
  function protectedCallback(message: ToHostPluginMessageTypes) {
    try{
        callback(message);
    }catch(e){
        console.error(`error in host plugin event subscriber: `, e);
    }
  }
  const subscription = toHostSubject.subscribe(protectedCallback);
  return subscription.unsubscribe.bind(subscription);
}

const messageQueue: IMessageToHost[] = [];
export function sendMessageToHost(data: string){
  const message: IMessageToHost = {type: "messageToHost", data};
  messageQueue.push(message);
}

//temp fix is to send 1 message per ms
setInterval(()=>{
  const message = messageQueue.shift();
  if(message){
    toHostSubject.next(message);
  }
}, .1);

function sendMessageObjToHost(messageObj: ToHostPluginMessageTypes){
  sendMessageToHost(messageToString(messageObj));
}

export function webAppLoaded(data: string){
  sendMessageObjToHost({type: "webAppLoaded", data});
}

export function requestToPlayMidiNotes(data: IMidiNoteData[]){
  sendMessageObjToHost({type: "requestToPlayMidiNotesMessage", data});
}

export function requestToStopMidiNotes(data: IMidiNoteData[]){
  sendMessageObjToHost({type: "requestToStopMidiNotesMessage", data});
}


function messageToString(message: any){
  return JSON.stringify(message);
}