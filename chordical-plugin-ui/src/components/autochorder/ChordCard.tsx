import React from 'react';
import {IChord} from "../../models/music/IChord";
import '../../style/components/autochorder/chord-card.scss';

export default function ChordCard({chord}: {chord: IChord}){
  return <div className="chord-card">
    <div className="">
      <div className="label">{chord.label}</div>
    </div>
   </div>;
}