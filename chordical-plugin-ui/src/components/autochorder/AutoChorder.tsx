import React from 'react';
import IAutochorderPageViewModel from "../../models/view/autochorder/IAutochorderPageViewModel";
import AutoChorderPreset from "../../models/view/autochorder/AutoChorderPreset";
import {IChord} from "../../models/music/IChord";
import ChordCard from "./ChordCard";
import autochorder from "../../services/pages/autochorder";
import {ScaleTypesEnum} from "../../models/music/scales";
import '../../style/components/autochorder/autochorder.scss';

export default function AutoChorder({viewModel}: {viewModel: IAutochorderPageViewModel}){
  const autoChorderPreset = viewModel.autoChorderPreset;
  const chordCardEls = createChordCardEls({autoChorderPreset});
  return <div className="autochorder">
    Test: {viewModel.test ? 'true' : 'false'}
    <div onClick={()=> doSomething()}>Do Something</div>
    <div className="chord-cards">
      {chordCardEls}
    </div>

   </div>;
}

function createChordCardEls({autoChorderPreset}: {autoChorderPreset: AutoChorderPreset}){
  return autoChorderPreset.chords.map((chord) => createChordCardEl({chord}));
}

function createChordCardEl({chord}: {chord: IChord}){
  return <ChordCard key={chord.id} chord={chord}/>;
}

const doSomething = () => autochorder.generateChordProgression({rootNote: 'c', scale: ScaleTypesEnum.majorIonian, octave: 4});