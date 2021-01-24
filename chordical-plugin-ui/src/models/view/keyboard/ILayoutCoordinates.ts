import ICoordinate from "./ICoordinate";

export default interface ILayoutCoordinates{
  topLeft: ICoordinate;
  topRight: ICoordinate;
  bottomLeft: ICoordinate;
  bottomRight: ICoordinate;
  width: number;
  height: number;
}