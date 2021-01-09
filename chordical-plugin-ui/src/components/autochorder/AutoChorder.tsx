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
import {subscribeToFromHostPluginEvents} from "../../services/eventBus/hostPlugin/fromHostPluginEventBus";

export default function AutoChorder({viewModel}: {viewModel: IAutochorderPageViewModel}){
  const slotCardEls = createSlotEls({viewModel});
  const l: string[] = [];
  // const [messages, setMessages] = useState(l);
  // useEffect(()=>{
  //   return subscribeToFromHostPluginEvents((message)=>{
  //     const m = "<div>" + JSON.stringify(message) + "</div>";
  //     setMessages([m, ...messages]);
  //   });
  // });
  return <div className="autochorder">
    <div onClick={() => autochorder.saveAppState() }>Save {viewModel.test ? 'true' : 'false'}</div>
    <div onClick={() => autochorder.getAppState() }>Get App State</div>
    <div onClick={()=> doSomething()}>Do Something</div>
    <div className="slot-cards">
      {slotCardEls}
    </div>
    {/*<div>*/}
      {/*{messages}*/}
    {/*</div>*/}
   </div>;
}

function createChordCardEl({chord, viewModel}: {chord: IChord, viewModel: IAutochorderPageViewModel}){
  return <ChordCard key={chord.id} chord={chord} viewModel={viewModel}/>;
}

function createSlotEls({viewModel}: {viewModel: IAutochorderPageViewModel}){
  return viewModel.autoChorderPreset.slots.map(slot => createSlotEl({slot, viewModel}));
}

function createSlotEl({slot, viewModel}: {slot: ISlot, viewModel: IAutochorderPageViewModel}){
  const chordEl = slot.content ? createChordCardEl({chord: slot.content, viewModel}) : null;
  return <SlotCard slot={slot}> {chordEl}</SlotCard>;
}

const doSomething = () => autochorder.generateChordProgression({rootNote: 'c', scale: ScaleTypesEnum.majorIonian, octave: 4});