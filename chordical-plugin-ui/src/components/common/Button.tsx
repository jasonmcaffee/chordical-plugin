import React from 'react';
import '../../style/components/common/button.scss';
export default function Button({label, onClick}: {label: string, onClick?: ()=>void}) {
  return <div className="button" onClick={onClick}>
    {label}
  </div>;
}