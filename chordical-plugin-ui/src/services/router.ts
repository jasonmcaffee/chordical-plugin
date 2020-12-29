import React from 'react';
import * as ReactDOM from "react-dom";

const defaultPage = 'autochorder';
class Router{
  configs:  IRouteConfig[] = [];
  constructor() {
    console.error(`router`);
    window.addEventListener('hashchange', ()=> this.handleHashChange());
  }
  handleHashChange(){
    const hash = window.location.hash.replace('#', '') || defaultPage;
    console.error(`hash changed: ${hash}`);
    const config = this.configs.find((c) => c.path === hash);
    if(config){
      config.handle(this.render);
    }else{
      console.error(`no config for hash: ${hash}`);
    }
  }
  registerRoute(config: IRouteConfig){
    this.configs.push(config);
  }
  render(component: React.FunctionComponentElement<any>){
    ReactDOM.render(component, document.getElementById('page'));
  }
  renderInitial(){
    this.handleHashChange();
  }
}

export interface IRouteConfig {
  path: string,
  handle: (render: (component: React.FunctionComponentElement<any>) => void) => void,
}

const router = new Router();
export default router;