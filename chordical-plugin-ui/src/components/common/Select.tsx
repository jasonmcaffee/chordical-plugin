import React, {useState} from 'react';
import {ISelectOption} from "../../models/view/common/ISelectOption";
import '../../style/components/common/select.scss';
import {FontAwesomeIcon} from "@fortawesome/react-fontawesome";
import {faChevronDown, faChevronUp} from "@fortawesome/free-solid-svg-icons";
import Button from "./Button";

export default function Select<TValueType>({options, onChange, currentlySelectedOption, label, }: {options: ISelectOption<TValueType>[], onChange: (option: ISelectOption<TValueType>) => void, currentlySelectedOption?: ISelectOption<TValueType>, label?: string}) {
  const [isOptionsVisible, setIsOptionsVisible] = useState(false);
  const onChangeIntercepted = (option: ISelectOption<TValueType>) => { setIsOptionsVisible(false); onChange(option); };
  const optionEls = createOptionEls(options, onChangeIntercepted, currentlySelectedOption);
  const optionsEl = isOptionsVisible ? <div className="options-container"><div className="options">{optionEls}</div></div> : null;
  const key = `${currentlySelectedOption?.value}`;
  const labelEl = label ? <div className="label">{label}</div> : null;
  const backgroundClickEl = isOptionsVisible ? <div className={`background-click`} onClick={() => setIsOptionsVisible(false)}></div> : null;
  const arrowIcon = isOptionsVisible ? faChevronUp : faChevronDown;
  return <div key={key} className="select" onClick={ () => setIsOptionsVisible(!isOptionsVisible)}>
    {backgroundClickEl}
    {labelEl}
    <div className="selected-and-arrow">
      <div key={key} className="selected">{currentlySelectedOption?.label}</div>
      <FontAwesomeIcon className="arrow" icon={arrowIcon}/>
    </div>
    {optionsEl}
  </div>;
}

function createOptionEls<TValueType>(options: ISelectOption<TValueType>[], onChange: (option: ISelectOption<TValueType>) => void, currentlySelectedOption?: ISelectOption<TValueType>){
  return options.map(o => createOptionEl(o, onChange, currentlySelectedOption));
}

function createOptionEl<TValueType>(option: ISelectOption<TValueType>, onChange: (option: ISelectOption<TValueType>) => void, currentlySelectedOption?: ISelectOption<TValueType>){
  return <div className={`option ${option.className ? option.className : ''}`} onClick={() => onChange(option)} >
    {option.label}
  </div>;
}