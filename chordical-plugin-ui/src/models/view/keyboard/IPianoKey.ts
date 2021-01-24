import ILayoutCoordinates from "./ILayoutCoordinates";

type NoteName = 'c' | 'c#' | 'd' | 'd#' | 'e' | 'f' | 'f#' | 'g' | 'g#' | 'a' | 'a#' | 'b';

// enum NoteName { 'c', 'c#', 'd', 'd#', 'e', 'f', 'f#', 'g', 'g#','a', 'a#', 'b', }
type KeyColor = 'white' | 'black';
export interface IPianoKey {
  noteName: NoteName;
  octave: number;
  midiNumber: number;
  keyColor: KeyColor;
  imageSource: string;
  coordinates: ILayoutCoordinates;
  keyLabelCoordinates: ILayoutCoordinates;
  image?: HTMLImageElement;
  hand?: 'left' | 'right'; //used when drawing highlights. this property will be set by evaluating the ss INote's track index.
  isOnUsersKeyboard: boolean; //when users have a 60 key keyboard, 28 keys (88 total) will be displayed that don't exist on the users keyboard, and we want to indicate that they aren't there.
}
