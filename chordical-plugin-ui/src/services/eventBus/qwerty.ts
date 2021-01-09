import {createEventBus} from "./common";

export interface IQwertyKeyDown{
  keyCode: number;
}

export interface IQwertyKeyUp {
  keyCode: number;
}

export const {subscribe: subscribeToQwertyKeyDown, emitMessage: keyDown, } = createEventBus<IQwertyKeyDown>();
export const {subscribe: subscribeToQwertyKeyUp, emitMessage: keyUp, } = createEventBus<IQwertyKeyDown>();