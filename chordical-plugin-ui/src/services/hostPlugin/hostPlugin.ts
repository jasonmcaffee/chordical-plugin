import {subscribeToHostPluginEvents} from "../eventBus/hostPlugin/toHostPluginEventBus";
import {
  appStateLoaded,
  midiNotePlayed,
  midiNoteStopped,
  testMessage
} from "../eventBus/hostPlugin/fromHostPluginEventBus";

import {HostPluginEventTypes} from "../eventBus/hostPlugin/HostPluginEventTypes";

class HostPlugin {
  constructor(){
    subscribeToHostPluginEvents((message: HostPluginEventTypes)=>{
      switch(message.type){
        case "messageToHost":
          this.sendMessageToHost(message.data); break;
      }
    });

    function handleHashChange(event: HashChangeEvent){
      // const hash = window.location.hash; <-- this will be outdated causing duplicate messages. eg when 2 midi note played messages are sent at the same time.
      const hash = event.newURL;
      const hashMessageIndicator = "message=";
      if(hash.indexOf(hashMessageIndicator) >= 0){
        //@ts-ignore
        // document.getElementById("page").innerHTML += `<br/> hash new Url ${event.newURL}`;
        const messageString = hash.substr(hash.indexOf(hashMessageIndicator) + hashMessageIndicator.length);
        const messageObj = convertMessageStringToObject(messageString);
        handleMessageFromPluginHost(messageObj);
      }
    }
    window.addEventListener('hashchange', handleHashChange);
  }
  destroy(){}
  sendMessageToHost(data: string){
    console.log(`send message to host`, data);
    window.location.href = `projucer://${data}`;
    // window.location.href = `https://toNativeHost/${data}`;
  }
}

function handleMessageFromPluginHost(message:any){
  switch(message.type){
    case "testMessage":
      testMessage(message.data);
      break;
    case "midiNotePlayed":
      //@ts-ignore
      // document.getElementById("page").innerHTML += "<br/> ------ " + JSON.stringify(message);
      midiNotePlayed(message.data);
      break;
    case "midiNoteStopped":
      midiNoteStopped(message.data);
      break;
    case "appStateLoaded":
      //@ts-ignore
      // document.getElementById('page').innerHTML += "decoded message: " + message.data.state + "<br/>";
      appStateLoaded(message.data.state);
      break;
    case "unknown":
      break;
  }
}


function convertMessageStringToObject(messageString: string){
  const decodedMessageString = decodeURIComponent(messageString);
  let messageObj;
  try{
    messageObj = JSON.parse(decodedMessageString);
  }catch(e){
    console.error(`cant parse hash message sent from plugin host`);
    messageObj = {type: "unknown", data: decodedMessageString};
    //@ts-ignore
    // document.getElementById('page').innerHTML += "unknown message: " + messageString;
  }
  return messageObj;
}


const hostPlugin = new HostPlugin();
export default hostPlugin;