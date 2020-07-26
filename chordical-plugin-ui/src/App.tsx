import React, {useState, useEffect} from 'react';
import logo from './logo.svg';
import './App.css';
import './services/hostPlugin/hostPlugin';
import './style/app.scss';
import {sendMessageToHost, webAppLoaded} from "./services/eventBus/hostPlugin/hostPluginEventBus";

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
  const [hashParam, setHashParam] = useState("");
  const [message, setMessage] = useState("");
  useEffect(()=>{
    function handleHashChange(){
      setMessage(`hash change!` + window.location.hash);
      setHashParam(window.location.hash);
      const hash = window.location.hash;
      const hashMessageIndicator = "message=";
      if(hash.indexOf(hashMessageIndicator) >= 0){
        const messageString = hash.substr(hash.indexOf(hashMessageIndicator) + hashMessageIndicator.length);
        const messageObj = convertMessageStringToObject(messageString);
        setMessage("deserialized: " + messageObj?.typeId);
        // setMessage("messageString: " + messageString);
      }
    }
    window.addEventListener('hashchange', handleHashChange);
    const unsubscribeFromHashChange = () => window.removeEventListener('hashchange', handleHashChange);

    webAppLoaded("hi");

    return () => {
      unsubscribeFromHashChange();
    };
  }, []);

  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
          <div className="app" onClick={sendJsonToHost }> hash: {hashParam}</div>
          <div>{message}</div>
      </header>
    </div>
  );
}

function sendJsonToHost(){
  const message = {
    type: "test",
    data: {prop1: "jason", z: { a: 99 }},
  };
  const messageString = JSON.stringify(message);
  sendMessageToHost(messageString);
}

export default App;
