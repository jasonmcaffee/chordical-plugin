import {IChord} from "../../music/IChord";

export default interface ISlot{
  id: string;
  content?: IChord;
  midiNoteTriggers: number[];
  qwertyKeyCodeTrigger: number;
  isBeingPlayed: boolean; //ui indicator
}