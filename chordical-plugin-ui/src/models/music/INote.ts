export default interface INote{
  noteSymbol: NoteSymbolTypes,
  octave: number,
  midi: number,
}

export type NoteSymbolTypes = 'c' | 'c#' | 'd' | 'd#' | 'e' | 'f' | 'f#' | 'g' | 'g#' | 'a' | 'a#' | 'b';