import React from 'react';
import ReactDOM from 'react-dom';
import '../../style/components/autochorder/slot-card.scss';
import autochorder from '../../services/pages/autochorder';
import ISlot from "../../models/view/autochorder/ISlot";

export default function SlotCard({slot, children}: {slot: ISlot, children?: React.ReactNode}){
  return <div className="slot-card"> slot
    {children}
  </div>;
}