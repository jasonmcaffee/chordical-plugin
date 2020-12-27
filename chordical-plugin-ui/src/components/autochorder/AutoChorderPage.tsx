import React from 'react';
import '../../style/components/autochorder/autochorder-page.scss';
import {useAutochorderPageViewModel} from "../../services/pages/autochorder";

export default function AutoChorderPage(){
  const viewModel = useAutochorderPageViewModel();
  return <div className="autochorder-page">
    Autochorder Page {viewModel.test ? 'true': 'false'}
  </div>;
}