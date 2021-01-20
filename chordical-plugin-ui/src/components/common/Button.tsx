import React, {ReactNode, useState} from 'react';
import '../../style/components/common/button.scss';
export default function Button({label, onClick, children, className}: {label?: string, onClick?: ()=>void, children?: ReactNode, className?: string},) {
  const [pressedClassName, setPressedClassName] = useState("");
  return <div className={`button ${pressedClassName} ${className}`} onClick={onClick} onMouseDown={()=> setPressedClassName("pressed")} onMouseUp={() => setPressedClassName("")}>
    {label || children}
  </div>;
}