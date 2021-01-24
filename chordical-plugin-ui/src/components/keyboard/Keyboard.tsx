import React, {useRef, useEffect,} from "react";
import '../../style/components/keyboard/keyboard.scss';
import {createKeyboardLayoutModel,} from "../../factories/keyboardFactory";

import INote from "../../models/music/INote";
import {IPianoKey} from "../../models/view/keyboard/IPianoKey";
import {drawNoteNameLabels, drawKeys, drawKeysHighlights} from "./keys";

interface IKeyboardProps {
}

interface ICanvases {
  whiteKeysLabelsAndImagesCanvas: HTMLCanvasElement;
  whiteKeysHighlightsCanvas: HTMLCanvasElement;
  playerNotesWhiteKeysHighlightsCanvas: HTMLCanvasElement;
  blackKeysLabelsAndImagesCanvas: HTMLCanvasElement;
  blackKeysHighlightsCanvas: HTMLCanvasElement;
  playerNotesBlackKeysHighlightsCanvas: HTMLCanvasElement;
}

type CanvasRef = React.MutableRefObject<HTMLCanvasElement>;

/**
 * Keyboard uses several canvases (for performance) to paint the fretboard, strings, frets, and finger markers for the notes currently being played.
 *
 * Listens for rxjs note events emitted by the notesEventWorker and playerNotesPlayer in order to have the keyboard ui reflect player notes, sheet music notes, currently selected notes, etc.
 *
 * The canvases are stacked, in order, on top of each other.
 * We use 6 canvases to simplify things and increase performance.
 * 1. white key images canvas for drawing the actual image of the key.  This won't need to be rerendered on updates to notes being played by sheet music or the player.
 * 2. white key highlights to place a gradient rectangle over the key image so we can indicate it's being played.  By having this as the second layer, we don't need to worry about covering part of the black key image with the highlight (white key shape is not a rectangle, so we'd need to do some calculations to trace it's shape)
 * 3. player white key highlights for player notes. we don't want player note highlights to get erased when sheet music notes change.
 * 4-6. same as 1-3, but for black keys.
 */
export default function Keyboard({}: IKeyboardProps) {
  const userKeyboardHighestMidiNumber = 21;
  const userKeyboardLowestMidiNumber = 108;
  //create refs. use new canvas to avoid having to constantly check for nulls.
  const whiteKeysLabelsAndImagesCanvasRef = useRef<HTMLCanvasElement>(document.createElement('canvas'));
  const whiteKeysHighlightsCanvasRef = useRef<HTMLCanvasElement>(document.createElement('canvas'));
  const playerNotesWhiteKeysHighlightsCanvasRef = useRef<HTMLCanvasElement>(document.createElement('canvas'));
  const blackKeysLabelsAndImagesCanvasRef = useRef<HTMLCanvasElement>(document.createElement('canvas'));
  const blackKeysHighlightsCanvasRef = useRef<HTMLCanvasElement>(document.createElement('canvas'));
  const playerNotesBlackKeysHighlightsCanvasRef = useRef<HTMLCanvasElement>(document.createElement('canvas'));

  let pianoKeys: IPianoKey[] = [];
  //on first render, size and draw the canvases.  listen for sheetMusicNotesCurrentlyBeingPlayedChanged rxjs events and repaint the finger markers.
  useEffect(()=>{
    //keep a reference to the notes currently being played, as we will need to repaint them when screen resize occurs.
    let sheetMusicNotesCurrentlyBeingPlayed: INote[] = [];
    let notesCurrentlySelected: INote[] = [];
    //function for initial render and rerender
    function calculateSizesAndRender(){
      const canvases = getCanvasesFromRefs({whiteKeysLabelsAndImagesCanvasRef, whiteKeysHighlightsCanvasRef, playerNotesWhiteKeysHighlightsCanvasRef, blackKeysLabelsAndImagesCanvasRef, blackKeysHighlightsCanvasRef, playerNotesBlackKeysHighlightsCanvasRef});
      pianoKeys = setCanvasSizeCreatePianoKeysAndRender(canvases, sheetMusicNotesCurrentlyBeingPlayed, notesCurrentlySelected, userKeyboardHighestMidiNumber, userKeyboardLowestMidiNumber);
    }
    //initial render
    calculateSizesAndRender();
    //rerender on window size changes
    const unsubscribeFromResizeAndOrientationChangeEvents = listenForWindowResizeAndOrientationChangeEvents(calculateSizesAndRender);
    //listen for player notes
    const notesCurrentlyBeingPlayedByUser = new Set<number>();
    // const unsubscribeFromNotesEvents = subscribeToNotesEvents((e) => {
    //   const canvases = getCanvasesFromRefs({whiteKeysLabelsAndImagesCanvasRef, whiteKeysHighlightsCanvasRef, playerNotesWhiteKeysHighlightsCanvasRef, blackKeysLabelsAndImagesCanvasRef, blackKeysHighlightsCanvasRef, playerNotesBlackKeysHighlightsCanvasRef});
    //   ({sheetMusicNotesCurrentlyBeingPlayed, notesCurrentlySelected} = handleNoteEvent(e, notesCurrentlyBeingPlayedByUser, pianoKeys, sheetMusicNotesCurrentlyBeingPlayed, notesCurrentlySelected, canvases));
    // });

    //return a function for unsubscribing.
    return () =>{
      unsubscribeFromResizeAndOrientationChangeEvents();
      // unsubscribeFromNotesEvents();
    };
  }, []);

  const isTouchDevice = ('ontouchstart' in window);

  const activeMouseDownMidiNotes = new Set<number>();
  const onMouseDown = !isTouchDevice ? (e: React.MouseEvent<HTMLDivElement>) => handleMouseDown(e, pianoKeys, playerNotesWhiteKeysHighlightsCanvasRef.current, activeMouseDownMidiNotes) : undefined;
  const onMouseUp = !isTouchDevice ? () => handleMouseUp(playerNotesWhiteKeysHighlightsCanvasRef.current, pianoKeys, activeMouseDownMidiNotes) : undefined;


  return (
    <div className="keyboard" onMouseDown={onMouseDown} onMouseUp={onMouseUp} onMouseOut={onMouseUp} onMouseLeave={onMouseUp}>
      <canvas ref={whiteKeysLabelsAndImagesCanvasRef} />
      <canvas ref={whiteKeysHighlightsCanvasRef} />
      <canvas ref={playerNotesWhiteKeysHighlightsCanvasRef}/>

      <canvas ref={blackKeysLabelsAndImagesCanvasRef} />
      <canvas ref={blackKeysHighlightsCanvasRef} />
      <canvas ref={playerNotesBlackKeysHighlightsCanvasRef}/>
    </div>
  );
}

function getCanvasesFromRefs({whiteKeysLabelsAndImagesCanvasRef, whiteKeysHighlightsCanvasRef, playerNotesWhiteKeysHighlightsCanvasRef, blackKeysLabelsAndImagesCanvasRef, blackKeysHighlightsCanvasRef, playerNotesBlackKeysHighlightsCanvasRef, } :{whiteKeysLabelsAndImagesCanvasRef: CanvasRef, whiteKeysHighlightsCanvasRef: CanvasRef, playerNotesWhiteKeysHighlightsCanvasRef: CanvasRef, blackKeysLabelsAndImagesCanvasRef: CanvasRef, blackKeysHighlightsCanvasRef: CanvasRef, playerNotesBlackKeysHighlightsCanvasRef: CanvasRef, }){
  return {
    whiteKeysLabelsAndImagesCanvas: whiteKeysLabelsAndImagesCanvasRef.current,
    whiteKeysHighlightsCanvas: whiteKeysHighlightsCanvasRef.current,
    playerNotesWhiteKeysHighlightsCanvas: playerNotesWhiteKeysHighlightsCanvasRef.current,
    blackKeysLabelsAndImagesCanvas: blackKeysLabelsAndImagesCanvasRef.current,
    blackKeysHighlightsCanvas: blackKeysHighlightsCanvasRef.current,
    playerNotesBlackKeysHighlightsCanvas: playerNotesBlackKeysHighlightsCanvasRef.current
  };
}

function setCanvasSizeCreatePianoKeysAndRender(canvases: ICanvases, sheetMusicNotesCurrentlyBeingPlayed: INote[], notesCurrentlySelected: INote[], userKeyboardHighestMidiNumber: number, userKeyboardLowestMidiNumber: number){
  const {whiteKeysLabelsAndImagesCanvas, whiteKeysHighlightsCanvas, blackKeysLabelsAndImagesCanvas, blackKeysHighlightsCanvas, playerNotesWhiteKeysHighlightsCanvas, playerNotesBlackKeysHighlightsCanvas,} = canvases;
  setCanvasSizesToMatchCSS([whiteKeysLabelsAndImagesCanvas, whiteKeysHighlightsCanvas, blackKeysLabelsAndImagesCanvas, blackKeysHighlightsCanvas, playerNotesWhiteKeysHighlightsCanvas, playerNotesBlackKeysHighlightsCanvas, ]);
  const pianoKeys = createKeyboardLayoutModel({width: whiteKeysLabelsAndImagesCanvas.width, height: whiteKeysLabelsAndImagesCanvas.height, userKeyboardHighestMidiNumber, userKeyboardLowestMidiNumber});
  drawKeyAndLabelAndHighlightCanvases(whiteKeysHighlightsCanvas, whiteKeysLabelsAndImagesCanvas, blackKeysHighlightsCanvas, blackKeysLabelsAndImagesCanvas, sheetMusicNotesCurrentlyBeingPlayed, notesCurrentlySelected, pianoKeys);
  return pianoKeys;
}

function determineKeyThatWasPressedByClientXandY(clientX: number, clientY: number, canvas: HTMLCanvasElement, pianoKeys: IPianoKey[]){
  const {x, y} = getRelativeXandY(clientX, clientY, canvas);
  return findPianoKeyAtXandYcoordinates(x, y, pianoKeys);
}

function getRelativeXandY(clientX: number, clientY: number, canvas: HTMLCanvasElement){
  const rectangle = canvas.getBoundingClientRect();
  const {left, top,} = rectangle;

  const x = clientX - left;
  const y = clientY - top;
  return {x, y};
}

/**
 * Hit detection is made simpler by evaluating whether black key was hit before evaluating white key.
 */
function findPianoKeyAtXandYcoordinates(x: number, y: number, pianoKeys: IPianoKey[]){
  const hitBlackKey = pianoKeys.filter(p => p.keyColor === 'black').find(p => doesXandYintersectWithKey(x, y, p));
  if(hitBlackKey){ return hitBlackKey; }
  return pianoKeys.filter(p => p.keyColor === 'white').find(p => doesXandYintersectWithKey(x, y, p));
}

/**
 * Divide by window.devicePixelRatio because it is used in setCanvasSizes (to fix blur) and makes the keys think that the width of the canvas is 2048, where mouse/touch events think its 1024
 */
function doesXandYintersectWithKey(x: number, y: number, pianoKey: IPianoKey){
  const {topLeft: {x: topLeftX, y: topLeftY}, bottomRight: {x: bottomRightX, y: bottomRightY}} = pianoKey.coordinates;
  return (x > topLeftX / window.devicePixelRatio && x < bottomRightX / window.devicePixelRatio && y > topLeftY / window.devicePixelRatio && y < bottomRightY / window.devicePixelRatio);
}

function drawPlayerNoteHighlights(notesCurrentlyBeingPlayedByUser: Set<number>, pianoKeys: IPianoKey[], playerNotesWhiteKeysHighlightsCanvas: HTMLCanvasElement, playerNotesBlackKeysHighlightsCanvas: HTMLCanvasElement){
  const whiteKeyContext = playerNotesWhiteKeysHighlightsCanvas.getContext('2d');
  const blackKeyContext = playerNotesBlackKeysHighlightsCanvas.getContext('2d');
  if(!whiteKeyContext || !blackKeyContext) { return; }
  //clear everything out
  whiteKeyContext.clearRect(0, 0, playerNotesWhiteKeysHighlightsCanvas.width, playerNotesWhiteKeysHighlightsCanvas.height);
  blackKeyContext.clearRect(0, 0, playerNotesBlackKeysHighlightsCanvas.width, playerNotesBlackKeysHighlightsCanvas.height);
  //repaint
  const pianoKeysBeingPlayedByUser = findPianoKeysCurrentlyBeingPlayedByMidiNumber(notesCurrentlyBeingPlayedByUser, pianoKeys);
  const {whiteKeys, blackKeys} = separateWhiteAndBlackKeys(pianoKeysBeingPlayedByUser);
  drawKeysHighlights(whiteKeys, whiteKeyContext, true);
  drawKeysHighlights(blackKeys, blackKeyContext, true);
}


function drawKeyAndLabelAndHighlightCanvases(whiteKeysHighlightsCanvas: HTMLCanvasElement, whiteKeysImagesCanvas: HTMLCanvasElement, blackKeysHighlightsCanvas: HTMLCanvasElement, blackKeysImagesCanvas: HTMLCanvasElement, sheetMusicNotesCurrentlyBeingPlayed: INote[], notesCurrentlySelected: INote[], pianoKeys: IPianoKey[]){
  const {whiteKeys, blackKeys} = separateWhiteAndBlackKeys(pianoKeys);

  //draw temp white and black keys while image loads:
  createContextAndDrawKeysAndLabels(whiteKeysImagesCanvas, whiteKeys);
  createContextAndDrawKeysAndLabels(blackKeysImagesCanvas, blackKeys);
  //once images have loaded, rerender.
  // createImageElementsAndWaitForThemToLoad({pianoKeys}).then(()=>{
  //   createContextAndDrawKeysAndLabels(whiteKeysImagesCanvas, whiteKeys);
  //   createContextAndDrawKeysAndLabels(blackKeysImagesCanvas, blackKeys);
  // });

  drawWhiteAndBlackKeysHightlightsCanvas(whiteKeysHighlightsCanvas, blackKeysHighlightsCanvas, sheetMusicNotesCurrentlyBeingPlayed, pianoKeys);
}


function listenForWindowResizeAndOrientationChangeEvents(handle: ()=> void){
  window.addEventListener('resize', handle);
  window.addEventListener("orientationchange", handle);
  return () => {
    window.removeEventListener('resize', handle);
    window.removeEventListener('orientationchange', handle);
  };
}

/**
 * The canvas element has width and height properties that we are required to set.  It is easiest to control size via css.
 * This function determines the css derived width and height, and sets the canvas element's width & height properties accordingly.
 * @param canvases
 */
function setCanvasSizesToMatchCSS(canvases: HTMLCanvasElement[]){
  //control canvas size entirely through css.
  for(let canvas of canvases){
    setCanvasSizeToMatchCSS(canvas);
  }
}

/**
 * Canvas uses 2 distinct sets of height and width.
 * The first, which is set by attribute only, is the pixel width.
 * The second, which is set by css, is the display width.
 * We want these to match, but leave control of styling in the css world.
 * https://stackoverflow.com/questions/10214873/make-canvas-as-wide-and-as-high-as-parent
 *
 * We also need to factor in window.devicePixelRatio, so that our canvas isn't blurry.
 */
function setCanvasSizeToMatchCSS(canvas: HTMLCanvasElement){
  canvas.width  = canvas.offsetWidth * window.devicePixelRatio; //https://stackoverflow.com/questions/24332639/why-context2d-backingstorepixelratio-deprecated
  canvas.height = canvas.offsetHeight * window.devicePixelRatio;
  return {height: canvas.height, width: canvas.width};
}

function createContextAndDrawKeysAndLabels(backgroundCanvas: HTMLCanvasElement, pianoKeys: IPianoKey[]){
  const ctx = backgroundCanvas.getContext('2d');
  if(!ctx) { return; }
  drawKeys(pianoKeys, ctx);
  drawNoteNameLabels(pianoKeys, ctx);
}

function drawWhiteAndBlackKeysHightlightsCanvas(whiteKeysHighlightsCanvas: HTMLCanvasElement, blackKeysHighlightsCanvas: HTMLCanvasElement, sheetMusicNotesCurrentlyBeingPlayed: INote[], pianoKeys: IPianoKey[]){
  const whiteKeysCtx = whiteKeysHighlightsCanvas.getContext('2d');
  const blackKeysCtx = blackKeysHighlightsCanvas.getContext('2d');
  if(!whiteKeysCtx){return;}
  if(!blackKeysCtx){return;}
  //clear the canvas first.
  whiteKeysCtx.clearRect(0, 0, whiteKeysHighlightsCanvas.width, whiteKeysHighlightsCanvas.height);
  blackKeysCtx.clearRect(0, 0, blackKeysHighlightsCanvas.width, blackKeysHighlightsCanvas.height);

  //paint the canvas.
  const pianoKeysForSheetMusicNotesCurrentlyBeingPlayed = findPianoKeysCurrentlyBeingPlayed(sheetMusicNotesCurrentlyBeingPlayed, pianoKeys);
  const {whiteKeys, blackKeys} = separateWhiteAndBlackKeys(pianoKeysForSheetMusicNotesCurrentlyBeingPlayed);

  drawKeysHighlights(whiteKeys, whiteKeysCtx, false);
  drawKeysHighlights(blackKeys, blackKeysCtx, false);
}

function separateWhiteAndBlackKeys(pianoKeys: IPianoKey[]){
  const whiteKeys: IPianoKey[] = [];
  const blackKeys: IPianoKey[] = [];
  for(let i = 0; i < pianoKeys.length; ++i){
    const pianoKey = pianoKeys[i];
    if(pianoKey.keyColor === 'white'){
      whiteKeys.push(pianoKey);
    }else{
      blackKeys.push(pianoKey);
    }
  }
  return {whiteKeys, blackKeys};
}

function findPianoKeysCurrentlyBeingPlayed(notesCurrentlyBeingPlayed: INote[], pianoKeys: IPianoKey[]){
  const result: IPianoKey[] = [];
  for(let i = 0; i < notesCurrentlyBeingPlayed.length; ++i){
    const note = notesCurrentlyBeingPlayed[i];
    const pianoKey = pianoKeys.find(p => p.midiNumber === note.midi);
    if(pianoKey){
      result.push(pianoKey);
    }
  }
  return result;
}

function findPianoKeysCurrentlyBeingPlayedByMidiNumber(midiNumbersCurrentlyBeingPlayed: Set<number>, pianoKeys: IPianoKey[]){
  const result: IPianoKey[] = [];
  const midiNoteArray = Array.from(midiNumbersCurrentlyBeingPlayed);
  for(let i = 0; i < midiNoteArray.length; ++i){
    const midiNote = midiNoteArray[i];
    const pianoKey = pianoKeys.find(p => p.midiNumber === midiNote);
    if(pianoKey){
      result.push(pianoKey);
    }
  }
  return result;
}

function handleMouseDown(e: React.MouseEvent<HTMLDivElement>, pianoKeys: IPianoKey[], playerNotesWhiteKeysHighlightsCanvas: HTMLCanvasElement, activeMouseDownMidiNumbers: Set<number>){
  const hitKey = determineKeyThatWasPressedByClientXandY(e.clientX, e.clientY, playerNotesWhiteKeysHighlightsCanvas, pianoKeys);
  if(hitKey){
    activeMouseDownMidiNumbers.add(hitKey.midiNumber);
    // uiKeyboardNotePressed(hitKey.midiNumber);
  }
}

function handleMouseUp(playerNotesWhiteKeysHighlightsCanvas: HTMLCanvasElement, pianoKeys: IPianoKey[], activeMouseDownMidiNumbers: Set<number>){
  const midiNotesBeingPlayed = Array.from(activeMouseDownMidiNumbers);
  activeMouseDownMidiNumbers.clear();
  // midiNotesBeingPlayed.forEach(midiNumber => uiKeyboardNoteReleased(midiNumber));
}

// function getNotesCurrentlyPlayedByUserFromActiveTouch(activeTouches: ITouchIdToMidiNoteHash){
//   const midiNumbers = new Set<number>();
//   for(const [_, value] of Object.entries(activeTouches)){
//     midiNumbers.add(value);
//   }
//   return midiNumbers;
// }


//
// function handleNoteEvent(e: NotesEventTypes, notesCurrentlyBeingPlayedByUser: Set<number>, pianoKeys: IPianoKey[], sheetMusicNotesCurrentlyBeingPlayed: INote[], notesCurrentlySelected: INote[], canvases: ICanvases){
//   const {playerNotesWhiteKeysHighlightsCanvas, playerNotesBlackKeysHighlightsCanvas, whiteKeysHighlightsCanvas, blackKeysHighlightsCanvas} = canvases;
//   switch(e.type){
//     case "playerNotePressed":
//       notesCurrentlyBeingPlayedByUser.add(e.midiNumber);
//       drawPlayerNoteHighlights(notesCurrentlyBeingPlayedByUser, pianoKeys, playerNotesWhiteKeysHighlightsCanvas, playerNotesBlackKeysHighlightsCanvas);
//       break;
//     case "playerNoteReleased":
//       notesCurrentlyBeingPlayedByUser.delete(e.midiNumber);
//       drawPlayerNoteHighlights(notesCurrentlyBeingPlayedByUser, pianoKeys, playerNotesWhiteKeysHighlightsCanvas, playerNotesBlackKeysHighlightsCanvas);
//       break;
//     case 'sheetMusicNotesCurrentlyBeingPlayedChanged':
//       sheetMusicNotesCurrentlyBeingPlayed = e.sheetMusicNotesCurrentlyBeingPlayed;
//       handleSheetMusicNotesCurrentlyBeingPlayedChanged(pianoKeys, sheetMusicNotesCurrentlyBeingPlayed, whiteKeysHighlightsCanvas, blackKeysHighlightsCanvas);
//       break;
//     case 'notesCurrentlySelectedChanged':
//       notesCurrentlySelected = e.notesCurrentlySelected;
//       handleNotesCurrentlySelectedChanged(pianoKeys, notesCurrentlySelected, whiteKeysHighlightsCanvas, blackKeysHighlightsCanvas);
//       break;
//   }
//
//   return {sheetMusicNotesCurrentlyBeingPlayed, notesCurrentlySelected};
// }
//
// function handleTouchStart(e: React.TouchEvent, pianoKeys: IPianoKey[], playerNotesWhiteKeysHighlightsCanvas: HTMLCanvasElement, touchNotesBeingPlayed: ITouchIdToMidiNoteHash){
//   for(let i = 0; i < e.changedTouches.length; ++i){
//     const changedTouch = e.changedTouches[i];
//     const hitKey = determineKeyThatWasPressedByClientXandY(changedTouch.clientX, changedTouch.clientY, playerNotesWhiteKeysHighlightsCanvas, pianoKeys);
//     if(hitKey){
//       clearAnyTouchesWithSameMidiNumber(touchNotesBeingPlayed, hitKey.midiNumber);
//       touchNotesBeingPlayed[changedTouch.identifier] = hitKey.midiNumber;
//       uiKeyboardNotePressed(hitKey.midiNumber);
//     }
//   }
// }
//
// function handleTouchMove(e: React.TouchEvent, pianoKeys: IPianoKey[], playerNotesWhiteKeysHighlightsCanvas: HTMLCanvasElement, touchNotesBeingPlayed: ITouchIdToMidiNoteHash){
//   for(let i = 0; i < e.changedTouches.length; ++i){
//     const changedTouch = e.changedTouches[i];
//     const hitKey = determineKeyThatWasPressedByClientXandY(changedTouch.clientX, changedTouch.clientY, playerNotesWhiteKeysHighlightsCanvas, pianoKeys);
//     if(hitKey){
//       //if the move still resides on the same key, don't do anything.
//       if(touchNotesBeingPlayed[changedTouch.identifier] === hitKey.midiNumber) { continue; }
//       //if we made it here then the move has gone from one key to another.  Stop playing the last midi number/previous key.
//       const lastMidiNumber = touchNotesBeingPlayed[changedTouch.identifier];
//       clearAnyTouchesWithSameMidiNumber(touchNotesBeingPlayed, lastMidiNumber);
//       //play the note that the move landed on.
//       touchNotesBeingPlayed[changedTouch.identifier] = hitKey.midiNumber;
//       uiKeyboardNotePressed(hitKey.midiNumber);
//     }
//   }
// }
//
// function handleTouchEnd(e: React.TouchEvent, pianoKeys: IPianoKey[], playerNotesWhiteKeysHighlightsCanvas: HTMLCanvasElement, touchNotesBeingPlayed: ITouchIdToMidiNoteHash){
//   for(let i = 0; i < e.changedTouches.length; ++i){
//     const changedTouch = e.changedTouches[i];
//     const midiNumber = touchNotesBeingPlayed[changedTouch.identifier];
//     clearAnyTouchesWithSameMidiNumber(touchNotesBeingPlayed, midiNumber);
//   }
// }
//
// function clearAnyTouchesWithSameMidiNumber(activeTouches: ITouchIdToMidiNoteHash, midiNumberParam: number){
//   for(const [touchId, midiNumber] of Object.entries(activeTouches)){
//     if(midiNumber === midiNumberParam){
//       uiKeyboardNoteReleased(midiNumber);
//       // @ts-ignore number key.
//       delete activeTouches[touchId];
//     }
//   }
// }
//


//
// function handleSheetMusicNotesCurrentlyBeingPlayedChanged(pianoKeys: IPianoKey[], sheetMusicNotesCurrentlyBeingPlayed: INote[], whiteKeysHighlightsCanvas: HTMLCanvasElement, blackKeysHighlightsCanvas: HTMLCanvasElement){
//   drawWhiteAndBlackKeysHightlightsCanvas(whiteKeysHighlightsCanvas, blackKeysHighlightsCanvas, sheetMusicNotesCurrentlyBeingPlayed, pianoKeys);
// }
//
// function handleNotesCurrentlySelectedChanged(pianoKeys: IPianoKey[], notesCurrentlySelected: INote[], whiteKeysHighlightsCanvas: HTMLCanvasElement, blackKeysHighlightsCanvas: HTMLCanvasElement){
//   drawWhiteAndBlackKeysHightlightsCanvas(whiteKeysHighlightsCanvas, blackKeysHighlightsCanvas, notesCurrentlySelected, pianoKeys);
// }