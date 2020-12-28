
//scale name to note index array
//For a major scale, the indexes would be [0, 2, 4, 5, 7, 9, 11], where 0 is c, 2 is d, 4 is e, 5 is f, etc
//this would be a tad bit better as represented by w, w, h, w ... but this works
export const scaleNoteIndexes: ScaleNoteIndexes = {
  'chromatic':[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11],
  'majorIonian':[0, 2, 4, 5, 7, 9, 11],
  'naturalMinorAeolian':[0, 2, 3, 5, 7, 8, 10], // 																												<-- c major starting at a
  'majorPentatonic':[0, 2, 4, 7, 9], //c major pentatonic is: C, D, E, G, A
  'minorPentatonic':[0, 3, 5, 7, 10], //a minor pentatonic is: A, C, D, E, G
  'dorian':[0, 2, 3, 5, 7, 9, 10], //d dorian is: D, E, F, G, A, B, C 												<-- c major starting at d
  'greekDorianPhrygian':[0, 1, 3, 5, 7, 8, 10], //e phrygian is: E, F, G, A, B, C, D 											<-- c major starting at e
  'lydian':[0, 2, 4, 6, 7, 9, 11], //f lydian is: F, G, A, B, C, D, E 												<-c major starting at f
  'mixolydian':[0, 2, 4, 5, 7, 9, 10], //g mixolydian is: G, A, B, C, D, E, F  <--c major starting at g
  'locrian':[0, 1, 3, 5, 6, 8, 10], //b locrian is: B, C, D, E, F, G, A
  'ascendingMelodicMinor':[0, 2, 3, 5, 7, 9, 11], //a ascending melodic minor is: A, B, C, D, E, F#, G#
  'hexatonicBlues':[0, 3, 5, 6, 7, 10], //c hexatonic blues is: C, D#, F, F#, G, A#
  'heptatonicBlues':[0, 2, 3, 5, 6, 9, 10], //c heptatonic blues is: C, D, Eb, F, Gb, A, Bb
  'nonatonicBlues':[0, 2, 3, 4, 5, 7, 9, 10 ], //c nonatonic blues is: C, D, D#, E, F, G, A, A#
  'acoustic':[0, 2, 4, 6, 7, 9, 10], //c acoustic is: C, D, E, F#, G, A, A#
  'algerian':[0, 2, 3, 6, 7, 8, 11], //c algerian is: C, D, D#, F#, G, G#, B,
  'altered':[0, 1, 3, 4, 6, 8, 10], //c altered is: C, C#, D#, E, F#, G#, A#
  'augmented':[0, 3, 4, 7, 8, 11], //c augmented is: C, D#, E, G, G#, B
  'bebopMajor': [0, 2, 4, 5, 7, 8, 9, 11], //c bebop major is: C, D, E, F, G, G#, A, B
  'bebopDominant':[0, 2, 4, 5, 7, 9, 10, 11], //c bebop dominate is: C, D, E, F, G, A, A#, B
  'bebopMinor': [0, 2, 3, 5, 7, 9, 10, 11], //c bebop minor is: C, D, D#, F, G, A, A#, B
  'doubleHarmonic':[0, 1, 4, 5, 7, 8, 11], //c double harmonic is: C, C#, E, F, G, G#, B
  'enigmatic':[0, 1, 4, 6, 8, 10, 11], //c enigmatic is: C, C#, E, F#, G#, A#, B
  'eulerFokker':[0, 2, 5, 7, 10, 11],//c euler fokker is: C, D, F, G, A#, B
  'flamenco':[0, 1, 4, 5, 7, 8, 11], //c flamenco is: C, C#, E, F, G, G#, B
  'gypsy':[0, 2, 3, 6, 7, 8, 10], //c gypsy is: C, D, D#, F#, G, G#, A#
  'halfDiminished':[0, 2, 3, 5, 6, 8, 10], //c half diminished is: C, D, D#, F, F#, G#, A#
  'harmonicMajor':[0, 2, 4, 5, 7, 8, 11], //c harmonic major is: C, D, E, F, G, G#, B
  'harmonicMinor':[0, 2, 3, 5, 7, 8, 11], //c harmonic minor is: C, D D#, F, G, G#, B
  'hirajoshi':[0, 4, 6, 7, 11], //c hirajoshi is: C, E, F#, G, B
  'hungarianGypsy':[0, 2, 3, 6, 7, 8, 11], //c hungarian gypsy is: C, D, D#, F#, G, G#, B
  'hungarianMinor':[0, 2, 3, 6, 7, 8, 11], //c is: C, D, D#, F#, G, G#, B
  'in':[0, 1, 5, 7, 8], //d is: D, D#, G, A. A#
  'insen':[0, 1, 5, 7, 10], //c is: C, C#, F, G, A#
  'iwato':[0, 1, 5, 6, 10], //c is: C, C#, F, F#, A#
  'lydianAugmented':[0, 2, 4, 6, 8, 9, 11], //c is: C, D, E, F#, G#, A, B
  'neapolitanMajor':[0, 1, 3, 5, 7, 9, 11], //c is: C, C#, D#, F, G, A, B
  'neapolitanMinor':[0, 1, 3, 5, 7, 8, 11], //c is: C, C#, D#, F, G, G#, B
  'persian':[0, 1, 4, 5, 6, 8, 11], //c is C, C#, E, F, F#, G#, B
  'phrygrianDominant':[0, 1, 4, 5, 7, 8, 10], //c is C, C#, E, F, G, G#, A#
  'prometheus':[0, 2, 4, 6, 9, 10], //c is C, D, E, F#, A, A#
  'tritone':[0, 1, 4, 6, 7, 10], //c is C, C#, E, F#, G, A#
  'ukranianDorian':[0, 2, 3, 6, 7, 9, 10], //c is C, D, D#, F#, G, A, A#
  'yo':[0, 3, 5, 7, 10], //d is D, F, G, A, C
};

export type ScaleNoteIndexes = {
  [key in keyof typeof ScaleTypesEnum] : number[]
}


export enum ScaleTypesEnum{
  chromatic = "chromatic",
  majorIonian = "majorIonian",
  naturalMinorAeolian = "naturalMinorAeolian",
  majorPentatonic = "majorPentatonic",
  minorPentatonic = "minorPentatonic",
  dorian = "dorian",
  greekDorianPhrygian = "greekDorianPhrygian",
  lydian = "lydian",
  mixolydian = "mixolydian",
  locrian = "locrian",
  ascendingMelodicMinor = "ascendingMelodicMinor",
  hexatonicBlues = "hexatonicBlues",
  heptatonicBlues = "heptatonicBlues",
  nonatonicBlues = "nonatonicBlues",
  acoustic = "acoustic",
  algerian = "algerian",
  altered = "altered",
  augmented = "augmented",
  bebopMajor = "bebopMajor",
  bebopDominant = "bebopDominant",
  bebopMinor = "bebopMinor",
  doubleHarmonic = "doubleHarmonic",
  enigmatic = "enigmatic",
  eulerFokker = "eulerFokker",
  flamenco = "flamenco",
  gypsy = "gypsy",
  halfDiminished = "halfDiminished",
  harmonicMajor = "harmonicMajor",
  harmonicMinor = "harmonicMinor",
  hirajoshi = "hirajoshi",
  hungarianGypsy = "hungarianGypsy",
  hungarianMinor = "hungarianMinor",
  in = "in",
  insen = "insen",
  iwato = "iwato",
  lydianAugmented = "lydianAugmented",
  neapolitanMajor = "neapolitanMajor",
  neapolitanMinor = "neapolitanMinor",
  persian = "persian",
  phrygrianDominant = "phrygrianDominant",
  prometheus = "prometheus",
  tritone = "tritone",
  ukranianDorian = "ukranianDorian",
  yo = "yo",
}

