import {Subject} from "rxjs";
import {useEffect, useState} from "react";

interface IMessage {
}

export type Unsubscribe = () => void;
export type Subscribe<TMessage> = (callback: (message: TMessage) => void) => Unsubscribe;

export function protectedSubscribe<TMessage extends IMessage>(subject: Subject<TMessage>, callback: (message: TMessage) => void): Unsubscribe{
  const protectedCallback = (message: TMessage) => {
    try{
      callback(message);
    }catch(e){
      console.error(`error encountered in observer of ${message.constructor.name}`, e);
    }
  };
  const subscription = subject.subscribe(protectedCallback);
  return subscription.unsubscribe.bind(subscription);
}

export function createEventBusForMessage<TMessage extends IMessage>(){
  return new Subject<TMessage>();
}

export function createEmitMessageFunction<TMessage extends IMessage>(subject: Subject<TMessage>){
  return (m: TMessage) => subject.next(m);
}

export function createEventBus<TMessage extends IMessage>(){
  const eventBus = createEventBusForMessage<TMessage>();
  const emitMessage = createEmitMessageFunction<TMessage>(eventBus);
  const subscribe: Subscribe<TMessage> = (callback: (message: TMessage) => void) => protectedSubscribe(eventBus, callback);
  return { subscribe, eventBus, emitMessage,};
}

export function hookifyEventSubscription<TMessage>(subscribe: Subscribe<TMessage>, initialValue: TMessage){
  return () => {
    const [value, setValue] = useState<TMessage>(initialValue);
    useEffect(()=> subscribe(setValue), []);
    return value;
  }
}

export function createEventBusAndHook<TMessage extends IMessage>(initialValue: TMessage){
  const {subscribe, eventBus, emitMessage} = createEventBus<TMessage>();
  const hook = hookifyEventSubscription<TMessage>(subscribe, initialValue);
  return {subscribe, emitMessage, hook, eventBus};
}
