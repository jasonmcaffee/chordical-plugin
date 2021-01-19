import React, {useEffect, useState} from 'react';
import IAutochorderPageViewModel from "../../models/view/autochorder/IAutochorderPageViewModel";
import AutoChorderPreset from "../../models/view/autochorder/AutoChorderPreset";
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

export default function AutoChorder({viewModel}: {viewModel: IAutochorderPageViewModel}){
  const slotCardEls = createSlotEls({viewModel});
  const {autoChorderPreset, scaleSelectOptions} = viewModel;
  return <div className="autochorder">
    <div className="options">
      <div className="key">
        <Select currentlySelectedOption={noteSelectOptions.find(n => n.value === autoChorderPreset.selectedKey.rootNote)} options={noteSelectOptions} onChange={(option) => autochorder.changeKey({key: {rootNote: option.value, scale: viewModel.autoChorderPreset.selectedKey.scale}}) }/>
        <Select currentlySelectedOption={scaleSelectOptions.find(s => s.value === autoChorderPreset.selectedKey.scale)} options={scaleSelectOptions} onChange={(option) => autochorder.changeKey({key: {rootNote: autoChorderPreset.selectedKey.rootNote, scale: option.value}})}/>
      </div>
    </div>

    <div className="slot-cards">
      {slotCardEls}
    </div>
   </div>;
}

function createChordCardEl({chord, viewModel}: {chord: IChord, viewModel: IAutochorderPageViewModel}){
  return <ChordCard key={chord.id} chord={chord} viewModel={viewModel}/>;
}

function createSlotEls({viewModel}: {viewModel: IAutochorderPageViewModel}){
  return viewModel.autoChorderPreset.slots.map(slot => createSlotEl({slot, viewModel}));
}

function createSlotEl({slot, viewModel}: {slot: ISlot, viewModel: IAutochorderPageViewModel}){
  const chordEl = slot.content ? createChordCardEl({chord: slot.content, viewModel}) : createAddChordEl();
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