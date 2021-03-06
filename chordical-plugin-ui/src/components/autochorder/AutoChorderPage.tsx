import React from 'react';
import '../../style/components/autochorder/autochorder-page.scss';
import {useAutochorderPageViewModel} from "../../services/pages/autochorder";
import AutoChorder from "./AutoChorder";

export default function AutoChorderPage(){
  const viewModel = useAutochorderPageViewModel();
  return <div className="autochorder-page">
    <AutoChorder viewModel={viewModel}/>
  </div>;
}