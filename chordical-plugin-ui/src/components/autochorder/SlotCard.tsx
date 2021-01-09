import React from 'react';
import '../../style/components/autochorder/slot-card.scss';
import ISlot from "../../models/view/autochorder/ISlot";

export default function SlotCard({slot, children}: {slot: ISlot, children?: React.ReactNode}){
  return <div className="slot-card">
    {children}
  </div>;
}