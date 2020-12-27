import {createEventBusAndHook} from "../eventBus/common";
import IAutochorderPageViewModel from "../../models/view/autochorder/IAutochorderPageViewModel";
const initialViewModel: IAutochorderPageViewModel = { test: false };

export const {subscribe: subscribeToViewModelChange, emitMessage: viewModelChanged, hook: useAutochorderPageViewModel} = createEventBusAndHook<IAutochorderPageViewModel>(initialViewModel);

class Autochorder{
  constructor(){
  }
  loadViewModel(){
    setTimeout(()=> {
      viewModelChanged({...initialViewModel, test: true});
    }, 1000);
  }
}

const autochorder = new Autochorder();
export default autochorder;
