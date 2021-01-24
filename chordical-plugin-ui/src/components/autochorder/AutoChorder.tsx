import React, {useEffect, useState} from 'react';
import IAutochorderPageViewModel from "../../models/view/autochorder/IAutochorderPageViewModel";
import {IChord} from "../../models/music/IChord";
import ChordCard from "./ChordCard";
import autochorder from "../../services/pages/autochorder";
import {ScaleTypesEnum} from "../../models/music/scales";
import '../../style/components/autochorder/autochorder.scss';
import ISlot from "../../models/view/autochorder/ISlot";
import SlotCard from "./SlotCard";
import Select from "../common/Select";
import {noteSelectOptions} from "../../services/music/notes";
import Button from "../common/Button";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faPlus } from "@fortawesome/free-solid-svg-icons";
import ChordRow from "./ChordRow";

export default function AutoChorder({viewModel}: {viewModel: IAutochorderPageViewModel}){
  const slotCardEls = createSlotEls({viewModel});
  const {autoChorderPreset, scaleSelectOptions, octaveOptions} = viewModel;
  const autoChorderClassName = viewModel.chordView === "rows" ? "chord-rows" : "";
  return <div className={`autochorder ${autoChorderClassName}`}>
    <div className="options">
      <div className="key">
        <Select currentlySelectedOption={noteSelectOptions.find(n => n.value === autoChorderPreset.selectedKey.rootNote)} options={noteSelectOptions} onChange={(option) => autochorder.changeKey({key: {rootNote: option.value, scale: viewModel.autoChorderPreset.selectedKey.scale}}) }/>
        <Select currentlySelectedOption={scaleSelectOptions.find(s => s.value === autoChorderPreset.selectedKey.scale)} options={scaleSelectOptions} onChange={(option) => autochorder.changeKey({key: {rootNote: autoChorderPreset.selectedKey.rootNote, scale: option.value}})}/>
      </div>
      <div className="min-max-octave">
        <div className="label">Random Min & Max Octave</div>
        <Select options={octaveOptions} onChange={o => autochorder.changeRandomizationMinOctave({newOctave: o.value})} currentlySelectedOption={octaveOptions.find(o => o.value === autoChorderPreset.randomizationMinOctave)}/>
        <Select options={octaveOptions} onChange={o => autochorder.changeRandomizationMaxOctave({newOctave: o.value})} currentlySelectedOption={octaveOptions.find(o => o.value === autoChorderPreset.randomizationMaxOctave)}/>
      </div>
    </div>

    <div className="slot-cards">
      {slotCardEls}
    </div>
   </div>;
}

function createChordCardEl({slot, chord, viewModel}: {slot: ISlot, chord: IChord, viewModel: IAutochorderPageViewModel}){
  return <ChordCard key={chord.id} slot={slot} chord={chord} viewModel={viewModel}/>;
}

function createChordRowEl({slot, chord, viewModel}: {slot: ISlot, chord: IChord, viewModel: IAutochorderPageViewModel}){
  return <ChordRow key={chord.id} slot={slot} chord={chord} viewModel={viewModel}/>;
}

function createSlotEls({viewModel}: {viewModel: IAutochorderPageViewModel}){
  return viewModel.autoChorderPreset.slots.map(slot => createSlotEl({slot, viewModel}));
}

function createSlotEl({slot, viewModel}: {slot: ISlot, viewModel: IAutochorderPageViewModel}){
  let chordEl = createAddChordEl();
  if(viewModel.chordView === "rows" && slot.content){
    chordEl = createChordRowEl({slot, chord: slot.content, viewModel})
  }else if(viewModel.chordView === "cards" && slot.content){
    chordEl =  createChordCardEl({slot, chord: slot.content, viewModel});
  }
  return <SlotCard slot={slot}> {chordEl}</SlotCard>;
}

function createAddChordEl(){
  return <div className={"add-chord"}>
    <Button onClick={() => autochorder.addChord()}>
      <FontAwesomeIcon icon={faPlus}/>
    </Button>
  </div>
}

const doSomething = () => autochorder.generateChordProgression({rootNote: 'c', scale: ScaleTypesEnum.majorIonian, octave: 4});