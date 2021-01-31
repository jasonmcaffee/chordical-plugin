import AutoChorderPreset from "./AutoChorderPreset";
import {ISelectOption} from "../common/ISelectOption";
import {ScaleTypesEnum} from "../../music/scales";
import {INoteSelectOption} from "../../../services/music/notes";

export default interface IAutochorderPageViewModel{
  version: string; //for state retention checking.
  windowHeight: number;
  windowWidth: number;
  test: boolean;
  autoChorderPreset: AutoChorderPreset;
  noteSelectOptions: INoteSelectOption[]; //options sorted by whether they are in the key.
  scaleSelectOptions: ISelectOption<ScaleTypesEnum>[];
  octaveOptions: ISelectOption<number>[];
  chordView: "cards" | "rows";
}