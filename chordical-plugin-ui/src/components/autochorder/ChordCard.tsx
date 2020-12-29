import React from 'react';
import {IChord} from "../../models/music/IChord";

export default function ChordCard({chord}: {chord: IChord}){
  return <div className="chord-card">Chord Card {chord.label}</div>;
}