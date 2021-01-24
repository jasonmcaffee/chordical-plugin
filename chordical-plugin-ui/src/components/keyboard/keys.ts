import {IPianoKey} from "../../models/view/keyboard/IPianoKey";

const style = {
  sheetMusicNoteHighlights:{
    leftHandGradientStartColor: 'rgba(113,202,237,0.5)',
    leftHandGradientEndColor: 'rgba(42,176,237,0.5)',
    rightHandGradientStartColor: 'rgba(223,229,110,0.5)',
    rightHandGradientEndColor: 'rgba(242,242,43,0.5)',
  },
  playerNoteHighlights: {
    startColor: 'rgba(64,150,238,0.6)',
    endColor: 'rgba(64,150,238,0.9)',
  },
  noteNameLabel:{
    textColor: 'rgba(218,227,237,1)',
    font: 'Arial',
    textAlign: 'center',
    textBaseline: 'middle',
    fontSizePxToKeyWidthRatioModifier: 1,
  },
  sticker:{
    textColor: 'rgba(218,227,237,1)',
    font: 'Arial',
    fontSizePxToKeyWidthRatioModifier: 1.5,
    textAlign: 'center',
    marginTopPercent: .07,
    marginBottomPercent: .07,
  },
  notOnUserKeyboard:{
    color: `rgba(121,130,132,0.4)`,
  },
};

export function drawNoteNameLabels(pianoKeys: IPianoKey[], ctx: CanvasRenderingContext2D){
  pianoKeys.forEach(p => drawNoteNameLabel(p, ctx));
}

export function drawNoteNameLabel(pianoKey: IPianoKey, ctx: CanvasRenderingContext2D){
  const {topLeft: {x: topLeftX, y: topLeftY}, width, height} = pianoKey.keyLabelCoordinates;
  if(pianoKey.keyColor === "white"){
    const {textColor, font, fontSizePxToKeyWidthRatioModifier, textBaseline, textAlign} = style.noteNameLabel;
    const fontSize = width * fontSizePxToKeyWidthRatioModifier;
    ctx.fillStyle = textColor;
    ctx.font = `${fontSize}px ${font}`;
    ctx.textAlign = textAlign as CanvasTextAlign;
    ctx.textBaseline = textBaseline as CanvasTextBaseline;
    const text = pianoKey.noteName.toUpperCase();
    ctx.fillText(text, topLeftX + width / 2, topLeftY + height / 2);
  }
}

function drawKeySticker(pianoKey: IPianoKey, ctx: CanvasRenderingContext2D){
  const {topLeft: {x: topLeftX, y: topLeftY}, bottomRight: {y: bottomRightY}, width, height} = pianoKey.keyLabelCoordinates;
  //draw sticker
  ctx.fillStyle = `rgba(122,188,255,1)`;
  const stickerCornerRadius = 5;
  roundedRectangle(ctx, topLeftX, topLeftY, width, height, stickerCornerRadius);
  ctx.fill();

  //white key shows both finger number and key label. black key just shows finger number.
  const fontSizeDivisor = pianoKey.keyColor === 'white' ? 2 : 1;

  //draw text for fingering
  const {textColor, textAlign, font, fontSizePxToKeyWidthRatioModifier, marginTopPercent, marginBottomPercent} = style.sticker;
  const fontSize = width / fontSizeDivisor * fontSizePxToKeyWidthRatioModifier;
  ctx.fillStyle = textColor;
  ctx.font = `${fontSize}px ${font}`;
  ctx.textAlign = textAlign as CanvasTextAlign;
  ctx.textBaseline = "top";
  const fingeringText = "";
  const marginTopPx = height * marginTopPercent;

  if(pianoKey.keyColor === 'white'){
    ctx.fillText(fingeringText, topLeftX + width / 2, topLeftY + marginTopPx);
  }else{ //center the
    ctx.textBaseline = "middle";
    ctx.fillText(fingeringText, topLeftX + width / 2, topLeftY + height / 2);
  }

  if(pianoKey.keyColor === 'white'){
    //draw text for letter
    ctx.textBaseline = "bottom";
    const noteText = pianoKey.noteName.toUpperCase();
    const marginBottomPx = height * marginBottomPercent;
    ctx.fillText(noteText, topLeftX + width / 2, bottomRightY - marginBottomPx);
  }
}

export function drawKeys(pianoKeys: IPianoKey[], ctx: CanvasRenderingContext2D){
  pianoKeys.forEach(p => drawKey(p, ctx));
}

function drawKey(pianoKey: IPianoKey, ctx: CanvasRenderingContext2D){
  const {topLeft: {x, y}, width, height} = pianoKey.coordinates;
  if(pianoKey.image){
    ctx.drawImage(pianoKey.image, x, y, width, height);
  }else{
    ctx.fillStyle = pianoKey.keyColor;
    ctx.fillRect(x, y, width, height);
  }

  // if(!pianoKey.isOnUsersKeyboard){
  //   ctx.fillStyle = style.notOnUserKeyboard.color;
  //   ctx.fillRect(x, y, width, height);
  // }
}

export function drawKeysHighlights(keysCurrentlyPressed: IPianoKey[], ctx: CanvasRenderingContext2D, isPlayerNotes: boolean){
  keysCurrentlyPressed.forEach(k => drawKeyHighlight(k, ctx, isPlayerNotes));
}

function drawKeyHighlight(keyCurrentlyPressed: IPianoKey, ctx: CanvasRenderingContext2D, isPlayerNote: boolean){
  const {topLeft: {x: topX, y: topY}, bottomRight: {x: bottomRightX, y: bottomRightY}, width, height} = keyCurrentlyPressed.coordinates;

  //decide key highlight color for left hand vs right hand.
  let startColor = style.playerNoteHighlights.startColor;
  let endColor = style.playerNoteHighlights.endColor;
  if(!isPlayerNote){
    if(keyCurrentlyPressed.hand === 'left'){
      startColor = style.sheetMusicNoteHighlights.leftHandGradientStartColor;
      endColor = style.sheetMusicNoteHighlights.leftHandGradientEndColor;
    }else{
      startColor = style.sheetMusicNoteHighlights.rightHandGradientStartColor;
      endColor = style.sheetMusicNoteHighlights.rightHandGradientEndColor;
    }
  }

  //create a vertical gradient
  const gradient = ctx.createLinearGradient(topX, topY, bottomRightX, bottomRightY); //horizontal gradient by only having a difference in x
  gradient.addColorStop(0, startColor);
  gradient.addColorStop(1, endColor);

  ctx.fillStyle = gradient;
  ctx.fillRect(topX, topY, width, height);
}

function roundedRectangle(ctx: CanvasRenderingContext2D, x: number, y: number, width: number, height: number, radius: number, ) {
  ctx.beginPath();
  ctx.moveTo(x + radius, y);
  ctx.lineTo(x + width - radius, y);
  ctx.quadraticCurveTo(x + width, y, x + width, y + radius);
  ctx.lineTo(x + width, y + height - radius);
  ctx.quadraticCurveTo(x + width, y + height, x + width - radius, y + height);
  ctx.lineTo(x + radius, y + height);
  ctx.quadraticCurveTo(x, y + height, x, y + height - radius);
  ctx.lineTo(x, y + radius);
  ctx.quadraticCurveTo(x, y, x + radius, y);
  ctx.closePath();
}