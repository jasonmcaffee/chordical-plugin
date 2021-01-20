import React, {ReactNode} from "react";
import '../../style/components/common/modal.scss';
import Button from "./Button";
import {FontAwesomeIcon} from "@fortawesome/react-fontawesome";
import {faCross} from "@fortawesome/free-solid-svg-icons";

export default function Modal({children, onClose}: {children: ReactNode, onClose: () => void}) {
  return (
    <div className="modal">
      <div className="content">
        <Button className={"close-button"} onClick={onClose}><FontAwesomeIcon icon={faCross}/></Button>
        {children}
      </div>
    </div>
  );
}