import React, {ReactNode, useState} from 'react';
import '../../style/components/common/button.scss';
export default function Button({label, onClick, children}: {label?: string, onClick?: ()=>void, children?: ReactNode},) {
  const [pressedClassName, setPressedClassName] = useState("");
  return <div className={`button ${pressedClassName}`} onClick={onClick} onMouseDown={()=> setPressedClassName("pressed")} onMouseUp={() => setPressedClassName("")}>
    {label || children}
  </div>;
}