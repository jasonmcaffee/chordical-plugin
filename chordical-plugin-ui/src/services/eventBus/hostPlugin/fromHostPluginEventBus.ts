import {FromHostPluginMessageTypes} from './HostPluginEventTypes';
import {Subject} from 'rxjs';

const fromHostSubject = new Subject<FromHostPluginMessageTypes>();

export function subscribeToFromHostPluginEvents(callback: (message: FromHostPluginMessageTypes) => void){
  function protectedCallback(message: FromHostPluginMessageTypes) {
    try{
      callback(message);
    }catch(e){
      console.error(`error in from host plugin event subscriber: `, e);
    }
  }
  const subscription = fromHostSubject.subscribe(protectedCallback);
  return subscription.unsubscribe.bind(subscription);
}

export function testMessage(data: string){
  fromHostSubject.next({type: "testMessage", data});
}