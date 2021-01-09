import AutoChorderPreset from "./AutoChorderPreset";
import {ISelectOption} from "../common/ISelectOption";
import {NoteSymbolTypes} from "../../music/INote";
import {ScaleTypesEnum} from "../../music/scales";

export default interface IAutochorderPageViewModel{
  test: boolean;
  autoChorderPreset: AutoChorderPreset;
  noteSelectOptions: ISelectOption<NoteSymbolTypes>[];
  scaleSelectOptions: ISelectOption<ScaleTypesEnum>[];
}