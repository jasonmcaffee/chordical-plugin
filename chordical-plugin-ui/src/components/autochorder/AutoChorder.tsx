import React from 'react';
import IAutochorderPageViewModel from "../../models/view/autochorder/IAutochorderPageViewModel";
import AutoChorderPreset from "../../models/view/autochorder/AutoChorderPreset";
import {IChord} from "../../models/music/IChord";
import ChordCard from "./ChordCard";
import autochorder from "../../services/pages/autochorder";
import {ScaleTypesEnum} from "../../models/music/scales";
import '../../style/components/autochorder/autochorder.scss';
import ISlot from "../../models/view/autochorder/ISlot";
import SlotCard from "./SlotCard";

export default function AutoChorder({viewModel}: {viewModel: IAutochorderPageViewModel}){
  const autoChorderPreset = viewModel.autoChorderPreset;
  // const chordCardEls = createChordCardEls({autoChorderPreset});
  const slotCardEls = createSlotEls({autoChorderPreset});
  return <div className="autochorder">
    Test: {viewModel.test ? 'true' : 'false'}
    <div onClick={()=> doSomething()}>Do Something</div>
    <div className="chord-cards">
      {slotCardEls}
    </div>

   </div>;
}

function createChordCardEls({autoChorderPreset}: {autoChorderPreset: AutoChorderPreset}){
  return autoChorderPreset.chords.map((chord) => createChordCardEl({chord}));
}

function createChordCardEl({chord}: {chord: IChord}){
  return <ChordCard key={chord.id} chord={chord}/>;
}

function createSlotEls({autoChorderPreset}: {autoChorderPreset: AutoChorderPreset}){
  return autoChorderPreset.slots.map(slot => createSlotEl({slot}));
}

function createSlotEl({slot, }: {slot: ISlot}){
  const chordEl = slot.content ? createChordCardEl({chord: slot.content}) : null;
  return <SlotCard slot={slot}> {chordEl}</SlotCard>;
}

const doSomething = () => autochorder.generateChordProgression({rootNote: 'c', scale: ScaleTypesEnum.majorIonian, octave: 4});