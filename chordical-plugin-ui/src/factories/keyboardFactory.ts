import ILayoutCoordinates from "../models/view/keyboard/ILayoutCoordinates";
import {IPianoKey} from "../models/view/keyboard/IPianoKey";
// import {keyboardImages, allPianoKeys} from "../config/config";
import {allPianoKeys} from "../models/view/keyboard/allPianoKeys";

// const minWidthPxToDrawAll88Keys = 813 * window.devicePixelRatio; //iphone x landscape width is 812
const minWidthPxToDrawAll88Keys = 1; //iphone x landscape width is 812

export function createKeyboardLayoutModel({width=0, height=0, userKeyboardHighestMidiNumber=21, userKeyboardLowestMidiNumber=108}: {width: number, height: number, userKeyboardHighestMidiNumber: number, userKeyboardLowestMidiNumber: number,}){
  const pianoKeys = createPianoKeys({userKeyboardHighestMidiNumber, userKeyboardLowestMidiNumber, width, minWidthPxToDrawAll88Keys});
  calculateAndSetKeyCoordinates({width, height, pianoKeys});
  calculateAndSetKeyLabelsCoordinates(pianoKeys);
  return pianoKeys;
}

const baseKeyboardImageSource = "https://d29h8r0xu3kanz.cloudfront.net/images/birds-eye-keyboard/keys2";
export const keyboardImages = {
  gImageSource: `${baseKeyboardImageSource}/key-g.png`,
  aImageSource: `${baseKeyboardImageSource}/key-a.png`,
  cAndFImageSource: `${baseKeyboardImageSource}/key-c-f.png`,
  dImageSource: `${baseKeyboardImageSource}/key-d.png`,
  eAndBImageSource: `${baseKeyboardImageSource}/key-e.png`,
  blackKeyImageSource: `${baseKeyboardImageSource}/key-sharp-flat.png`,
  a0ImageSource: `${baseKeyboardImageSource}/key-a0.png`,
  c8ImageSource: `${baseKeyboardImageSource}/key-c8.png`,
};
// export async function createImageElementsAndWaitForThemToLoad({pianoKeys}: {pianoKeys: IPianoKey[]}){
//   //first we need to download our piano key images (in parallel), so that we can assign the appropriate key image to each pianoKey
//   const {gImage, aImage, blackKeyImage, cAndFImage, dImage, eAndBImage, a0image, c8image} = await createAndLoadPianoKeyImages();
//   //set the image property of each IPianoKey (used by canvas components)
//   setPianoKeyImages({pianoKeys, gImage, aImage, blackKeyImage, cAndFImage, dImage, eAndBImage, a0image, c8image});
// }
//
// function setPianoKeyImages({pianoKeys, gImage, aImage, blackKeyImage, cAndFImage, dImage, eAndBImage, a0image, c8image}:{pianoKeys: IPianoKey[], gImage:HTMLImageElement, aImage:HTMLImageElement, blackKeyImage:HTMLImageElement, cAndFImage:HTMLImageElement, dImage:HTMLImageElement, eAndBImage:HTMLImageElement, a0image:HTMLImageElement, c8image:HTMLImageElement} ){
//   for(let pianoKey of pianoKeys){
//     const {noteName, midiNumber} = pianoKey;
//     if(noteName === "a"){
//       pianoKey.image = midiNumber === 21 ? a0image : aImage;
//     } else if(noteName === "b" || noteName === "e"){
//       pianoKey.image = eAndBImage;
//     } else if(noteName === "d"){
//       pianoKey.image = dImage;
//     } else if(noteName === "c" || noteName === "f"){
//       pianoKey.image = midiNumber === 108 ? c8image : cAndFImage;
//     } else if(noteName === "g"){
//       pianoKey.image = gImage;
//     } else {
//       pianoKey.image = blackKeyImage;
//     }
//   }
// }
//
// async function createAndLoadPianoKeyImages(){
//   const {gImageSource, a0ImageSource, aImageSource, blackKeyImageSource, c8ImageSource, cAndFImageSource, dImageSource, eAndBImageSource} = keyboardImages;
//   //download the images in parallel and await for them all to resolve with their HTMLImageElement values.
//   const [ gImage, aImage, cAndFImage, dImage, eAndBImage, blackKeyImage, a0image, c8image ] = await Promise.all([
//     createImageWithPromisifiedOnLoad(gImageSource),
//     createImageWithPromisifiedOnLoad(aImageSource),
//     createImageWithPromisifiedOnLoad(cAndFImageSource),
//     createImageWithPromisifiedOnLoad(dImageSource),
//     createImageWithPromisifiedOnLoad(eAndBImageSource),
//     createImageWithPromisifiedOnLoad(blackKeyImageSource),
//     createImageWithPromisifiedOnLoad(a0ImageSource),
//     createImageWithPromisifiedOnLoad(c8ImageSource),
//   ]);
//
//   return {gImage, aImage, cAndFImage, dImage, eAndBImage, blackKeyImage, a0image, c8image};
// }

/**
 * Allows you to create an image and await it's load and error functions, rather than to have to deal with the
 * "image.onload = () => {}" and "image.onload = () => {}" callback.
 * Instead, we can use await, so that the image is not returned until load has completed (or error).
 * This helps simplify loading multiple images in parallel.
 * @param imageSource
 */
// async function createImageWithPromisifiedOnLoad(imageSource: string){
//   return new Promise<HTMLImageElement>((resolve, reject)=>{
//     const image = new Image();
//     image.onload = () => { resolve(image); } ;
//     image.onerror = reject;
//     image.src = imageSource;
//   });
// }

const keyRatios = {
  blackKeyHeightPercent: .669, //how far down the black key reaches
  blackKeyWidthPercent: .64, //how wide compared to a white key.
  blackKeyStartXPercentFromWhiteKeyA: .2, //percent from the right of the white key
  blackKeyStartXPercentFromWhiteKeyC: .41,
  blackKeyStartXPercentFromWhiteKeyD: .25,
  blackKeyStartXPercentFromWhiteKeyF: .45,
  blackKeyStartXPercentFromWhiteKeyG: .315,
};

const keyLabelStyle = {
  whiteKey: {
    marginTopPercent: .69,
    marginLeftPercent: .1,
    marginRightPercent: .1,
    marginBottomPercent: .02,
  },
  blackKey: {
    marginTopPercent: .5,
    marginLeftPercent: .1,
    marginRightPercent: .1,
    marginBottomPercent: .1,
  }
};

function calculateAndSetKeyLabelsCoordinates(pianoKeys: IPianoKey[]){
  pianoKeys.forEach(p => calculateAndSetKeyLabelCoordinates(p));
}

function calculateAndSetKeyLabelCoordinates(pianoKey: IPianoKey){
  const labelStyle = pianoKey.keyColor === 'white' ? keyLabelStyle.whiteKey : keyLabelStyle.blackKey;
  const {marginLeftPercent, marginRightPercent, marginBottomPercent, marginTopPercent} = labelStyle;
  const {width: keyWidth, height: keyHeight, topLeft: {x: keyTopLeftX, y: keyTopLeftY}} = pianoKey.coordinates;
  const width = keyWidth - (keyWidth * marginRightPercent) - (keyWidth * marginLeftPercent);
  const height = keyHeight - (keyHeight * marginTopPercent) - (keyHeight * marginBottomPercent);
  const startY = keyTopLeftY + (keyHeight * marginTopPercent);
  const startX = keyTopLeftX + (keyWidth * marginLeftPercent);
  pianoKey.keyLabelCoordinates = calculateLayoutCoordinates({width, height, startX, startY});
}

function calculateAndSetKeyCoordinates({width=0, height=0, pianoKeys=[]} : {width: number, height: number, pianoKeys: IPianoKey[]}){
  const whiteKeys = pianoKeys.filter(k => k.keyColor === 'white');
  const numberOfWhiteKeys = whiteKeys.length;
  const whiteKeyWidth = width / numberOfWhiteKeys;

  let whiteKeyCount = 0; //since the white keys are placed right next to each other, we need to track the white key count so we can calculate the start x coordinate for the key.
  let nextAsharpStartX = 0;
  let nextCsharpStartX = 0;
  let nextDsharpStartX = 0;
  let nextFsharpStartX = 0;
  let nextGsharpStartX = 0;

  let blackKeyHeight = height * keyRatios.blackKeyHeightPercent;
  let blackKeyWidth = whiteKeyWidth * keyRatios.blackKeyWidthPercent;

  for(let pianoKey of pianoKeys){
    if(pianoKey.keyColor === 'white'){ //white key
      const startX = whiteKeyCount * whiteKeyWidth;
      pianoKey.coordinates = calculateLayoutCoordinates({width: whiteKeyWidth, height, startX, startY: 0});
      ++whiteKeyCount;

      switch(pianoKey.noteName){
        case "a":
          nextAsharpStartX = pianoKey.coordinates.topRight.x  - (whiteKeyWidth  * keyRatios.blackKeyStartXPercentFromWhiteKeyA); break;
        case "c":
          nextCsharpStartX = pianoKey.coordinates.topRight.x  - (whiteKeyWidth  * keyRatios.blackKeyStartXPercentFromWhiteKeyC); break;
        case "d":
          nextDsharpStartX =  pianoKey.coordinates.topRight.x  - (whiteKeyWidth  * keyRatios.blackKeyStartXPercentFromWhiteKeyD); break;
        case "f":
          nextFsharpStartX =  pianoKey.coordinates.topRight.x  - (whiteKeyWidth  * keyRatios.blackKeyStartXPercentFromWhiteKeyF); break;
        case "g":
          nextGsharpStartX =  pianoKey.coordinates.topRight.x  - (whiteKeyWidth  * keyRatios.blackKeyStartXPercentFromWhiteKeyG); break;
      }
    }else{ //black key
      let blackKeyStartX = 0;
      switch(pianoKey.noteName){
        case "a#":
          blackKeyStartX = nextAsharpStartX; break;
        case "c#":
          blackKeyStartX = nextCsharpStartX; break;
        case "d#":
          blackKeyStartX = nextDsharpStartX; break;
        case "f#":
          blackKeyStartX = nextFsharpStartX; break;
        case "g#":
          blackKeyStartX = nextGsharpStartX; break;
      }
      pianoKey.coordinates = calculateLayoutCoordinates({width: blackKeyWidth, height: blackKeyHeight, startX: blackKeyStartX, startY: 0});
    }
  }
}


/**
 * Helper function used to create LayoutCoordinates.
 * LayoutCoordinates include topLeft, topRight, bottomLeft, etc, which are useful when painting the canvas.
 * @param width - width of the item to create coordinates for
 * @param height - height of the item to create coordinates for
 * @param startX - start x position of the item to create coordinates for
 * @param startY - start y position of the item to create coordinates for.
 */
function calculateLayoutCoordinates({width=0, height=0, startX=0, startY=0}): ILayoutCoordinates{
  const topLeft= {x: startX, y: startY};
  const topRight = {x: topLeft.x + width, y: startY};
  const bottomLeft = {x: startX, y: startY + height};
  const bottomRight = {x: bottomLeft.x + width, y: startY + height};
  return { topLeft, topRight, bottomLeft, bottomRight, width, height};
}

function createPianoKeys({userKeyboardHighestMidiNumber, userKeyboardLowestMidiNumber, width, minWidthPxToDrawAll88Keys,}: {userKeyboardHighestMidiNumber: number, userKeyboardLowestMidiNumber: number, width: number, minWidthPxToDrawAll88Keys: number}){
  const shouldNotDrawAll88Keys = width < minWidthPxToDrawAll88Keys;
  const pianoKeys: IPianoKey[] = [];
  for (const [_, partialPianoKey] of Object.entries(allPianoKeys)){
    const pianoKey = partialPianoKey as IPianoKey;
    if(shouldNotDrawAll88Keys && (pianoKey.midiNumber < userKeyboardLowestMidiNumber || pianoKey.midiNumber > userKeyboardHighestMidiNumber) ){ continue; }
    pianoKey.isOnUsersKeyboard = pianoKey.midiNumber >= userKeyboardLowestMidiNumber && pianoKey.midiNumber <= userKeyboardHighestMidiNumber;
    if(pianoKey){
      pianoKeys.push(pianoKey);
    }
  }

  return pianoKeys;
}