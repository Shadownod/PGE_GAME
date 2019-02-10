//#include "CDungeon.h"
//#include "CFloor.h"
//
//CDungeon* CDungeon::instance;
//
//CDungeon:: CDungeon()
//	: currentFloor(-1)
//{
//	
//}
//
//CDungeon::~CDungeon()
//{
//}
//
//bool CDungeon::AddNewFloor(int _floorNum, CFloor* _newFloor)
//{
//	if (_floorNum == floors.size() + 1)
//	{
//		floors.push_back(_newFloor);
//		return true;
//	}
//
//	if (floors[_floorNum] == nullptr)
//	{
//		floors[_floorNum] = _newFloor;
//		return true;
//	}
//
//	return false;
//}