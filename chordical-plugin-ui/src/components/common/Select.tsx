import React, {useState} from 'react';
import {ISelectOption} from "../../models/view/common/ISelectOption";
import '../../style/components/common/select.scss';

export default function Select<TValueType>({options, onChange, currentlySelectedOption, label, }: {options: ISelectOption<TValueType>[], onChange: (option: ISelectOption<TValueType>) => void, currentlySelectedOption?: ISelectOption<TValueType>, label?: string}) {
  const [isOptionsVisible, setIsOptionsVisible] = useState(false);
  const onChangeIntercepted = (option: ISelectOption<TValueType>) => { setIsOptionsVisible(false); onChange(option); };
  const optionEls = createOptionEls(options, onChangeIntercepted, currentlySelectedOption);
  const optionsEl = isOptionsVisible ? <div className="options">{optionEls}</div> : null;
  const key = `${currentlySelectedOption?.value}`;
  const labelEl = label ? <div className="label">{label}</div> : null;
  return <div key={key} className="select">
    {labelEl}
    <div key={key} className="selected" onClick={ () => setIsOptionsVisible(!isOptionsVisible)}>{currentlySelectedOption?.label}</div>
    {optionsEl}
  </div>;
}

function createOptionEls<TValueType>(options: ISelectOption<TValueType>[], onChange: (option: ISelectOption<TValueType>) => void, currentlySelectedOption?: ISelectOption<TValueType>){
  return options.map(o => createOptionEl(o, onChange, currentlySelectedOption));
}

function createOptionEl<TValueType>(option: ISelectOption<TValueType>, onChange: (option: ISelectOption<TValueType>) => void, currentlySelectedOption?: ISelectOption<TValueType>){
  return <div className="option" onClick={() => onChange(option)} >
    {option.label}
  </div>;
}