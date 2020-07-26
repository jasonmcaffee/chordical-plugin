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

    function handleHashChange(){
      const hash = window.location.hash;
      const hashMessageIndicator = "message=";
      if(hash.indexOf(hashMessageIndicator) >= 0){
        const messageString = hash.substr(hash.indexOf(hashMessageIndicator) + hashMessageIndicator.length);
        const messageObj = convertMessageStringToObject(messageString);
      }
    }
    window.addEventListener('hashchange', handleHashChange);
  }
  destroy(){}
  sendMessageToHost(data: string){
    console.log(`send message to host`, data);
    window.location.href = `projucer://${data}`;
  }
}

function convertMessageStringToObject(messageString: string){
  let messageObj;
  try{
    messageObj = JSON.parse(messageString);
  }catch(e){
    console.error(`cant parse hash message sent from plugin host`);
  }
  return messageObj;
}


const hostPlugin = new HostPlugin();
export default hostPlugin;