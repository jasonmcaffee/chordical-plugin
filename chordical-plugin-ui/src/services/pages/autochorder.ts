import {createEventBusAndHook} from "../eventBus/common";
import IAutochorderPageViewModel from "../../models/view/autochorder/IAutochorderPageViewModel";
import {NoteSymbolTypes} from "../../models/music/INote";
import {ScaleTypesEnum} from "../../models/music/scales";
import {
  buildChordOfRandomRootNoteAndType, buildChordOfRandomType, buildChordProgression,
  buildScaleProgression,
  chordFuncs as chordServiceChords,
  chordOptions,
  getChordOptions
} from "../music/chords";
import {IChord} from "../../models/music/IChord";
import {IPredefinedNote, predefinedNotes} from "../music/predefinedNotes";
import {createNoteWithRandomOctave, findNoteByNoteSymbolAndOctave} from "../music/notes";
import AutoChorderPreset, {IKey} from "../../models/view/autochorder/AutoChorderPreset";
import {
  requestToGetAppState,
  requestToPlayMidiNotes, requestToSaveAppState,
  requestToStopMidiNotes,
  subscribeToHostPluginEvents
} from "../eventBus/hostPlugin/toHostPluginEventBus";
import {IMidiNoteData} from "../../models/IMidiNoteData";
import {subscribeToFromHostPluginEvents} from "../eventBus/hostPlugin/fromHostPluginEventBus";
import ISlot from "../../models/view/autochorder/ISlot";
import {ISelectOption} from "../../models/view/common/ISelectOption";
import {subscribeToQwertyKeyDown, subscribeToQwertyKeyUp} from '../eventBus/qwerty';
import {qwertyKeyCodes} from "../qwerty/qwerty";

const noteSelectOptions = createSelectOptionsForNotes(predefinedNotes);
const scaleSelectOptions = createSelectOptionsForScales();
const initialViewModel: IAutochorderPageViewModel = { noteSelectOptions, test: false, autoChorderPreset: new AutoChorderPreset({slots: createDefaultSlots()}), scaleSelectOptions};

export const {subscribe: subscribeToViewModelChange, emitMessage: viewModelChanged, hook: useAutochorderPageViewModel} = createEventBusAndHook<IAutochorderPageViewModel>(initialViewModel);


class Autochorder{
  viewModel = initialViewModel;
  unsubscribeFuncs: (() => void)[] = [];
  constructor(){
    this.generateChordProgression({rootNote: 'c', octave: 4, scale: ScaleTypesEnum.majorIonian, saveState: false}); //saveState false as we wait for appStateLoaded
    this.unsubscribeFuncs = [
      subscribeToQwertyKeyDown(e => {
        const slots = findSlotsWithMatchingQwertyKeyTrigger({qwertyKeyCode: e.keyCode, slots: this.viewModel.autoChorderPreset.slots});
        this.playSlots({slots});
      }),
      subscribeToQwertyKeyUp(e =>  {
        const slots = findSlotsWithMatchingQwertyKeyTrigger({qwertyKeyCode: e.keyCode, slots: this.viewModel.autoChorderPreset.slots});
        this.stopSlots({slots});
      }),
      subscribeToFromHostPluginEvents((e) => {
        switch(e.type){
          case "appStateLoaded":
            try{
              const newViewModel = JSON.parse(e.state);
              this.viewModel = newViewModel;
              this.emitChange({saveState: false});
            }catch(e){
              //@ts-ignore
              document.getElementById('page').innerHTML += "failed to parse " + e.message;
            }
            break;
          case "midiNotePlayed":{
            console.error(`midi note played: `, e.data);
            const {midiNote} = e.data;
            const slots = findSlotsWithMatchingMidiNoteTrigger({midiNote, slots: this.viewModel.autoChorderPreset.slots});
            this.playSlots({slots});
            break;
          }
          case "midiNoteStopped":{
            const {midiNote} = e.data;
            const slots = findSlotsWithMatchingMidiNoteTrigger({midiNote, slots: this.viewModel.autoChorderPreset.slots});
            this.stopSlots({slots});
            break;
          }
        }
      })
    ];
  }

  loadViewModel(){
    setTimeout(()=> {
      // this.viewModel.test = true;
      // this.emitChange();

    }, 1000);
  }

  playSlots({slots}: {slots: ISlot[]}){
    slots.forEach((s)=>{
      if(s.content){
        this.playChord({chord: s.content});
      }
    });
  }
  stopSlots({slots}: {slots: ISlot[]}){
    slots.forEach((s)=>{
      if(s.content){
        this.stopChord({chord: s.content});
      }
    });
  }

  saveAppState(){
    const data = JSON.stringify(this.viewModel); //.replace(/"/g, "'");
    // const data = encodeURIComponent(JSON.stringify(this.viewModel));
    requestToSaveAppState(data);
    // requestToSaveAppState(`hello`);
  }

  getAppState(){
    requestToGetAppState();
  }
  emitChange({saveState=true}: {saveState?: boolean} = {}){
    this.viewModel = {...this.viewModel,};
    // this.viewModel = JSON.parse(JSON.stringify(this.viewModel));
    viewModelChanged(this.viewModel);
    if(saveState){
      this.saveAppState();
    }
  }

  getChordOptionsForChordTypesInKey({rootNote=this.viewModel.autoChorderPreset.selectedKey.rootNote, scale=this.viewModel.autoChorderPreset.selectedKey.scale, chordRootNote='c'}: {rootNote?: NoteSymbolTypes, scale?: ScaleTypesEnum, chordRootNote?: NoteSymbolTypes}){
    const options = getChordOptions({rootNote, scale, chordRootNote});
    console.debug(`options for chords in key: `, options, scale, rootNote);
    return options;
  }

  //######################################################### play ###################################################
  playChord({chord}: {chord: IChord}){
    const notes = convertChordToHostMidiNotes({chord});
    requestToPlayMidiNotes(notes);
  }

  stopChord({chord}: {chord: IChord}){
    const notes = convertChordToHostMidiNotes({chord});
    requestToStopMidiNotes(notes);
  }

  //######################################################### chord manipulation #####################################
  addEachNoteOfKeyAsChordCell({rootNote=this.viewModel.autoChorderPreset.selectedKey.rootNote, scale=this.viewModel.autoChorderPreset.selectedKey.scale, startOctave=this.viewModel.autoChorderPreset.randomizationMinOctave, endOctave=this.viewModel.autoChorderPreset.randomizationMaxOctave, }={}){
    const newChords = buildScaleProgression({rootNote, scale, startOctave, endOctave});
    this.viewModel.autoChorderPreset.chords = this.viewModel.autoChorderPreset.chords.concat(newChords);
    // trigger(presetChanged, {autoChorderPreset: this});
    this.emitChange();
  }

  changeRandomizationMinOctave({newOctave}:{newOctave: number}){
    this.viewModel.autoChorderPreset.randomizationMinOctave = newOctave;
    console.log('changeRandomizationMinOctave ', newOctave);
    // trigger(randomizationMinOctaveChanged, {octave: this.viewModel.randomizationMinOctave});
    this.emitChange();
  }

  changeRandomizationMaxOctave({newOctave}: {newOctave: number}){
    this.viewModel.autoChorderPreset.randomizationMaxOctave = newOctave;
    // trigger(randomizationMaxOctaveChanged, {octave: this.viewModel.randomizationMaxOctave});
    this.emitChange();
  }

  qwertykeyPressed({key, index}: {key: number, index: number}){
    console.log(`AutoChorderPreset received keyPressed for key: ${key} index: ${index}`);
    const chord = this.viewModel.autoChorderPreset.chords[index];
    if(!chord){ return console.log('no chord to play for index: ', index); }
    // trigger(ec.autoChorder.chordPressed, {chord});
    this.emitChange();
  }

  qwertykeyReleased({key, index}:  {key: number, index: number}){
    console.log(`AutoChorderPreset received keyReleased for key: ${key} index: ${index}`);
    const chord = this.viewModel.autoChorderPreset.chords[index];
    if(!chord){ return console.log('no chord to release for index: ', index); }
    this.emitChange();
  }

  changeKey({key}: {key: IKey}){
    const {rootNote, scale} = key;
    this.viewModel.autoChorderPreset.selectedKey = {rootNote, scale};
    // this.emitChange();
    this.generateChordProgression({rootNote, scale});
  }
  /**
   * Change the type of chord. e.g. 'Major 7th'.  Triggered by ui Select in ChordCell component.
   * @param chord - chord which should be modified.
   * @param newChordType - selected option from service/chords->chordOptions. Should match a function name in service/chords->chords.  e.g. "major", "_7"
   * @param chords - chords that currently exist in the preset. we will search this array by chord.id and modify that chord.
   */
  changeChordType({chord, newChordType, chords=this.viewModel.autoChorderPreset.chords, }: {chord: IChord, newChordType: string, chords?: IChord[]}){
    //find the chord to be modified in our array of chords
    const chordBeingModifiedIndex = chords.findIndex(c=>c.id === chord.id);
    if(chordBeingModifiedIndex < 0){ return console.log(`AutoChorderPreset doesn't have chord id: ${chord.id}`); }
    //@ts-ignore
    if(typeof chordServiceChords[newChordType] !== 'function'){ return console.error(`AutoChorderPreset cant find chord function for type: ${newChordType}`); }
    const chordBeingModified = chords[chordBeingModifiedIndex];
    //create a new chord.
    const {id, octave, rootNote} = chordBeingModified;
    //@ts-ignore
    const newChord = chordServiceChords[newChordType]({rootNote, octave});
    newChord.id = id; //keep the same id so ui component knows when it's chord has been updated.
    //replace in chords
    chords[chordBeingModifiedIndex] = newChord;
    //tell the ChordCell ui to use the new chord and refresh
    // trigger(chordChanged, {chord: newChord});
    this.emitChange();
  }

  changeChordRootNote({chord, newRootNote, chords=this.viewModel.autoChorderPreset.chords, }: {chord: IChord, newRootNote: NoteSymbolTypes, chords?: IChord[]}){
    //find the chord to be modified in our array of chords
    const chordBeingModifiedIndex = chords.findIndex(c=>c.id === chord.id);
    if(chordBeingModifiedIndex < 0){ return console.log(`AutoChorderPreset doesn't have chord id: ${chord.id}`); }
    const chordBeingModified = chords[chordBeingModifiedIndex];
    //create a new chord.
    const {id, octave, type} = chordBeingModified;
    const option = chordOptions.find(c=>c.name === type); //this leads you to be able to create a chord type for chord root that doesnt exist in scale.
    if(!option){ return console.error('chord option not found for type', type); }
    const functionName = option.value;
    //@ts-ignore
    const newChord = chordServiceChords[functionName]({rootNote: newRootNote, octave});
    newChord.id = id; //keep the same id so ui component knows when it's chord has been updated.
    //replace in chords
    chords[chordBeingModifiedIndex] = newChord;
    //tell the ChordCell ui to use the new chord and refresh
    // trigger(chordChanged, {chord: newChord});
    this.emitChange();
  }

  changeNoteSymbol({chord, note, newNoteSymbol, chords=this.viewModel.autoChorderPreset.chords}: {chord: IChord, note: IPredefinedNote, newNoteSymbol: NoteSymbolTypes, chords?: IChord[]}){
    //find the chord and note to be modified in our array of chords
    const noteAndChord =  getNoteAndChordFromChords({chordId: chord.id, noteId: note.id, chords});
    if(!noteAndChord){ return console.log(`AutoChordPreset chord id: ${chord.id} doesn't have note id: ${note.id} chords:`, chord, chords); }
    const {chord: chordBeingModified, note: noteBeingModified, noteIndex: noteBeingModifiedIndex} = noteAndChord;
    //find the new note
    const {octave} = noteBeingModified;
    const newNote = findNoteByNoteSymbolAndOctave({noteSymbol: newNoteSymbol, octave});
    //replace existing note with the new note
    const clone = cloneChord({chord: chordBeingModified});
    //@ts-ignore
    clone.notes[noteBeingModifiedIndex] = newNote;
    //replace the chord in chords array
    const indexOfChordBeingModified = chords.indexOf(chordBeingModified);
    chords[indexOfChordBeingModified] = clone;
    updateSlotContentByChordId(this.viewModel.autoChorderPreset.slots, clone);
    //tell the ChordCell ui to use the new chord and refresh
    // trigger(chordChanged, {chord: clone});
    this.emitChange();
  }

  changeNoteOctave({chord, note, newNoteOctave, chords=this.viewModel.autoChorderPreset.chords}: {chord: IChord, note: IPredefinedNote, newNoteOctave: number, chords?: IChord[]}){
    const noteAndChord = getNoteAndChordFromChords({chordId: chord.id, noteId: note.id, chords});
    if(!noteAndChord){ return console.log(`AutoChordPreset chord id: ${chord.id} doesn't have note id: ${note.id} chords:`, chords, chord); }
    //find the chord and note to be modified in our array of chords
    const {chord: chordBeingModified, note: noteBeingModified, noteIndex: noteBeingModifiedIndex} = noteAndChord;
    if(!noteBeingModified){ return console.log(`AutoChordPreset chord id: ${chord.id} doesn't have note id: ${note.id}`); }
    //find the new note
    const {noteSymbol} = noteBeingModified;
    const newNote = findNoteByNoteSymbolAndOctave({noteSymbol, octave: newNoteOctave});
    //replace existing note with the new note
    const clone = cloneChord({chord: chordBeingModified});
    //@ts-ignore
    clone.notes[noteBeingModifiedIndex] = newNote;
    //replace the chord in chords array
    const indexOfChordBeingModified = chords.indexOf(chordBeingModified);
    chords[indexOfChordBeingModified] = clone;
    //tell the ChordCell ui to use the new chord and refresh
    // trigger(chordChanged, {chord: clone});
    this.emitChange();
  }

  deleteNote({chord, note, chords=this.viewModel.autoChorderPreset.chords}:  {chord: IChord, note: IPredefinedNote, chords?: IChord[]}){
    const noteAndChord = getNoteAndChordFromChords({chordId: chord.id, noteId: note.id, chords});
    if(!noteAndChord){ return console.log(`AutoChordPreset chord id: ${chord.id} doesn't have note id: ${note.id} chords:`, chords, chord); }
    //find the chord to be modified in our array of chords
    const {chord: chordBeingModified, note: noteBeingModified, noteIndex: noteBeingModifiedIndex} = noteAndChord;
    if(!noteBeingModified){ return console.log(`AutoChordPreset chord id: ${chord.id} doesn't have note id: ${note.id}`); }
    //remove the note
    chordBeingModified.notes.splice(noteBeingModifiedIndex, 1);
    //tell the ChordCell ui to use the new chord and refresh
    // trigger(chordChanged, {chord: chordBeingModified});
    this.emitChange();
  }

  addNote({chord, chords=this.viewModel.autoChorderPreset.chords}: {chord: IChord, chords?: IChord[]}){
    //find the chord to be modified in our array of chords
    const chordBeingModified = chords.find(c=>c.id === chord.id);
    if(!chordBeingModified){ return console.log(`AutoChorderPreset doesn't have chord id: ${chord.id}`); }
    //create a new note and add it to the chord
    const newNote = findNoteByNoteSymbolAndOctave({noteSymbol:'c', octave: 3});
    if(!newNote){ return console.log(`no new note found`); }
    chordBeingModified.notes.push(newNote);
    //tell the ChordCell ui to use the new chord and refresh
    // trigger(chordChanged, {chord: chordBeingModified});
    this.emitChange();
  }

  addChord({onlyGenerateChordsInKey=true, selectedKey=this.viewModel.autoChorderPreset.selectedKey, octave=this.viewModel.autoChorderPreset.randomizationMinOctave}={}){
    const scale = onlyGenerateChordsInKey ? selectedKey.scale : undefined;
    const keyRootNote = selectedKey.rootNote;
    const newChord = buildChordOfRandomRootNoteAndType({keyRootNote, scale, octave});
    this.viewModel.autoChorderPreset.chords.push(newChord);
    // trigger(presetChanged, {autoChorderPreset: this});
    this.emitChange();
  }

  duplicateChord({chord}: {chord: IChord}){
    const newChord = {...chord, id: generateRandomId()};
    this.viewModel.autoChorderPreset.chords.push(newChord);
    console.log(`new chord is `, newChord, chord);
    // trigger(presetChanged, {autoChorderPreset: this});
    this.emitChange();
  }

  deleteChord({chord, chords=this.viewModel.autoChorderPreset.chords}: {chord: IChord, chords?:IChord[]}){
    //find the chord to be modified in our array of chords
    const chordBeingModifiedIndex = chords.findIndex(c=>c.id === chord.id);
    if(chordBeingModifiedIndex < 0){ return console.log(`AutoChorderPreset doesn't have chord id: ${chord.id} chords: `, chords, chords[0] && chords[0].id); }
    //remove the chord
    this.viewModel.autoChorderPreset.chords.splice(chordBeingModifiedIndex, 1);
    //update the ui
    // trigger(presetChanged, {autoChorderPreset: this});
    this.emitChange();
  }

  changeChordLabel({chord, newLabel, chords=this.viewModel.autoChorderPreset.chords}: {chord: IChord, newLabel: string, chords?: IChord[]}){
    //find the chord to be modified in our array of chords
    const chordBeingModified = chords.find(c=>c.id === chord.id);
    if(!chordBeingModified){ return console.log(`AutoChorderPreset doesn't have chord id: ${chord.id}`); }
    //don't modify a chord, especially it's notes, which are used to stop playing a chord.
    const clone = cloneChord({chord: chordBeingModified});
    //set the label
    clone.label = newLabel;
    //swap existing chord
    const chordIndex = chords.indexOf(chordBeingModified);
    chords[chordIndex] = clone;
    //update the ui
    // trigger(chordChanged, {chord: clone});
    this.emitChange();
  }

  randomizeNoteVoicingForChord({chord, chords=this.viewModel.autoChorderPreset.chords, minOctave=this.viewModel.autoChorderPreset.randomizationMinOctave, maxOctave=this.viewModel.autoChorderPreset.randomizationMaxOctave}: {chord: IChord, chords?: IChord[], minOctave?: number, maxOctave?: number}){
    //find the chord to be modified in our array of chords
    const chordBeingModified = chords.find(c=>c.id === chord.id);
    if(!chordBeingModified){ return console.log(`AutoChorderPreset doesn't have chord id: ${chord.id}`); }
    //don't modify a chord, especially it's notes, which are used to stop playing a chord.
    const clone = cloneChord({chord: chordBeingModified});
    const newNotes = clone.notes.map(n=>{
      const {noteSymbol} = n;
      return createNoteWithRandomOctave({noteSymbol, minOctave, maxOctave});
    });
    clone.notes = newNotes as IPredefinedNote[];
    //swap existing chord
    const chordIndex = chords.indexOf(chordBeingModified);
    chords[chordIndex] = clone;
    this.emitChange();
  }

  randomizeChordType({chord, onlyGenerateChordsInKey=true, chords=this.viewModel.autoChorderPreset.chords, octave=this.viewModel.autoChorderPreset.randomizationMinOctave}: {chord: IChord, onlyGenerateChordsInKey?: boolean, chords?: IChord[], octave?: number}){
    const chordBeingModified = chords.find(c=>c.id === chord.id);
    if(!chordBeingModified){ return console.log(`AutoChorderPreset doesn't have chord id: ${chord.id}`); }
    //if onlyGenerateChordsInKey is true, we will only build chords that have notes in the selected scale.
    const scale = onlyGenerateChordsInKey ? this.viewModel.autoChorderPreset.selectedKey.scale : undefined;
    const keyRootNote = this.viewModel.autoChorderPreset.selectedKey.rootNote;
    const {id, rootNote,} = chord;
    const randomChord = buildChordOfRandomType({rootNote, octave, scale, keyRootNote});
    if(!randomChord){ return console.error(`no random chord type could be found for this rootnote`); }
    randomChord.id = id;

    //replace existing chord in our chords array, so it can be found later with chords.find()
    const chordIndex = chords.indexOf(chordBeingModified);
    chords[chordIndex] = randomChord;

    //update the ui
    // trigger(chordChanged, {chord: randomChord});
    this.emitChange();
  }

  generateChordProgression({rootNote=this.viewModel.autoChorderPreset.selectedKey.rootNote, scale=this.viewModel.autoChorderPreset.selectedKey.scale, octave=this.viewModel.autoChorderPreset.randomizationMinOctave, saveState=true}: {rootNote?: NoteSymbolTypes, scale?: ScaleTypesEnum, octave?: number, saveState?: boolean}){
    console.log(`generateChordProgression rootNote: ${rootNote} scale: ${scale} octave: ${octave}`);
    const chordProgression = buildChordProgression({rootNote, scale, octave});
    this.viewModel.autoChorderPreset.chords = chordProgression;
    this.placeChordsInSlots();
    this.emitChange({saveState});
  }
  clearAllChords(){
    this.viewModel.autoChorderPreset.chords = [];
    this.emitChange();
  }
  placeChordsInSlots({autoChorderPreset=this.viewModel.autoChorderPreset}: {autoChorderPreset?: AutoChorderPreset} = {}){
    const {chords, slots} = autoChorderPreset;
    slots.forEach(slot => slot.content = undefined);
    for(let i = 0; i < chords.length; ++i){
      const chord = chords[i];
      if(i >= slots.length){
        const previousSlotFirstMidiNoteTrigger = slots[i - 1].midiNoteTriggers[0];
        const midiNoteTriggers = previousSlotFirstMidiNoteTrigger ? [previousSlotFirstMidiNoteTrigger + 1] : [];
        const qwertyKeyCode = qwertyKeyCodes[i];
        const slot: ISlot = { midiNoteTriggers, content: chord, qwertyKeyCodeTrigger: qwertyKeyCode.code};
        slots.push(slot);
        continue;
      }
      slots[i].content = chord;
    }
  }
}


function getNoteAndChordFromChords({chordId, noteId, chords}: {chordId: string, noteId: string, chords: IChord[]}) : undefined | { note: IPredefinedNote, chord: IChord, noteIndex: number}{
  // let result = {};
  const chordBeingModified = chords.find(c=>c.id === chordId);
  if(!chordBeingModified){ return; }
  console.log(`found chord being modified: `, chordBeingModified);

  const noteBeingModifiedIndex = chordBeingModified.notes.findIndex(n=>n.id === noteId);
  console.log(`note being modified index: `, noteBeingModifiedIndex, noteId);
  const noteBeingModified = chordBeingModified.notes[noteBeingModifiedIndex];
  if(!noteBeingModified){ return; }

  const result = {note: noteBeingModified, chord: chordBeingModified, noteIndex: noteBeingModifiedIndex};
  return result;
}

/**
 * when we add notes, etc, we don't want to modify an existing chord, as it's notes are used to stop playing the chord.
 * @param chord
 * @returns {*}
 */
function cloneChord({chord}: {chord: IChord}){
  //shallow
  const shallow = Object.assign({}, chord);
  shallow.notes = chord.notes.map(n=>n);
  return shallow;
}

const autochorder = new Autochorder();
export default autochorder;

function generateRandomId({name=''}={}){
  return `${name}${getRandomInt()}time${Date.now()}`;
}

function getRandomInt(min=1, max=999999999) {
  min = Math.ceil(min);
  max = Math.floor(max) + 1;
  return Math.floor(Math.random() * (max - min)) + min; //The maximum is exclusive and the minimum is inclusive <- not any longer. max is now inclusive
}

function convertChordToHostMidiNotes({chord}: {chord: IChord}) : IMidiNoteData[]{
  return chord.notes.map(n => {
    return { midiNote: n.midiNoteNumber, velocity: 100};
  });
}

function createDefaultSlots({startMidiNumber=60, numberOfSlots=20}: {startMidiNumber?: number, numberOfSlots?: number} = {}): ISlot[]{
  const result: ISlot[] = [];
  for(let i = 0; i < numberOfSlots; ++i){
    const midiNoteTrigger = startMidiNumber + i;
    const qwertyKeyCode = qwertyKeyCodes[i];
    const slot: ISlot = {midiNoteTriggers: [midiNoteTrigger], qwertyKeyCodeTrigger: qwertyKeyCode.code};
    result.push(slot);
  }
  return result;
}

function findSlotsWithMatchingMidiNoteTrigger({midiNote, slots}: {midiNote: number, slots: ISlot[]}){
  return slots.filter((s) => s.midiNoteTriggers.includes(midiNote));
}

function findSlotsWithMatchingQwertyKeyTrigger({qwertyKeyCode, slots}: {qwertyKeyCode: number, slots: ISlot[]}){
  return slots.filter(s => s.qwertyKeyCodeTrigger === qwertyKeyCode);
}

function updateSlotContentByChordId(slots: ISlot[], chord: IChord){
  const slot = slots.find(s => s.content?.id === chord.id);
  if(slot){
    slot.content = chord;
  }
}

function createSelectOptionsForNotes(notes: IPredefinedNote[]) : ISelectOption<NoteSymbolTypes>[]{
  return notes.map(n => {
    const option: ISelectOption<NoteSymbolTypes> = { value: n.noteSymbol, label: n.noteSymbol};
    return option;
  });
}

function createSelectOptionsForScales(): ISelectOption<ScaleTypesEnum>[]{
  return Object.values(ScaleTypesEnum).map(s => {
    const option: ISelectOption<ScaleTypesEnum> = { value: s, label: s};
    return option;
  })
}



// function test(){
//   const chord1: IChord = { notes: [ {midiNoteNumber: 40, noteSymbol: "c", octave: 4, frequency: 222, id:"no"}], id: "chord1", label: "", type: "6", rootNote: "c", octave: 4};
//   const chord2: IChord = { notes: [ {midiNoteNumber: 65, noteSymbol: "c", octave: 4, frequency: 222, id:"no"}], id: "chord1", label: "", type: "6", rootNote: "c", octave: 4};
//   const chord3: IChord = { notes: [ {midiNoteNumber: 70, noteSymbol: "c", octave: 4, frequency: 222, id:"no"}], id: "chord1", label: "", type: "6", rootNote: "c", octave: 4};
//   const chord4: IChord = { notes: [ {midiNoteNumber: 85, noteSymbol: "c", octave: 4, frequency: 222, id:"no"}], id: "chord1", label: "", type: "6", rootNote: "c", octave: 4};
//
//   function send(){
//     autochorder.playChord({chord: chord1});
//     autochorder.playChord({chord: chord2});
//     autochorder.playChord({chord: chord3});
//     autochorder.playChord({chord: chord4});
//     // setTimeout(()=>{
//     //
//     // }, 1);
//   }
//   send();
//   setInterval(() => {
//     send();
//   }, 5000);
// }
//
// test();