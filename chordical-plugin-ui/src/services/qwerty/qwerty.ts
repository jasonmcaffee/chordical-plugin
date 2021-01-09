import {keyDown, keyUp} from '../eventBus/qwerty';
interface IQwertyKeyCode {
  key: string,
  code: number;
}
class Qwerty {
  pressedKeyCodes: IQwertyKeyCode[]=[];
  constructor() {
    document.addEventListener('keydown', this.handleKeyDown.bind(this));
    document.addEventListener('keyup', this.handleKeyUp.bind(this));
  }
  handleKeyDown({keyCode}: KeyboardEvent){
    const qwertyKeyCode = qwertyKeyCodes.find(qkc=>qkc.code === keyCode);
    if(!qwertyKeyCode){return;}
    const qwertyKeyCodeIndex = this.pressedKeyCodes.findIndex(qkc=>qkc.code === keyCode);
    if(qwertyKeyCodeIndex >= 0){ return console.log('keycode already pressed'); }
    console.log('handleKeyDown for ', qwertyKeyCode);
    this.pressedKeyCodes.push(qwertyKeyCode);
    keyDown({keyCode});
  }
  handleKeyUp({keyCode}: KeyboardEvent){
    const qwertyKeyCodeIndex = this.pressedKeyCodes.findIndex(qkc=>qkc.code === keyCode);
    if(qwertyKeyCodeIndex < 0){return;}
    const qwertyKeyCode = this.pressedKeyCodes[qwertyKeyCodeIndex];
    this.pressedKeyCodes.splice(qwertyKeyCodeIndex, 1);
    console.log('handleKeyUp for ', qwertyKeyCode);
    keyUp({keyCode});
  }
}

export const qwertyKeyCodes = [
  {key: '1', code: 49},
  {key: '2', code: 50},
  {key: '3', code: 51},
  {key: '4', code: 52},
  {key: '5', code: 53},
  {key: '6', code: 54},
  {key: '7', code: 55},
  {key: '8', code: 56},
  {key: '9', code: 57},
  {key: '0', code: 48},
  {key: '-', code: 189},
  {key: '=', code: 187},
  {key: 'delete', code: 8},

  {key: 'q', code: 81},
  {key: 'w', code: 87},
  {key: 'e', code: 69},
  {key: 'r', code: 82},
  {key: 't', code: 84},
  {key: 'y', code: 89},
  {key: 'u', code: 85},
  {key: 'i', code: 73},
  {key: 'o', code: 79},
  {key: 'p', code: 80},
  {key: '[', code: 219},
  {key: ']', code: 221},
  {key: '\\', code: 220},

  {key: 'a', code: 65},
  {key: 's', code: 83},
  {key: 'd', code: 68},
  {key: 'f', code: 70},
  {key: 'g', code: 71},
  {key: 'h', code: 72},
  {key: 'j', code: 74},
  {key: 'k', code: 75},
  {key: 'l', code: 76},
  {key: ';', code: 186},
  {key: "'", code: 222},
  {key: 'enter', code: 13},

  {key: 'z', code: 90},
  {key: 'x', code: 88},
  {key: 'c', code: 67},
  {key: 'v', code: 86},
  {key: 'b', code: 66},
  {key: 'n', code: 78},
  {key: 'm', code: 77},
  {key: ',', code: 188},
  {key: '.', code: 190},
  {key: '/', code: 191},
];

export const qwertyService = new Qwerty();