import {
  findNoteByNoteSymbolAndOctave,
  flattenNote,
  getNotesForScale,
  getNotesWithinOctaveRange,
  getScaleStepsForScale,
  INoteSelectOption, noteSymbols,
  sharpenNote
} from "./notes";
import {ScaleTypesEnum} from "../../models/music/scales";
import {NoteSymbolTypes} from "../../models/music/INote";
import {ChordTypes, IChord} from "../../models/music/IChord";
import {IPredefinedNote} from "./predefinedNotes";
import {ISelectOption} from "../../models/view/common/ISelectOption";
import {IKey} from "../../models/view/autochorder/AutoChorderPreset";

//patterns can be strings, so we can indicate when to sharpen 's' or flatten 'b' a note
const _3b = '3b';
const _5b = '5b';
const _5s = '5s';
const _7b = '7b';
const _9b = '9b';
const _9s = '9s';
const _11s = '11s';
const _13b = '13b';

const c = buildChord;
export const chordFuncs = {
  major(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Major', pattern: [1, 3, 5], ...rest }); },
  minor(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor', pattern: [1, _3b, 5], ...rest }); },
  major7th(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Major 7th', pattern: [1, 3, 5, 7], ...rest }); },
  minor7th(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 7th',  pattern: [1, _3b, 5, _7b], ...rest }); },
  minorMajor7th(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor Major 7th',  pattern: [1, _3b, 5, 7], ...rest }); },
  sustained4(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Sustained 4',  pattern: [1, 4, 5], ...rest }); },
  sustained2(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Sustained 2',  pattern: [1, 2, 5], ...rest }); },
  _6(rest: Partial<IBuildChordTypeParam>){ return c({ type: '6',  pattern: [1, 3, 5, 6], ...rest }); },
  minor6(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 6',  pattern: [1, _3b, 5, 6], ...rest }); },
  _9(rest: Partial<IBuildChordTypeParam>){ return c({ type: '9',  pattern: [1, 3, 5, _7b, 9], ...rest }); },
  minor9(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 9',  pattern: [1, _3b, 5, _7b, 9], ...rest }); },
  major9(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Major 9',  pattern: [1, 3, 5, 7, 9], ...rest }); },
  minorMajor9(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor Major 9',  pattern: [1, _3b, 5, 7, 9], ...rest }); },
  _11(rest: Partial<IBuildChordTypeParam>){ return c({ type: '11',  pattern: [1, 3, 5, _7b, 9, 11], ...rest }); },
  minor11(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 11',  pattern: [1, _3b, 5, _7b, 9, 11], ...rest }); },
  major11(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Major 11',  pattern: [1, 3, 5, 7, 9, 11], ...rest }); },
  minorMajor11(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor Major 11',  pattern: [1, _3b, 5, 7, 9, 11], ...rest }); },
  _13(rest: Partial<IBuildChordTypeParam>){ return c({ type: '13',  pattern: [1, 3, 5, _7b, 9, 13], ...rest }); },
  minor13(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 13',  pattern: [1, _3b, 5, _7b, 9, 13], ...rest }); },
  major13(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Major 13',  pattern: [1, 3, 5, 7, 9, 13], ...rest }); },
  minorMajor13(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor Major 13',  pattern: [1, _3b, 5, 7, 9, 13], ...rest }); },
  add9(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Add 9',  pattern: [1, 3, 5, 9], ...rest }); },
  minorAdd9(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor Add 9',  pattern: [1, _3b, 5, 9], ...rest }); },
  _6add9(rest: Partial<IBuildChordTypeParam>){ return c({ type: '6 Add 9',  pattern: [1, 3, 5, 6, 9], ...rest }); },
  minor6add9(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 6 Add 9',  pattern: [1, _3b, 5, 6, 9], ...rest }); },
  dominant7thAdd11(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Dominant 7th Add 11',  pattern: [1, 3, 5, _7b, 11], ...rest }); },
  major7thAdd11(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Major 7th Add 11',  pattern: [1, 3, 5, 7, 11], ...rest }); },
  minor7thAdd11(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 7th Add 11',  pattern: [1, _3b, 5, _7b, 11], ...rest }); },
  minorMajor7thAdd11(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor Major 7th Add 11',  pattern: [1, _3b, 5, 7, 11], ...rest }); },
  dominant7thAdd13(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Dominant 7th Add 13',  pattern: [1, 3, 5, _7b, 13], ...rest }); },
  major7thAdd13(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Major 7th Add 13',  pattern: [1, 3, 5, 7, 13], ...rest }); },
  minor7thAdd13(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 7th Add 13',  pattern: [1, _3b, 5, _7b, 13], ...rest }); },
  minorMajor7thAdd13(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor Major 7th Add 13',  pattern: [1, _3b, 5, 7, 13], ...rest }); },
  _7flat5(rest: Partial<IBuildChordTypeParam>){ return c({ type: '7 flat 5',  pattern: [1, 3, _5b, _7b], ...rest }); },
  _7sharp5(rest: Partial<IBuildChordTypeParam>){ return c({ type: '7 sharp 5',  pattern: [1, 3, _5s, _7b], ...rest }); },
  _7flat9(rest: Partial<IBuildChordTypeParam>){ return c({ type: '7 flat 9',  pattern: [1, 3, 5, _7b, _9b], ...rest }); },
  _7sharp9(rest: Partial<IBuildChordTypeParam>){ return c({ type: '7 sharp 9',  pattern: [1, 3, 5, _7b, _9s], ...rest }); },
  _7sharp5flat9(rest: Partial<IBuildChordTypeParam>){ return c({ type: '7 sharp 5 flat 9',  pattern: [1, 3, _5s, _7b, _9b], ...rest }); },
  minorflat5(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Diminished / Minor flat 5',  pattern: [1, _3b, _5b], ...rest }); },
  minor7flat5(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 7 flat 5',  pattern: [1, _3b, _5b, _7b], ...rest }); },
  minor7sharp5(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 7 sharp 5',  pattern: [1, _3b, _5s, _7b], ...rest }); },
  minor7flat9(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Minor 7 flat 9',  pattern: [1, _3b, _5s, _7b, _9b], ...rest }); },
  _9sharp11(rest: Partial<IBuildChordTypeParam>){ return c({ type: '9 sharp 11',  pattern: [1, 3, 5, _7b, 9, _11s], ...rest }); },
  _9flat13(rest: Partial<IBuildChordTypeParam>){ return c({ type: '9 flat 13',  pattern: [1, 3, 5, _7b, 9, _13b], ...rest }); },
  _6sustained4(rest: Partial<IBuildChordTypeParam>){ return c({ type: '6 sustained 4',  pattern: [1, 4, 5, 6], ...rest }); },
  _7sustained4(rest: Partial<IBuildChordTypeParam>){ return c({ type: '7 sustained 4',  pattern: [1, 4, 5, _7b], ...rest }); },
  major7thsustained4(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Major 7th sustained 4',  pattern: [1, 4, 5, 7], ...rest }); },
  _9sustained4(rest: Partial<IBuildChordTypeParam>){ return c({ type: '9 sustained 4',  pattern: [1, 4, 5, _7b, 9], ...rest }); },
  major9thsustained4(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Major 9th sustained 4',  pattern: [1, 4, 5, 7, 9], ...rest }); },
  root(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Root',  pattern: [1], ...rest }); },
  dyad1and5(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Dyad: 1 & 5',  pattern: [1, 5], ...rest }); },
  dyad1and3(rest: Partial<IBuildChordTypeParam>){ return c({ type: 'Dyad: 1 & 3',  pattern: [1, 3], ...rest }); },
};

export interface IBuildChordTypeParam{
  rootNote: NoteSymbolTypes, octave: number,
}

export interface IBuildChordParam extends IBuildChordTypeParam{
  type: ChordTypes, pattern: (number|string)[], id: string, label: string
}

function buildChord({type='Major', rootNote='c', octave=3, pattern=[], id=generateRandomId(), label=`${rootNote} ${type}`}: Partial<IBuildChordParam>){
  // console.log('buildChord called for ', type, rootNote, octave, pattern);
  const majorScaleNotes = getMajorScaleNotes({rootNote, octave});
  // console.log('majorScaleNotes', majorScaleNotes);
  const notes = getNotesFromPattern({pattern, notes: majorScaleNotes});
  // console.log('notes', notes);
  const chord: IChord = {
    id,
    label,
    octave, //useful when we need to regenerate a chord based on type. let's us construct a new chord with settings of previous.
    rootNote,
    type,
    notes,
  };
  return chord;
}


/**
 * Used to determine if a chord is in a key, which is useful when generating random chords in a key.
 * @param chord - each note in the chord must exist in the notes param
 * @param notes - array of notes to check the chord against.
 * @returns {boolean}
 */
function doesChordContainOnlyTheseNotes({chord, notes}: {chord: IChord, notes: IPredefinedNote[]}){
  const noteSymbols = notes.map(n=>n.noteSymbol);
  const result = chord.notes.every((n)=>{
    return noteSymbols.includes(n.noteSymbol);
  });
  return result;
}

/**
 * Patterns can be used to construct chords, where the pattern is reference to the major scale of the root note.
 * e.g. for chord C Minor, we'd first grab the C Major scale: c, d, e, f, g
 * then we'd use the pattern [1, 3b, 5] to grab c, eb, g
 * @param rootNote
 * @param octave
 * @returns {Array<{id, noteSymbol, octave, frequency, midiNoteNumber}>}
 */
function getMajorScaleNotes({rootNote='c', octave=3}: {rootNote: NoteSymbolTypes, octave: number}){
  const notesWithStartingOctave = getNotesWithinOctaveRange({begin: octave, end: octave + 2});
  const majorScaleNotes = getNotesForScale({scale: ScaleTypesEnum.majorIonian, rootNote, notes: notesWithStartingOctave});
  return majorScaleNotes;
}

/**
 * Chords can be thought of as patterns of indexes to use against an array of major scale notes.
 * @param pattern - array of indexes to use to construct the chord. e.g. [1, 3, 5] for a major chord.
 * @param notes - array of major scale notes.
 * @returns {any[]}
 */
function getNotesFromPattern({pattern=[], notes=[]}: {pattern: (number | string)[], notes: IPredefinedNote[]}): IPredefinedNote[]{
  return pattern.map(p => {
    let result: IPredefinedNote;
    if(typeof p === 'string'){ // allow for '3b'
      // let [patternString, operation] = p;//  // '3', 'b'
      let patternString = p[0];
      let operation = p[1];
      if(p.length === 3){ // 11b
        // const [p1, p2, op] = p;
        let p1 = p[0];
        let p2 = p[1];
        let op = p[2];
        patternString = p1 + p2;
        operation = op;
      }
      const patternNumber = Number(patternString); // 3
      const note:IPredefinedNote = notes[patternNumber - 1]; //grab the note at 3
      if(operation === 'b'){
        result = flattenNote(note); //flatten it by looking at all notes and going to the index below this note.
      } else if(operation === 's'){
        result = sharpenNote(note); //flatten it by looking at all notes and going to the index below this note.
      } else {
        console.error(`unknown operation : ${operation} for note pattern`);
        result = note;
      }
    }else{
      result = notes[p-1];
    }
    return result;
  });
}

function generateRandomId({name=''}={}){
  return `${name}${getRandomInt()}time${Date.now()}`;
}

function getRandomInt(min=1, max=999999999) {
  min = Math.ceil(min);
  max = Math.floor(max) + 1;
  return Math.floor(Math.random() * (max - min)) + min; //The maximum is exclusive and the minimum is inclusive <- not any longer. max is now inclusive
}

export interface IChordSelectOption extends ISelectOption<string>{
  isInScale: boolean;
}


export const chordOptions: ISelectOption<string>[] = [
  {value:"major",label:"Major"} ,
  {value:"minor",label:"Minor"},
  {value:"major7th",label:"Major 7th"},
  {value:"minor7th",label:"Minor 7th"},
  {value:"minorMajor7th",label:"Minor Major 7th"},
  {value:"sustained4",label:"Sustained 4"},
  {value:"sustained2",label:"Sustained 2"},
  {value:"_6",label:"6"},
  {value:"minor6",label:"Minor 6"},
  {value:"_9",label:"9"},
  {value:"minor9",label:"Minor 9"},
  {value:"major9",label:"Major 9"},
  {value:"minorMajor9",label:"Minor Major 9"},
  {value:"_11",label:"11"},
  {value:"minor11",label:"Minor 11"},
  {value:"major11",label:"Major 11"},
  {value:"minorMajor11",label:"Minor Major 11"},
  {value:"_13",label:"13"},
  {value:"minor13",label:"Minor 13"},
  {value:"major13",label:"Major 13"},
  {value:"minorMajor13",label:"Minor Major 13"},
  {value:"add9",label:"Add 9"},
  {value:"minorAdd9",label:"Minor Add 9"},
  {value:"_6add9",label:"6 Add 9"},
  {value:"minor6add9",label:"Minor 6 Add 9"},
  {value:"dominant7thAdd11",label:"Dominant 7th Add 11"},
  {value:"major7thAdd11",label:"Major 7th Add 11"},
  {value:"minor7thAdd11",label:"Minor 7th Add 11"},
  {value:"minorMajor7thAdd11",label:"Minor Major 7th Add 11"},
  {value:"dominant7thAdd13",label:"Dominant 7th Add 13"},
  {value:"major7thAdd13",label:"Major 7th Add 13"},
  {value:"minor7thAdd13",label:"Minor 7th Add 13"},
  {value:"minorMajor7thAdd13",label:"Minor Major 7th Add 13"},
  {value:"minorflat5",label:"Diminished / Minor flat 5"},
  {value:"_7flat5",label:"7 flat 5"},
  {value:"_7sharp5",label:"7 sharp 5"},
  {value:"_7flat9",label:"7 flat 9"},
  {value:"_7sharp9",label:"7 sharp 9"},
  {value:"_7sharp5flat9",label:"7 sharp 5 flat 9"},
  {value:"minor7flat5",label:"Minor 7 flat 5"},
  {value:"minor7sharp5",label:"Minor 7 sharp 5"},
  {value:"minor7flat9",label:"Minor 7 flat 9"},
  {value:"_9sharp11",label:"9 sharp 11"},
  {value:"_9flat13",label:"9 flat 13"},
  {value:"_6sustained4",label:"6 sustained 4"},
  {value:"_7sustained4",label:"7 sustained 4"},
  {value:"major7thsustained4",label:"Major 7th sustained 4"},
  {value:"_9sustained4",label:"9 sustained 4"},
  {value:"major9thsustained4",label:"Major 9th sustained 4"},
  {value:"root",label:"Root"},
  {value:"dyad1and5",label:"Dyad: 1 & 5"},
  {value:"dyad1and3",label:"Dyad: 1 & 3"},
];


/**
 * Return a complete list of all options.  Options that are in scale will be placed first.
 * @param rootNote? - provide if the chord options should be in the given key e.g. 'c'
 * @param scale? - e.g. = 'majorIonian'
 * @param chordRootNote
 * @param chordOptions
 * @returns {*[]}
 */
export function getChordOptions({rootNote, scale, chordRootNote,}: {scale: ScaleTypesEnum, rootNote: NoteSymbolTypes, chordRootNote: NoteSymbolTypes}): IChordSelectOption[]{
  console.log(`getting chord options for rootNote: ${rootNote} scale: ${scale} chordRootNote: ${chordRootNote}`);

  const optionsThatExistInScale: IChordSelectOption[] = [];
  const optionsThatDontExistInScale: IChordSelectOption[] = [];
  //iterate over each option, generate the chord, then see if all notes of chord are in scale.
  //@ts-ignore
  const allChordsForChordRootNote = Object.keys(chordFuncs).map(funcName=>chordFuncs[funcName]({rootNote: chordRootNote, octave: 3}));
  //get all notes in the key (rootNote + scale) so we can verify that a generated chord for chordRootNote has only notes found in the key.
  const allNotesForScale = getNotesForScale({scale, rootNote});
  //iterate over each chord for chordRootNote and see if only has notes in the key.
  for(let chordForChordRootNote of allChordsForChordRootNote){
    const doAllNotesForChordExistInScale = doesChordContainOnlyTheseNotes({chord: chordForChordRootNote, notes: allNotesForScale});
    if(doAllNotesForChordExistInScale){ //the generated chord only has notes that belong to the key.
      //find the option and add it to our result.
      // console.error(`chord options: `, chordOptions);
      const optionThatMatchesChordType = chordOptions.find(co => co.label === chordForChordRootNote.type);
      // console.error(`matching optionThatMatchesChordType: `, optionThatMatchesChordType);
      if(optionThatMatchesChordType !== undefined){
        optionsThatExistInScale.push({...optionThatMatchesChordType, isInScale: true});
      }else{
        console.error(`no option found for ${scale}  rootNote:${rootNote} chord:`, chordForChordRootNote, ` allNotesForScale: `, allNotesForScale);
      }
    }else{
      const optionThatMatchesChordType = chordOptions.find(co => co.label === chordForChordRootNote.type);
      if(optionThatMatchesChordType){
        optionsThatDontExistInScale.push({...optionThatMatchesChordType, isInScale: false});
      }
    }
  }
  const options: IChordSelectOption[] = [...optionsThatExistInScale, ...optionsThatDontExistInScale];
  return options;
}
/**
 * http://www.piano-keyboard-guide.com/key-of-c-minor.html
 * https://en.wikipedia.org/wiki/Chord_progression
 * https://www.basicmusictheory.com/c-dorian-triad-chords
 * https://www.jamplay.com/articles/5-guides/120-modal-chord-progressions - has chord progressions for dorian, ionian, lydian, etc.
 *
 * I ii iii IV V vi viiÂ° - The capital roman numerals denote Major chords; the lower case denotes a minor chord.
 * @param rootNote
 * @param scale
 * @param octave
 */
export function buildChordProgression({rootNote='c', scale=ScaleTypesEnum.majorIonian, octave=5}: {rootNote?: NoteSymbolTypes, scale?: ScaleTypesEnum, octave?: number}){
  const notesWithStartingOctave = getNotesWithinOctaveRange({begin: octave, end: octave + 2});
  const notesForScalePlusExtra: IPredefinedNote[] = getNotesForScale({rootNote, scale, notes: notesWithStartingOctave});
  const notesForScale: IPredefinedNote[] = notesForScalePlusExtra.slice(0, getScaleStepsForScale({scale}).length);//only want the bare minimum of notes. e.g. don't want c2 and c3
  console.log('notesForScale: ', notesForScale);
  let result = buildChordProgressionUsingAuto({notesForScale});
  return result;
}

export function buildScaleProgression({rootNote='c', scale=ScaleTypesEnum.majorIonian, startOctave=5, endOctave=startOctave+1, }: {rootNote?: NoteSymbolTypes, scale?: ScaleTypesEnum, startOctave?: number, endOctave?: number}){
  const notesWithStartingOctave = getNotesWithinOctaveRange({begin: startOctave, end: endOctave});
  const notesForScalePlusExtra = getNotesForScale({rootNote, scale, notes:notesWithStartingOctave});
  const notesForScale = notesForScalePlusExtra;
  const result: IChord[] = [];
  //iterate over each note of scale
  for(let i = 0; i < notesForScale.length; ++i){
    const note = notesForScale[i];
    const {noteSymbol, octave} = note;
    const chord = chordFuncs.root({rootNote: noteSymbol, octave});
    result.push(chord);
  }
  return result;
}

function buildChordProgressionUsingChordTypes({chordTypeProgression=[], notesForScale=[]}){
  const result = [];
  //iterate over each note of scale
  for(let i = 0; i < notesForScale.length; ++i){
    const note = notesForScale[i];
    const {noteSymbol, octave} = note;
    const chordType = chordTypeProgression[i];
    if(typeof chordFuncs[chordType] !== 'function'){
      //this is expected. the notes length can be longer than the progression length, in some cases.
      // console.error('no chordType could be found for: ', chordType);
      continue;
    }
    //@ts-ignore
    const chord = chordFuncs[chordType]({rootNote: noteSymbol, octave});
    result.push(chord);
  }
  return result;
}

/**
 * iterates over each note of the scale. generates chords for each note until it finds one with all the notes in the scale
 * @param notesForScale
 * @returns {Array}
 */
function buildChordProgressionUsingAuto({notesForScale=[]}: {notesForScale: IPredefinedNote[]}){
  console.log('build chord progression using auto');
  const chords = [];
  for(let i = 0; i < notesForScale.length; ++i){
    const note = notesForScale[i];
    const {noteSymbol: rootNote, octave} = note;
    const chord = findFirstChordWithNotesInScale({notesForScale, rootNote, octave});
    if(!chord){
      console.error('could not find firstChordWithNotesInScale for ', notesForScale, rootNote, octave);
      continue;
    }
    chords.push(chord);
  }
  return chords;
}

/**
 * Iterates over each chord function in scales until it finds a chord that only contains the notes for the scale.
 * @param notesForScale - notes allowed in the scale. noteSymbol is used for comparison.
 * @param rootNote - which chord note is the basis for the chord. e.g. C Major would be 'c'.
 * @param octave - octave to start the chord at.
 * @returns {*}
 */
function findFirstChordWithNotesInScale({notesForScale, rootNote='c', octave=5}: {notesForScale: IPredefinedNote[], rootNote?: NoteSymbolTypes, octave?: number}){
  const chordFuncNames = Object.keys(chordFuncs);
  for(let i = 0; i < chordFuncNames.length; ++i){
    const chordFuncName = chordFuncNames[i];
    //@ts-ignore
    const chord = chordFuncs[chordFuncName]({rootNote, octave});
    const doesOnlyContainNotes = doesChordContainOnlyTheseNotes({chord, notes: notesForScale});
    if(doesOnlyContainNotes){
      return chord;
    }
  }
}


/**
 * generates a random chord. if scale is provided, the chord generated will have notes only in that scale.
 * useful for changing the chord type of an existing chord on the autochorder page.
 * @param rootNote - root of the chord. e.g. C Major would be 'c'
 * @param octave - which octave to start the chord at.
 * @param scale - scale from notes service e.g. 'majorIonian'
 * @param keyRootNote - the 'c' in C Major
 * @returns {chord}
 */
export function buildChordOfRandomType({rootNote, octave, scale, keyRootNote}: {rootNote: NoteSymbolTypes, octave: number, scale?: ScaleTypesEnum, keyRootNote: NoteSymbolTypes}): IChord{
  console.log(`building chord of random type.`);
  if(scale === undefined){
    //generate all chords for the root and octave by iterating over every chord function in chords
    //@ts-ignore
    const allChordsForRootAndOctave = Object.keys(chordFuncs).map(funcName=>chordFuncs[funcName]({rootNote, octave}));
    //select a random chord
    const randomIndex = getRandomInt(0, allChordsForRootAndOctave.length - 1);
    const randomChord = allChordsForRootAndOctave[randomIndex];
    return randomChord;
  }

  //determine which notes are allowed in the current key (rootNote + scale name)
  const notesWithStartingOctave = getNotesWithinOctaveRange({begin: octave, end: octave + 2});
  const notesForScale = getNotesForScale({scale, rootNote: keyRootNote, notes: notesWithStartingOctave});
  //generate all chords for the root and octave by iterating over every chord function in chords
  //@ts-ignore
  const allChordsForRootAndOctave = Object.keys(chordFuncs).map(funcName=>chordFuncs[funcName]({rootNote, octave}));
  //filter out chords that aren't in the key
  const chordsInScale = allChordsForRootAndOctave.filter(chord=>doesChordContainOnlyTheseNotes({chord, notes: notesForScale}));
  //select a random chord
  const randomIndex = getRandomInt(0, chordsInScale.length - 1);
  const randomChord = chordsInScale[randomIndex];
  return randomChord;
}

export function buildChordOfRandomRootNoteAndType({octave=3, scale=ScaleTypesEnum.majorIonian, keyRootNote='c'}: {octave?: number, scale?: ScaleTypesEnum, keyRootNote?: NoteSymbolTypes}){
  //pick a random note in the scale
  const root = getRandomNoteFromScale({scale, octave, keyRootNote});
  const rootNote = root.noteSymbol;
  console.log('random note: ', rootNote);
  const chord = buildChordOfRandomType({rootNote, octave, scale, keyRootNote});
  return chord;
}

export function getRandomNoteFromScale({scale=ScaleTypesEnum.majorIonian, keyRootNote='c', octave=3}: {scale?: ScaleTypesEnum, keyRootNote?: NoteSymbolTypes, octave?: number}){
  const notesWithStartingOctave = getNotesWithinOctaveRange({begin: octave, end: octave + 2});
  const notesForScalePlusExtra = getNotesForScale({rootNote: keyRootNote, scale, notes: notesWithStartingOctave});
  const notesForScale = notesForScalePlusExtra.slice(0, getScaleStepsForScale({scale}).length);//only want the bare minimum of notes. e.g. don't want c2 and c3
  const randomIndex = getRandomInt(0, notesForScale.length - 1);
  const note = notesForScale[randomIndex];
  return note;
}

function buildAllChords({notes=noteSymbols}: {notes?: NoteSymbolTypes[]} = {}){
  const chords: IChord[] = [];
  for(let note of notes){
    for(let chordFuncPropName in chordFuncs){
      //@ts-ignore
      const chordFunc = chordFuncs[chordFuncPropName];
      const chord = chordFunc({rootNote: note, octave: 1});
      chords.push(chord);
    }
  }
  return chords;
}

const allChords = buildAllChords();

export function reverseChordLookup({notes}: {notes: IPredefinedNote[]}){
  for(let chord of allChords){
    if(doesChordContainOnlyTheseNoteSymbols({notes, chord})){
      return chord;
    }
  }
}

function doesChordContainOnlyTheseNoteSymbols({notes, chord}: {notes: IPredefinedNote[], chord: IChord}){
  const chordNotes = chord.notes;
  if(chordNotes.length !== notes.length){ return false; }
  for(let note of notes){
    if(!chordNotes.find(cn => cn.noteSymbol === note.noteSymbol)){
      return false;
    }
  }
  return true;
}

export function findSensibleNoteToAddToChordGivenKey({key, chord}: {key: IKey, chord: IChord}){
  const chordOptionsInKey = getChordOptions({rootNote: key.rootNote, scale: key.scale, chordRootNote: chord.rootNote}).filter(o => o.isInScale);
  let sensibleNote = findNoteByNoteSymbolAndOctave({noteSymbol: chord.notes[0].noteSymbol, octave: chord.notes[0].octave + 1}) || chord.notes[0];
  let chordWithSensibleNote = chord;
  //@ts-ignore
  for(let chordOption of chordOptionsInKey){
    //@ts-ignore
    const possibleChord: IChord = chordFuncs[chordOption.value]({rootNote: chord.rootNote, octave: chord.octave});
    if(possibleChord.notes.length > chord.notes.length){
      //get the note from possible chord not in chord.
      const notesFromPossibleChordNotInChord = findNotesFromAnotFoundInB({notesA: possibleChord.notes, notesB: chord.notes});
      if(notesFromPossibleChordNotInChord.length > 0){
        sensibleNote = notesFromPossibleChordNotInChord[0];
        chordWithSensibleNote = possibleChord;
        break;
      }
    }
  }
  return {sensibleNote, chordWithSensibleNote};
}

function findNotesFromAnotFoundInB({notesA, notesB}: {notesA:IPredefinedNote[], notesB: IPredefinedNote[]}){
  const notInB: IPredefinedNote[] = [];
  for(let noteA of notesA){
    if(!notesB.find(nb => nb.noteSymbol === noteA.noteSymbol)){
      notInB.push(noteA);
    }
  }
  return notInB;
}

