import {IChord} from "../../music/IChord";

export default interface ISlot{
  content?: IChord;
  midiNoteTriggers: number[];
  qwertyKeyCodeTrigger: number;
}