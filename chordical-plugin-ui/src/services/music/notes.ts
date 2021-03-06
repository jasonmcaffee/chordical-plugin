import {IPredefinedNote, predefinedNotes} from './predefinedNotes';
import {NoteSymbolTypes} from "../../models/music/INote";
import {scaleNoteIndexes, ScaleTypesEnum} from "../../models/music/scales";
import {ISelectOption} from "../../models/view/common/ISelectOption";
export const noteSymbols: NoteSymbolTypes[] = ['c', 'c#', 'd', 'd#', 'e', 'f', 'f#', 'g', 'g#', 'a', 'a#', 'b'];
export interface INoteSelectOption extends ISelectOption<NoteSymbolTypes> {
  isInKey?: boolean;
}

export const noteSelectOptions: INoteSelectOption[] = [{"value":"c","label":"c"},{"value":"c#","label":"c#"},{"value":"d","label":"d"},{"value":"d#","label":"d#"},{"value":"e","label":"e"},{"value":"f","label":"f"},{"value":"f#","label":"f#"},{"value":"g","label":"g"},{"value":"g#","label":"g#"},{"value":"a","label":"a"},{"value":"a#","label":"a#"},{"value":"b","label":"b"}];

export interface IOctaveOption {
  value: number,
  name: string,
}
export const octaveOptions: ISelectOption<number>[] = [{"value":0,"label":"0"},{"value":1,"label":"1"},{"value":2,"label":"2"},{"value":3,"label":"3"},{"value":4,"label":"4"},{"value":5,"label":"5"},{"value":6,"label":"6"},{"value":7,"label":"7"},{"value":8,"label":"8"},{"value":9,"label":"9"},{"value":10,"label":"10"},{"value":11,"label":"11"}];

export function findNoteByMidiNoteNumber(midiNoteNumber: number): IPredefinedNote| undefined{
  const note = predefinedNotes.find(n=>n.midiNoteNumber===midiNoteNumber);
  if(!note){ return; }
  const result = {...note}; //fix for weird issue where midi note play would result in qwerty note play to stop working.
  return result;
}


export function findNoteByNoteSymbolAndOctave({noteSymbol, octave}: {noteSymbol: NoteSymbolTypes, octave: number}){
  const result = predefinedNotes.find(n=>n.noteSymbol === noteSymbol && n.octave === octave);
  return result;
}

export function createNoteWithRandomOctave({noteSymbol, minOctave=2, maxOctave=8}: {noteSymbol: NoteSymbolTypes, minOctave: number, maxOctave: number}){
  let octave = getRandomInt(minOctave, maxOctave);
  // console.error(`octave is : ${octave}`);
  let note = findNoteByNoteSymbolAndOctave({noteSymbol, octave});
  //if the random octave isn't on the keyboard, try min then max
  if(note && !isNoteOn88KeyKeyboard(note)){
    // console.error(`note not found on keyboard: `, note);
    let lowestNoteOnKeyboard;
    for(let i = minOctave; i <= maxOctave; ++i){
      const n = findNoteByNoteSymbolAndOctave({noteSymbol, octave: i});
      if(n && isNoteOn88KeyKeyboard(n)){
        lowestNoteOnKeyboard = n;
        // console.error(`lowest note on keyboard: `, lowestNoteOnKeyboard);
        break;
      }
    }
    let highestNoteOnKeyboard;
    for(let i = maxOctave; i >= minOctave; --i){
      const n = findNoteByNoteSymbolAndOctave({noteSymbol, octave: i});
      if(n && isNoteOn88KeyKeyboard(n)){
        highestNoteOnKeyboard = n;
        break;
      }
    }
    if(lowestNoteOnKeyboard && highestNoteOnKeyboard){
      octave = getRandomInt(lowestNoteOnKeyboard.octave, highestNoteOnKeyboard.octave);
      note = findNoteByNoteSymbolAndOctave({noteSymbol, octave});
    }
  }
  return note;
}

export function isNoteOn88KeyKeyboard(note: IPredefinedNote){
  return note.midiNoteNumber >= 21 && note.midiNoteNumber <= 108;
}

/**
 * Filters notes before first occurrence of rootNote.
 * Useful for creating a scale in a given key, where the key is the starting note/rootNote
 * @param rootNote - first entry in returned array should be this note.
 * @param notes - optional - array of notes to filter.
 * @returns {*[]}
 */
export function getNotesStartingAtRootNote({rootNote, notes=predefinedNotes} : {rootNote: NoteSymbolTypes, notes: IPredefinedNote[]}){
  const firstIndexOfRootNote = notes.findIndex(n=>n.noteSymbol===rootNote);
  const result = notes.slice(firstIndexOfRootNote);
  return result;
}

/**
 * Filters notes down to only notes within the specified octaves.
 * Useful for displaying a subset of notes on the keyboard page, as well as constructing chords
 * @param begin - beginning octave. inclusive
 * @param end - ending octave. inclusive
 * @param notes - optional - array of notes to filter for notes of given octave.
 * @returns {*[]}
 */
export function getNotesWithinOctaveRange({begin=0, end=10, notes=predefinedNotes}){
  const result = notes.filter(n => n.octave >= begin && n.octave <= end);
  return result;
}

/**
 * Convert new structure of notes to legacy way.
 * New uses an array, whereas legacy used an object literal.
 * @param notes - e.g. [ {id: "c1", octave: 1, midiNoteNumber: 55, } ]
 * @returns {*} - e.g.
 * {
 *     c1: {
 *         id: "c1",
 *         octave: 1,
 *     },...
 * }
 */
// export function convertNoteArrayToObject({notes}){
//   const result = notes.reduce((acc, note)=>{
//     acc[note.id] = note;
//     return acc;
//   }, {});
//   return result;
// }

/**
 * Finds all notes for a given scale.
 * @param scale - name of the scale to get notes for
 * @param rootNote - aka key - starting note
 * @param notes - optional - array of notes to be used to filter against.
 * @returns {Array<{"id", "noteSymbol", "octave", "frequency", "midiNoteNumber"}>}
 */
export function getNotesForScale({scale=ScaleTypesEnum.chromatic, rootNote='c', notes=predefinedNotes}: {scale?: ScaleTypesEnum, rootNote?: NoteSymbolTypes, notes?: IPredefinedNote[]}): IPredefinedNote[]{
  const notesStartingAtRootNote = getNotesStartingAtRootNote({rootNote, notes});
  const scaleSteps = getScaleStepsForScale({scale});
  const notesInScale: IPredefinedNote[] = [];

  if(scaleSteps === undefined){
    console.error(`scalesSteps dont exist for: ${scale}`);
    return notesInScale;
  }
  let currentIndex = 0;
  for(let note of notesStartingAtRootNote){
    if(scaleSteps.includes(currentIndex++)){
      notesInScale.push(note);
    }
    if(currentIndex > 11){
      currentIndex = 0;
    }
  }
  return notesInScale;
}

/**
 * Returns an array of indexes to use to construct a scale of a given type.
 * Meant to use in conjunction with a notes array.
 * e.g.
 * notes = [ {noteSymbol:"c"}, {noteSymbol:"c#"}, {noteSymbol:"d"}, {noteSymbol:"d#"}, {noteSymbol:"e"}, {noteSymbol:"f"}, ]
 *
 * For a major scale, the indexes would be [0, 2, 4, 5, 7, 9, 11], where 0 is c, 2 is d, 4 is e, 5 is f, etc
 * @param scale
 * @returns {*}
 */
export function getScaleStepsForScale({scale}: {scale: ScaleTypesEnum}){
  return scaleNoteIndexes[scale];
}

export const scaleOptions = Object.keys(scaleNoteIndexes).map(scale=>{
  return {name: scale, value: scale};
});

export function flattenNote({octave, noteSymbol, notes=predefinedNotes}: {octave: number, noteSymbol: NoteSymbolTypes, notes?: IPredefinedNote[]}){
  const noteIndex = notes.findIndex(n => n.octave === octave && n.noteSymbol === noteSymbol);
  if(noteIndex < 0){ console.error(`flattenNote cant find noteSymbol: ${noteSymbol} octave: ${octave}`); return notes[0]; }
  const flattenedNote = notes[noteIndex - 1]; //todo: small chance for error if no index
  return flattenedNote;
}

export function sharpenNote({octave, noteSymbol, notes=predefinedNotes}: {octave: number, noteSymbol: NoteSymbolTypes, notes?: IPredefinedNote[]}){
  const noteIndex = notes.findIndex(n => n.octave === octave && n.noteSymbol === noteSymbol);
  if(noteIndex < 0){ console.error(`sharpenNote cant find noteSymbol: ${noteSymbol} octave: ${octave}`); return notes[0]; }
  const sharpenedNote = notes[noteIndex + 1]; //todo: small chance for error if no index
  return sharpenedNote;
}

function getRandomInt(min=1, max=999999999) {
  min = Math.ceil(min);
  max = Math.floor(max) + 1;
  return Math.floor(Math.random() * (max - min)) + min; //The maximum is exclusive and the minimum is inclusive <- not any longer. max is now inclusive
}