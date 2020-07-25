import {subscribeToHostPluginEvents} from "../eventBus/hostPlugin/hostPluginEventBus";
import {HostPluginEventTypes} from "../eventBus/hostPlugin/HostPluginEventTypes";

class HostPlugin {
  constructor(){
    subscribeToHostPluginEvents((message: HostPluginEventTypes)=>{
      switch(message.type){
        case "messageToHost":
          this.sendMessageToHost(message.data); break;
      }
    });
  }
  destroy(){

  }
  sendMessageToHost(data: string){
    console.log(`send message to host`, data);
    window.location.href = `projucer://${data}`;
  }
}

const hostPlugin = new HostPlugin();
export default hostPlugin;