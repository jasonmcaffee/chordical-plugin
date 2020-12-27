import React, {ReactDOM} from "react";
import AutoChorderPage from '../../components/autochorder/AutoChorderPage';
import router, {IRouteConfig} from "../router";

const config: IRouteConfig = {
  path: 'autochorder',
  async handle(render: (component: React.FunctionComponentElement<any>) => void){
    const page = React.createElement(AutoChorderPage, {}, null);
    render(page);
  }
};

router.registerRoute(config);