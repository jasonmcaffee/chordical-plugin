import React, {useState, useEffect} from 'react';
import logo from './logo.svg';
import './App.css';
import './services/hostPlugin/hostPlugin';
import './style/app.scss';
import {sendMessageToHost} from "./services/eventBus/hostPlugin/hostPluginEventBus";

function App() {
  const [hashParam, setHashParam] = useState("");
  useEffect(()=>{
    function handleHashChange(){
      console.log(`hash change!`, window.location.hash);
      setHashParam(window.location.hash);
    }
    window.addEventListener('hashchange', handleHashChange);
    const unsubscribeFromHashChange = () => window.removeEventListener('hashchange', handleHashChange);

    return () => {
      unsubscribeFromHashChange();
    };
  }, []);

  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
          <div className="app" onClick={() => sendMessageToHost('button-clicked') }>{window.location.href} {window.location.hash} hello {hashParam}</div>
      </header>
    </div>
  );
}

export default App;
