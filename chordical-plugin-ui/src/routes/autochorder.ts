import React, {ReactDOM} from "react";
import AutoChorderPage from '../components/autochorder/AutoChorderPage';
import router, {IRouteConfig} from "../services/router";
import autochorder from "../services/pages/autochorder";

const config: IRouteConfig = {
  path: 'autochorder',
  async handle(render: (component: React.FunctionComponentElement<any>) => void){
    autochorder.loadViewModel();
    const page = React.createElement(AutoChorderPage, {}, null);
    render(page);
  }
};

router.registerRoute(config);