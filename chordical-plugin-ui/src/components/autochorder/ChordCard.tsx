import React from 'react';
import {IChord} from "../../models/music/IChord";
import '../../style/components/autochorder/chord-card.scss';
import autochorder from '../../services/pages/autochorder';
import IAutochorderPageViewModel from "../../models/view/autochorder/IAutochorderPageViewModel";
import Select from "../common/Select";
import {IPredefinedNote} from "../../services/music/predefinedNotes";
import {ISelectOption} from "../../models/view/common/ISelectOption";

export default function ChordCard({chord, viewModel}: {chord: IChord, viewModel: IAutochorderPageViewModel}){

  const key = chord.id;
  return <div key={key} className="chord-card">
    <div className="details">
      <div className="label" onMouseDown={() => autochorder.playChord({chord})} onMouseUp={() => autochorder.stopChord({chord})}>{chord.label}</div>
    </div>
    <div className="notes">
      {createSelectForEachNoteInChord({chord, viewModel})}
    </div>
   </div>;
}

function createSelectForEachNoteInChord({chord, viewModel}: {chord: IChord, viewModel: IAutochorderPageViewModel}){
  return chord.notes.map(note => createSelectForNote({note, chord, viewModel}));
}

function createSelectForNote({note, chord, viewModel}: {note: IPredefinedNote, chord: IChord, viewModel: IAutochorderPageViewModel}){
  const selectOptionForNote = viewModel.noteSelectOptions.find(s => s.value === note.noteSymbol);
  const selectedOptionForOctave = viewModel.octaveOptions.find(o => o.value === note.octave);
  console.error(`chord is:`, chord, selectedOptionForOctave);
  return <div className="note-and-octave">
    <Select options={viewModel.noteSelectOptions} onChange={(option)=> autochorder.changeNoteSymbol({note, chord, newNoteSymbol: option.value})} currentlySelectedOption={selectOptionForNote}/>
    <Select options={viewModel.octaveOptions} onChange={(option)=> autochorder.changeNoteOctave({note, chord, newNoteOctave: option.value})} currentlySelectedOption={selectedOptionForOctave}/>
  </div>
}