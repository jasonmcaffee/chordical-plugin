import React, {useEffect, useState} from 'react';
import {IChord} from "../../models/music/IChord";
import '../../style/components/autochorder/chord-card.scss';
import autochorder from '../../services/pages/autochorder';
import IAutochorderPageViewModel from "../../models/view/autochorder/IAutochorderPageViewModel";
import Select from "../common/Select";
import {IPredefinedNote} from "../../services/music/predefinedNotes";
import {ISelectOption} from "../../models/view/common/ISelectOption";
import Button from "../common/Button";
import {INoteSelectOption} from "../../services/music/notes";

export default function ChordCard({chord, viewModel}: {chord: IChord, viewModel: IAutochorderPageViewModel}){
  const chordTypeOptions2 = autochorder.getChordTypeSelectOptions({chordRootNote: chord.rootNote});
  const chordTypeOptions = chordTypeOptions2.map(c => ({...c, className: c.isInScale ? "in-key" : "not-in-key"}) );
  const currentlySelectChordTypeOption = chordTypeOptions.find(c => c.label === chord.type.toString());
  const noteSelectOptions = viewModel.noteSelectOptions.map(o => ({...o, className: o.isInKey ? "in-key": "not-in-key"}));
  const currentlySelectedChordRootNote = noteSelectOptions.find(o => o.value === chord.rootNote);
  const key = chord.id;
  return <div key={key} className="chord-card">
    <div className="details">
      <div className="label" onMouseDown={() => autochorder.playChord({chord})} onMouseUp={() => autochorder.stopChord({chord})}>{chord.label}</div>
      <Select currentlySelectedOption={currentlySelectedChordRootNote} options={noteSelectOptions} onChange={(o)=> autochorder.changeChordRootNote({chord, newRootNote: o.value})}/>
      <Select currentlySelectedOption={currentlySelectChordTypeOption} options={chordTypeOptions} onChange={(o) => autochorder.changeChordType({chord, newChordType: o.value})}/>
    </div>
    <div className="notes">
      <Button label={"randomize"} onClick={() => { autochorder.randomizeNoteVoicingForChordAndSample({chord}); } }/>
      {createSelectForEachNoteInChord({chord, viewModel, noteSelectOptions})}
      <Button label={"add"} onClick={() => autochorder.addNote({chord})}/>
    </div>
   </div>;
}

function createSelectForEachNoteInChord({chord, viewModel, noteSelectOptions}: {chord: IChord, viewModel: IAutochorderPageViewModel, noteSelectOptions: INoteSelectOption[]}){
  return chord.notes.map(note => createSelectForNote({note, chord, viewModel, noteSelectOptions}));
}

function createSelectForNote({note, chord, viewModel, noteSelectOptions}: {note: IPredefinedNote, chord: IChord, viewModel: IAutochorderPageViewModel, noteSelectOptions: INoteSelectOption[]}){
  // const selectOptionForNote = viewModel.noteSelectOptions.find(s => s.value === note.noteSymbol);
  const selectedOptionForOctave = viewModel.octaveOptions.find(o => o.value === note.octave);
  // const noteSelectOptions = viewModel.noteSelectOptions.map(o => ({...o, className: o.isInKey ? "in-key": "not-in-key"}));
  const selectOptionForNote = noteSelectOptions.find(s => s.value === note.noteSymbol);
  // console.error(`chord is:`, chord, selectedOptionForOctave);
  return <div className="note-and-octave">
    <Select options={noteSelectOptions} onChange={(option)=> autochorder.changeNoteSymbol({note, chord, newNoteSymbol: option.value})} currentlySelectedOption={selectOptionForNote}/>
    <Select options={viewModel.octaveOptions} onChange={(option)=> autochorder.changeNoteOctave({note, chord, newNoteOctave: option.value})} currentlySelectedOption={selectedOptionForOctave}/>
    <Button label={"X"} onClick={() => autochorder.deleteNote({chord, note}) }/>
  </div>
}