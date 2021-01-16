import INote, {NoteSymbolTypes} from "./INote";
import {IPredefinedNote} from "../../services/music/predefinedNotes";

export interface IChord {
  id: string,
  label: string,
  octave: number, //useful when we need to regenerate a chord based on type. let's us construct a new chord with settings of previous.
  rootNote: NoteSymbolTypes,
  type: ChordTypes,
  notes: IPredefinedNote[],
}

export type ChordTypes = "Custom" | "Major" | "Minor" | "Major 7th" | "Minor 7th" | "Minor Major 7th" | "Sustained 4" | "Sustained 2" | "6" | "Minor 6" | "9" | "Minor 9" | "Major 9" | "Minor Major 9" | "11" | "Minor 11" | "Major 11" | "Minor Major 11" | "13" | "Minor 13" | "Major 13" | "Minor Major 13" | "Add 9" | "Minor Add 9" | "6 Add 9" | "Minor 6 Add 9" | "Dominant 7th Add 11" | "Major 7th Add 11" | "Minor 7th Add 11" | "Minor Major 7th Add 11" | "Dominant 7th Add 13" | "Major 7th Add 13" | "Minor 7th Add 13" | "Minor Major 7th Add 13" | "Diminished / Minor flat 5" | "7 flat 5" | "7 sharp 5" | "7 flat 9" | "7 sharp 9" | "7 sharp 5 flat 9" | "Minor 7 flat 5" | "Minor 7 sharp 5" | "Minor 7 flat 9" | "9 sharp 11" | "9 flat 13" | "6 sustained 4" | "7 sustained 4" | "Major 7th sustained 4" | "9 sustained 4" | "Major 9th sustained 4" | "Root" | "Dyad: 1 & 5" | "Dyad: 1 & 3";

export interface IChordProgression {
  name: 'Major' | 'Minor',
  chordTypeProgression: ChordTypes[],
}

const chordProgressions: IChordProgression[] = [
  {name: 'Major', chordTypeProgression: ['Major', 'Minor', 'Minor', 'Major', 'Major', 'Minor', 'Minor 7 flat 5']},
  {name: 'Minor', chordTypeProgression: ['Minor', 'Minor 7 flat 5', 'Major', 'Minor', 'Minor', 'Major', 'Major']},
];

export enum ChordTypesEnum{
  major = "Major",
  minor = "Minor",
  major7th = "Major 7th",
  minor7th = "Minor 7th",
  minorMajor7th = "Minor Major 7th",
  sustained4 = "Sustained 4",
  sustained2 = "Sustained 2",
  _6 = "6",
  minor6 = "Minor 6",
  _9 = "9",
  minor9 = "Minor 9",
  major9 = "Major 9",
  minorMajor9 = "Minor Major 9",
  _11 = "11",
  minor11 = "Minor 11",
  major11 = "Major 11",
  minorMajor11 = "Minor Major 11",
  _13 = "13",
  minor13 = "Minor 13",
  major13 = "Major 13",
  minorMajor13 = "Minor Major 13",
  add9 = "Add 9",
  minorAdd9 = "Minor Add 9",
  _6add9 = "6 Add 9",
  minor6add9 = "Minor 6 Add 9",
  dominant7thAdd11 = "Dominant 7th Add 11",
  major7thAdd11 = "Major 7th Add 11",
  minor7thAdd11 = "Minor 7th Add 11",
  minorMajor7thAdd11 = "Minor Major 7th Add 11",
  dominant7thAdd13 = "Dominant 7th Add 13",
  major7thAdd13 = "Major 7th Add 13",
  minor7thAdd13 = "Minor 7th Add 13",
  minorMajor7thAdd13 = "Minor Major 7th Add 13",
  minorflat5 = "Diminished / Minor flat 5",
  _7flat5 = "7 flat 5",
  _7sharp5 = "7 sharp 5",
  _7flat9 = "7 flat 9",
  _7sharp9 = "7 sharp 9",
  _7sharp5flat9 = "7 sharp 5 flat 9",
  minor7flat5 = "Minor 7 flat 5",
  minor7sharp5 = "Minor 7 sharp 5",
  minor7flat9 = "Minor 7 flat 9",
  _9sharp11 = "9 sharp 11",
  _9flat13 = "9 flat 13",
  _6sustained4 = "6 sustained 4",
  _7sustained4 = "7 sustained 4",
  major7thsustained4 = "Major 7th sustained 4",
  _9sustained4 = "9 sustained 4",
  major9thsustained4 = "Major 9th sustained 4",
  root = "Root",
  dyad1and5 = "Dyad: 1 & 5",
  dyad1and3 = "Dyad: 1 & 3",
}