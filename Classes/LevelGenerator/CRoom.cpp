#include "CRoom.h"
#include "CCorridor.h"
#include "CDungeonUtilities.h"

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>
USING_NS_CC;

CRoom::CRoom()
{
}

CRoom::~CRoom()
{
}

int CRoom::SetupAllRoom(int _boardWidth, int _boardHeight, int _roomWidth, int _roomHeight, int _corridorLength, CRoomCoordinate* _startingCoord,
	int _maxRooms, vector<vector<bool>> &_gameBoard, vector<CRoom*> &_rooms, vector<CCorridor*> &_corridors)
{
	/*********************
	 * GENERATE 1st ROOM
	 *********************/
	firstRoom = true;

	// Set a random width and height.
	roomDepth = 0;
	roomWidth = _roomWidth;
	roomHeight = _roomHeight;

	xPos = (int)(_boardWidth * 0.5f - roomWidth * 0.5f);
	yPos = (int)(_boardHeight * 0.5f - roomHeight * 0.5f);

	coordinate = new CRoomCoordinate(_startingCoord);
	_gameBoard[coordinate->x][coordinate->y] = true;

	generated = true;
	int currNumRooms = 1;   // 1st room

	// Create Next Corridors
	nextCorridors.clear();
	for (int i = 0; i < (int)Direction::Size; ++i)
	{
		//Create Corridors
		// Safety Check  if not, create a corridor for the room
		switch ((Direction)i)
		{
		case Direction::NORTH:
			//if the next room will be out of board
			if (coordinate->y + 1 < _gameBoard[0].size())
				if (!_gameBoard[coordinate->x][coordinate->y + 1])
					break;
			continue;
		case Direction::SOUTH:
			if (coordinate->y - 1 >= 0)
				if (_gameBoard[coordinate->x][coordinate->y - 1])
					break;
			continue;
		case Direction::EAST:
			if (coordinate->x + 1 < _gameBoard.size())
				if (!_gameBoard[coordinate->x + 1][coordinate->y])
					break;
			continue;
		case Direction::WEST:
			if (coordinate->x - 1 >= 0)
				if (!_gameBoard[coordinate->x - 1][coordinate->y])
					break;
			continue;
		}

		CCorridor* newCor = new CCorridor();
		newCor->SetupCorridor(this, _corridorLength, (Direction)i);
		_corridors.push_back(newCor);
		nextCorridors.push_back(newCor);
	}

	int availableRooms = nextCorridors.size();

	// Create Next Room
	CRoomCoordinate* nextRoomCoord = new CRoomCoordinate(0, 0);

	for (int i = 0; i < nextCorridors.size(); ++i)
	{
		//if direction have a room alrdy base on the _gameboard, skip
		//if direction is same as previous corridor / corridors in list, skip
		//random a corridor except for north side and check if they got slot on gameboard
		switch (nextCorridors[i]->direction)
		{
		case Direction::NORTH:
			if (!_gameBoard[coordinate->x][coordinate->y + 1])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x, coordinate->y + 1);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_roomWidth, _roomHeight, nextRoomCoord, nextCorridors[i], currNumRooms, availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, 0);
			}
			break;

		case Direction::EAST:
			if (!_gameBoard[coordinate->x + 1][coordinate->y])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x + 1, coordinate->y);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_roomWidth, _roomHeight, nextRoomCoord, nextCorridors[i], currNumRooms, availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, 0);
			}
			break;

		case Direction::WEST:
			if (!_gameBoard[coordinate->x - 1][coordinate->y])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x - 1, coordinate->y);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_roomWidth, _roomHeight, nextRoomCoord, nextCorridors[i], currNumRooms, availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, 0);
			}
			break;

		case Direction::SOUTH:
			if (!_gameBoard[coordinate->x][coordinate->y - 1])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x, coordinate->y - 1);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_roomWidth, _roomHeight, nextRoomCoord, nextCorridors[i], currNumRooms, availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, 0);
			}
			break;
		}
	}

	//Check if its enough rooms
	while (currNumRooms < _maxRooms)
	{
		CreateEndRooms(_roomWidth, _roomHeight, _corridorLength - 2, GetEndRooms(_rooms, _maxRooms / 4), currNumRooms, availableRooms, _maxRooms, _gameBoard, _rooms, _corridors);
	}

	return currNumRooms;
}

void CRoom::SetupRoom(int _width, int _height, CRoomCoordinate* _roomCoordinate, CCorridor* _prevCorridor,
	int &_numRooms, int &_availableRooms, int &_maxRooms, vector<vector<bool>> &_gameBoard, vector<CRoom*> &_rooms, vector<CCorridor*> &_corridors,
	int _depth, bool _ignoreDepth)
{
	//Return Mechanic / Safety
	if (_roomCoordinate->x >= _gameBoard.size())
		return;

	if (_roomCoordinate->y >= _gameBoard[0].size())
		return;

	if (_gameBoard[_roomCoordinate->x][_roomCoordinate->y])
		return;

	// Init Values
	// Set the entering corridor Direction::
	nextCorridors.clear();
	prevCorridor = _prevCorridor->direction;

	roomWidth = _width;
	roomHeight = _height;
	roomDepth = _depth + 1;

	coordinate = new CRoomCoordinate(_roomCoordinate);

	//Create Room
	switch (_prevCorridor->direction)
	{
		// If the corridor entering this room is going north...
	case Direction::NORTH:
		// The y coordinate of the room must be at the end of the corridor (since the corridor leads to the bottom of the room).
		xPos = _prevCorridor->getEndPositionX() - (roomWidth / 2);
		yPos = _prevCorridor->getEndPositionY() + 1;
		break;

	case Direction::EAST:
		xPos = _prevCorridor->getEndPositionX() + 1;
		yPos = _prevCorridor->getEndPositionY() - (roomHeight / 2);
		break;

	case Direction::SOUTH:
		xPos = _prevCorridor->getEndPositionX() - (roomWidth / 2);
		yPos = _prevCorridor->getEndPositionY() - roomHeight;
		break;

	case Direction::WEST:
		xPos = _prevCorridor->getEndPositionX() - roomWidth;
		yPos = _prevCorridor->getEndPositionY() - (roomHeight / 2);
		break;
	}

	// room created successfully!
	_prevCorridor->connectedTo = true;
	generated = true;
	_gameBoard[_roomCoordinate->x][_roomCoordinate->y] = true;

	_availableRooms--;
	_numRooms++;

	if (_numRooms >= _maxRooms)
		return;

	int limit = _maxRooms / 4;

	if (limit < _depth && !_ignoreDepth)
	{
		return;
	}

	// Create Next Corridors
	int startDir = RandomHelper::random_int(0, (int)Direction::Size);
	for (int i = 0; i < (int)Direction::Size; ++i, ++startDir)
	{
		Direction nextDir = (Direction)(startDir % (int)Direction::Size);
		//if ((startDir % (int)Direction::Size) != (int)prevCorridor)
		{
			//Create Corridors
			if (RandomHelper::random_real(0.0f, 1.0f) <= 1.0f - (_numRooms + _availableRooms) / _maxRooms - i * 0.1f)
			{
				// Safety Check  if not, create a corridor for the room
				switch (nextDir)
				{
				case Direction::NORTH:
					//if the next room will be out of board
					if (coordinate->y + 1 < _gameBoard[0].size())
						if (!_gameBoard[coordinate->x][coordinate->y + 1])
							break;
					continue;
				case Direction::SOUTH:
					if (coordinate->y - 1 >= 0)
						if (!_gameBoard[coordinate->x][coordinate->y - 1])
							break;
					continue;
				case Direction::EAST:
					if (coordinate->x + 1 < _gameBoard.size())
						if (!_gameBoard[coordinate->x + 1][coordinate->y])
							break;
					continue;
				case Direction::WEST:
					if (coordinate->x - 1 >= 0)
						if (!_gameBoard[coordinate->x - 1][coordinate->y])
							break;
					continue;
				}

				CCorridor* newCor = new CCorridor();
				newCor->SetupCorridor(this, _prevCorridor->corridorLength, nextDir);
				_corridors.push_back(newCor);
				nextCorridors.push_back(newCor);
			}
		}
	}

	// Create 1 End Room
	if (nextCorridors.size() <= 0)
		return;

	_availableRooms += nextCorridors.size();

	// Create Next Room
	CRoomCoordinate* nextRoomCoord = new CRoomCoordinate(0, 0);

	for (int i = 0; i < nextCorridors.size(); ++i)
	{
		//if direction have a room alrdy base on the _gameboard, skip
		switch (nextCorridors[i]->direction)
		{
		case Direction::NORTH:
			if (!_gameBoard[coordinate->x][coordinate->y + 1])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x, coordinate->y + 1);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], _numRooms, _availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, roomDepth);
			}
			break;

		case Direction::EAST:
			if (!_gameBoard[coordinate->x + 1][coordinate->y])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x + 1, coordinate->y);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], _numRooms, _availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, roomDepth);
			}
			break;

		case Direction::WEST:
			if (!_gameBoard[coordinate->x - 1][coordinate->y])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x - 1, coordinate->y);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], _numRooms, _availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, roomDepth);
			}
			break;

		case Direction::SOUTH:
			if (!_gameBoard[coordinate->x][coordinate->y - 1])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x, coordinate->y - 1);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], _numRooms, _availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, roomDepth);
			}
			break;
		}
	}
}

/*****************************
 * FIRST ROOM FUNCTIONS ONLY
 *****************************/
vector<CRoom*> CRoom::GetEndRooms(vector<CRoom*> _rooms, int _depth)
{
	//Get all room with the same finalDepth
	vector<CRoom*> endRooms;
	for (int i = 0; i < _rooms.size(); ++i)
	{
		if (_rooms[i]->roomDepth >= _depth)
		{
			if (_rooms[i]->nextCorridors.size() <= 0)
				endRooms.push_back(_rooms[i]);
		}
	}

	return endRooms;

}
//Overlapping issue somewhere when forcing creation, mayb _gameboard is not registerig new rooms
void CRoom::CreateEndRooms(int _width, int _height, int _corridorLength, vector<CRoom*> _endRooms,
	int &_numRooms, int &_availableRooms, int &_maxRooms, vector<vector<bool>> &_gameBoard, vector<CRoom*> &_rooms, vector<CCorridor*> &_corridors)
{
	for (int i = 0; i < _endRooms.size(); ++i)
	{
		if (_endRooms[i]->nextCorridors.size() > 0)
			continue;

		_endRooms[i]->SetupEndRoom(_width, _height, _corridorLength, _numRooms, _availableRooms, _maxRooms, _gameBoard, _rooms, _corridors);

		if (_numRooms >= _maxRooms)
			break;
	}
}

void CRoom::SetupEndRoom(int _width, int _height, int _corridorLength,
	int &_numRooms, int &_availableRooms, int &_maxRooms, vector<vector<bool>> &_gameBoard, vector<CRoom*> &_rooms, vector<CCorridor*> &_corridors)
{
	//Safety measures
	if (nextCorridors.size() > 0)
		return;

	//Create Corridors
	int startDir = RandomHelper::random_int(0, (int)Direction::Size);
	for (int i = 0; i < (int)Direction::Size; ++i, ++startDir)
	{
		Direction nextDir = (Direction)(startDir % (int)Direction::Size);
		//if ((startDir % (int)Direction::Size) != (int)prevCorridor)
		{
			//Create Corridors
			if (RandomHelper::random_real(0.0f, 1.0f) <= 0.5f - i * 0.1f)
			{
				// Safety Check  if not, create a corridor for the room
				switch (nextDir)
				{
				case Direction::NORTH:
					//if the next room will be out of board
					if (coordinate->y + 1 >= _gameBoard[0].size())
						continue;
					//if corridor has a room already?
					if (_gameBoard[coordinate->x][coordinate->y + 1])
						continue;
					break;
				case Direction::SOUTH:
					if (coordinate->y - 1 < 0)
						continue;
					if (_gameBoard[coordinate->x][coordinate->y - 1])
						continue;
					break;
				case Direction::EAST:
					if (coordinate->x + 1 >= _gameBoard.size())
						continue;
					if (_gameBoard[coordinate->x + 1][coordinate->y])
						continue;
					break;
				case Direction::WEST:
					if (coordinate->x - 1 < 0)
						continue;
					if (_gameBoard[coordinate->x - 1][coordinate->y])
						continue;
					break;
				}

				CCorridor* newCor = new CCorridor();
				newCor->SetupCorridor(this, _corridorLength, nextDir);
				_corridors.push_back(newCor);
				nextCorridors.push_back(newCor);
			}
		}
	}

	// Create 1 End Room
	if (nextCorridors.size() <= 0)
		return;

	_availableRooms += nextCorridors.size();

	// Create Next Room
	CRoomCoordinate* nextRoomCoord = new CRoomCoordinate(0, 0);

	for (int i = 0; i < nextCorridors.size(); ++i)
	{
		//if direction have a room alrdy base on the _gameboard, skip
		switch (nextCorridors[i]->direction)
		{
		case Direction::NORTH:
			if (!_gameBoard[coordinate->x][coordinate->y + 1])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x, coordinate->y + 1);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], _numRooms, _availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, roomDepth, true);
			}
			break;

		case Direction::EAST:
			if (!_gameBoard[coordinate->x + 1][coordinate->y])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x + 1, coordinate->y);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], _numRooms, _availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, roomDepth, true);
			}
			break;

		case Direction::WEST:
			if (!_gameBoard[coordinate->x - 1][coordinate->y])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x - 1, coordinate->y);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], _numRooms, _availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, roomDepth, true);
			}
			break;

		case Direction::SOUTH:
			if (!_gameBoard[coordinate->x][coordinate->y - 1])
			{
				//Create next room
				CRoom* newRoom = new CRoom();
				nextRoomCoord->setCoordinate(coordinate->x, coordinate->y - 1);
				_rooms.push_back(newRoom);
				newRoom->SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], _numRooms, _availableRooms, _maxRooms, _gameBoard, _rooms, _corridors, roomDepth, true);
			}
			break;
		}
	}

}

