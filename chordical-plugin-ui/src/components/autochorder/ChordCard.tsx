import React from 'react';
import {IChord} from "../../models/music/IChord";
import '../../style/components/autochorder/chord-card.scss';
import autochorder from '../../services/pages/autochorder';

export default function ChordCard({chord}: {chord: IChord}){
  return <div className="chord-card">
    <div className="">
      <div className="label" onMouseDown={() => autochorder.playChord({chord})} onMouseUp={() => autochorder.stopChord({chord})}>{chord.label}</div>
    </div>
   </div>;
}