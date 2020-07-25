import {HostPluginEventTypes} from './HostPluginEventTypes';
import {Subject} from 'rxjs';

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