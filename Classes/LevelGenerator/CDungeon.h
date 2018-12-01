#ifndef CDUNGEON_H
#define CDUNGEON_H

#include <vector>
using std::vector;

class CFloor;

class CDungeon
{
public:
	static CDungeon* getInstance()
	{
		if (instance == nullptr)
			instance = new CDungeon();
		return instance;
	}

	~CDungeon();

	bool AddNewFloor(int _floorNum, CFloor* _newFloor);

	int currentFloor;
	vector<CFloor*> floors;

private:
	CDungeon();

	static CDungeon* instance;


};

#endif