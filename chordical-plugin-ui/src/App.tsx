import React, {useState, useEffect} from 'react';
import logo from './logo.svg';
import './App.css';
import './services/hostPlugin/hostPlugin';
import './style/app.scss';
import {requestToPlayMidiNotes, requestToStopMidiNotes, sendMessageToHost, webAppLoaded} from "./services/eventBus/hostPlugin/toHostPluginEventBus";
import {subscribeToFromHostPluginEvents} from "./services/eventBus/hostPlugin/fromHostPluginEventBus";
import {FromHostPluginMessageTypes} from "./services/eventBus/hostPlugin/HostPluginEventTypes";

function notifyUserOfError(e:Error){
  alert(e.message); //alert doesnt work in plugin
}

function convertMessageStringToObject(messageString: string){
  let messageObj;
  try{
    messageObj = JSON.parse(messageString);
  }catch(e){
    notifyUserOfError(e);
  }
  return messageObj;
}

function App() {
  const [message, setMessage] = useState("");
  useEffect(()=>{
    //tell the host that the app has loaded
    webAppLoaded("hi");

    const unsubscribeFromHostPluginEvents = subscribeToFromHostPluginEvents((m: FromHostPluginMessageTypes) => {
      switch(m.type){
        case "testMessage":
          setMessage(m.data);
          break;
      }
    });

    return () => {
      unsubscribeFromHostPluginEvents();
    };
  }, []);

  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <div className="play-notes-button" onMouseDown={handleOnMouseDown } onMouseUp={handleOnMouseUp} >Play Notes</div>
        <div>{message}</div>
      </header>
    </div>
  );
}


function handleOnMouseDown(){
  requestToPlayMidiNotes([{midiNote: 44, velocity: 100}, {midiNote: 66, velocity: 99}]);
}

function handleOnMouseUp(){
  requestToStopMidiNotes([{midiNote: 44, velocity: 0}, {midiNote: 66, velocity: 0}]);
}

export default App;
