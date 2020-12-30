import AutoChorderPreset from "./AutoChorderPreset";
import {ISelectOption} from "../common/ISelectOption";
import {NoteSymbolTypes} from "../../music/INote";

export default interface IAutochorderPageViewModel{
  test: boolean;
  autoChorderPreset: AutoChorderPreset;
  noteSelectOptions: ISelectOption<NoteSymbolTypes>[];
}