#ifndef CDUNGEON_H
#define CDUNGEON_H

#include "CFloor.h"

#include <vector>

class CDungeon
{
public:
	static CDungeon* instance;

	static CDungeon* Instance()
	{
		if (instance == nullptr)
			instance = new CDungeon();
		return instance;
	}

private:

	CDungeon();
	bool AddNewFloor(int _floorNum, CFloor* _newFloor);


	int currentFloor;

	std::vector<CFloor*> floors;

};

#endif