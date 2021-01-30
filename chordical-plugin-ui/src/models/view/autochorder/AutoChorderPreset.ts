import {NoteSymbolTypes} from "../../music/INote";
import {ScaleTypesEnum} from "../../music/scales";
import {IChord} from "../../music/IChord";
import ISlot from "./ISlot";

export interface IKey{
  rootNote: NoteSymbolTypes,
  scale: ScaleTypesEnum,
}

/**
 * Contains the state of chords of the preset/progression.
 * Contains the state of data displayed in the toolbar as well. (e.g. randomization values, selected key, etc.)
 * Handles modifying the state of chords. e.g. randomize notes in chord, add new chord, etc.
 * Handles qwerty key press events so that chords are played.
 */
export default class AutoChorderPreset {
  id = '';
  chords:IChord[] = []; //chord model array of all the chords in this preset.
  slots: ISlot[] = [];
  selectedKey: IKey = { rootNote: "c", scale: ScaleTypesEnum.majorIonian}; // we use key (rootnote + octave) when generating chord progressions (e.g. c major chord progression)
  randomizationMinOctave: number = 0;
  randomizationMaxOctave: number = 0;
  name: string = ''; // displayed to user on preset selector.
  constructor({id=generateRandomId({name:'AutoChorderPreset'}), selectedKey={rootNote:'c', scale: ScaleTypesEnum.majorIonian},
                chords=[], randomizationMinOctave=3, randomizationMaxOctave=5,
                name=`${new Date().toLocaleString()}`, slots=[]} :Partial<AutoChorderPreset>) {
    Object.assign(this, {id, chords, selectedKey, randomizationMinOctave, randomizationMaxOctave, name, slots});
  }
}

function generateRandomId({name=''}={}){
  return `${name}${getRandomInt()}time${Date.now()}`;
}

function getRandomInt(min=1, max=999999999) {
  min = Math.ceil(min);
  max = Math.floor(max) + 1;
  return Math.floor(Math.random() * (max - min)) + min; //The maximum is exclusive and the minimum is inclusive <- not any longer. max is now inclusive
}