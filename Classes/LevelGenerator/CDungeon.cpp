#include "CDungeon.h"

CDungeon::CDungeon()
{
	currentFloor = -1;
}

bool CDungeon::AddNewFloor(int _floorNum, CFloor* _newFloor)
{
	if (_floorNum >= floors.size)
		return false;

	if (floors[_floorNum] == nullptr)
	{
		floors[_floorNum] = _newFloor;
		return true;
	}

	if (_floorNum == floors.size + 1)
	{
		floors.push_back(_newFloor);
		return true;
	}
}