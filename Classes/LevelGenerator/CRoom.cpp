#include "CRoom.h"

int CRoom::SetupAllRoom(int _boardWidth, int _boardHeight, int _roomWidth, int _roomHeight, int _corridorLength, CRoomCoordinate _startingCoord, int _maxRooms,
	bool[][] _gameBoard, List<CRoom> _rooms, ref List<CCorridor> _corridors)
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
	_gameBoard[coordinate.x][coordinate.y] = true;

	generated = true;
	int currNumRooms = 1;   // 1st room

	// Create Next Corridors
	nextCorridors = new List<CCorridor>();
	for (int i = 0; i < (int)Direction::Size; ++i)
	{
		//Create Corridors
		// Safety Check  if not, create a corridor for the room
		switch ((Direction)i)
		{
		case Direction::NORTH:
			//if the next room will be out of board
			if (coordinate.y + 1 < _gameBoard[0].Length)
				if (!_gameBoard[coordinate.x][coordinate.y + 1])
					break;
			continue;
		case Direction::SOUTH:
			if (coordinate.y - 1 >= 0)
				if (_gameBoard[coordinate.x][coordinate.y - 1])
					break;
			continue;
		case Direction::EAST:
			if (coordinate.x + 1 < _gameBoard.Length)
				if (!_gameBoard[coordinate.x + 1][coordinate.y])
					break;
			continue;
		case Direction::WEST:
			if (coordinate.x - 1 >= 0)
				if (!_gameBoard[coordinate.x - 1][coordinate.y])
					break;
			continue;
		}

		CCorridor newCor = new CCorridor();
		newCor.SetupCorridor(this, _corridorLength, (Direction)i);
		_corridors.Add(newCor);
		nextCorridors.Add(newCor);
	}

	int availableRooms = nextCorridors.Count;

	// Create Next Room
	CRoomCoordinate nextRoomCoord = new CRoomCoordinate(0, 0);

	for (int i = 0; i < nextCorridors.Count; ++i)
	{
		//if direction have a room alrdy base on the _gameboard, skip
		//if direction is same as previous corridor / corridors in list, skip
		//random a corridor except for north side and check if they got slot on gameboard
		switch (nextCorridors[i].direction)
		{
		case Direction::NORTH:
			if (!_gameBoard[coordinate.x][coordinate.y + 1])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x, coordinate.y + 1);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_roomWidth, _roomHeight, nextRoomCoord, nextCorridors[i], ref currNumRooms, ref availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, 0);
			}
			break;

		case Direction::EAST:
			if (!_gameBoard[coordinate.x + 1][coordinate.y])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x + 1, coordinate.y);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_roomWidth, _roomHeight, nextRoomCoord, nextCorridors[i], ref currNumRooms, ref availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, 0);
			}
			break;

		case Direction::WEST:
			if (!_gameBoard[coordinate.x - 1][coordinate.y])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x - 1, coordinate.y);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_roomWidth, _roomHeight, nextRoomCoord, nextCorridors[i], ref currNumRooms, ref availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, 0);
			}
			break;

		case Direction::SOUTH:
			if (!_gameBoard[coordinate.x][coordinate.y - 1])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x, coordinate.y - 1);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_roomWidth, _roomHeight, nextRoomCoord, nextCorridors[i], ref currNumRooms, ref availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, 0);
			}
			break;
		}
	}

	//Check if its enough rooms
	while (currNumRooms < _maxRooms)
	{
		Debug.Log("Force Create Rooms Calling");
		CreateEndRooms(_roomWidth, _roomHeight, _corridorLength - 2, GetEndRooms(_rooms, _maxRooms / 4), ref currNumRooms, ref availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors);
	}

	return currNumRooms;
}

void CRoom::SetupRoom(int _width, int _height, CRoomCoordinate _roomCoordinate, CCorridor _prevCorridor,
	ref int _numRooms, ref int _availableRooms, ref int _maxRooms, ref bool[][] _gameBoard, ref List<CRoom> _rooms, ref List<CCorridor> _corridors,
	int _depth, bool _ignoreDepth = false)
{
	//Return Mechanic / Safety
	if (_roomCoordinate.x >= _gameBoard.Length)
		return;

	if (_roomCoordinate.y >= _gameBoard[0].Length)
		return;

	if (_gameBoard[_roomCoordinate.x][_roomCoordinate.y])
		return;

	// Init Values
	// Set the entering corridor Direction::
	nextCorridors = new List<CCorridor>();
	prevCorridor = _prevCorridor.direction;

	roomWidth = _width;
	roomHeight = _height;
	roomDepth = _depth + 1;

	coordinate = new CRoomCoordinate(_roomCoordinate);

	//Create Room
	switch (_prevCorridor.direction)
	{
		// If the corridor entering this room is going north...
	case Direction::NORTH:
		// The y coordinate of the room must be at the end of the corridor (since the corridor leads to the bottom of the room).
		xPos = _prevCorridor.EndPositionX - (roomWidth / 2);
		yPos = _prevCorridor.EndPositionY + 1;
		break;

	case Direction::EAST:
		xPos = _prevCorridor.EndPositionX + 1;
		yPos = _prevCorridor.EndPositionY - (roomHeight / 2);
		break;

	case Direction::SOUTH:
		xPos = _prevCorridor.EndPositionX - (roomWidth / 2);
		yPos = _prevCorridor.EndPositionY - roomHeight;
		break;

	case Direction::WEST:
		xPos = _prevCorridor.EndPositionX - roomWidth;
		yPos = _prevCorridor.EndPositionY - (roomHeight / 2);
		break;
	}

	// room created successfully!
	_prevCorridor.connectedTo = true;
	generated = true;
	_gameBoard[_roomCoordinate.x][_roomCoordinate.y] = true;

	_availableRooms--;
	_numRooms++;
	Debug.Log("CR_Count " + _rooms.Count + "  _numRooms: " + _numRooms);
	Debug.Log("Coord: " + coordinate.x + ", " + coordinate.y);

	if (_numRooms >= _maxRooms)
		return;

	int limit = _maxRooms / 4;

	if (limit < _depth && !_ignoreDepth)
	{
		return;
	}

	// Create Next Corridors
	int startDir = Random.Range(0, (int)Direction::Size);
	for (int i = 0; i < (int)Direction::Size; ++i, ++startDir)
	{
		Direction nextDir = (Direction)(startDir % (int)Direction::Size);
		//if ((startDir % (int)Direction::Size) != (int)prevCorridor)
		{
			//Create Corridors
			if (Random.Range(0.0f, 1.0f) <= 1.0f - (_numRooms + _availableRooms) / _maxRooms - i * 0.1f)
			{
				// Safety Check  if not, create a corridor for the room
				switch (nextDir)
				{
				case Direction::NORTH:
					//if the next room will be out of board
					if (coordinate.y + 1 < _gameBoard[0].Length)
						if (!_gameBoard[coordinate.x][coordinate.y + 1])
							break;
					continue;
				case Direction::SOUTH:
					if (coordinate.y - 1 >= 0)
						if (!_gameBoard[coordinate.x][coordinate.y - 1])
							break;
					continue;
				case Direction::EAST:
					if (coordinate.x + 1 < _gameBoard.Length)
						if (!_gameBoard[coordinate.x + 1][coordinate.y])
							break;
					continue;
				case Direction::WEST:
					if (coordinate.x - 1 >= 0)
						if (!_gameBoard[coordinate.x - 1][coordinate.y])
							break;
					continue;
				}

				CCorridor newCor = new CCorridor();
				newCor.SetupCorridor(this, _prevCorridor.corridorLength, nextDir);
				_corridors.Add(newCor);
				nextCorridors.Add(newCor);
			}
		}
	}

	// Create 1 End Room
	if (nextCorridors.Count <= 0)
		return;

	_availableRooms += nextCorridors.Count;

	// Create Next Room
	CRoomCoordinate nextRoomCoord = new CRoomCoordinate(0, 0);

	for (int i = 0; i < nextCorridors.Count; ++i)
	{
		//if direction have a room alrdy base on the _gameboard, skip
		switch (nextCorridors[i].direction)
		{
		case Direction::NORTH:
			if (!_gameBoard[coordinate.x][coordinate.y + 1])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x, coordinate.y + 1);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], ref _numRooms, ref _availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, roomDepth);
			}
			break;

		case Direction::EAST:
			if (!_gameBoard[coordinate.x + 1][coordinate.y])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x + 1, coordinate.y);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], ref _numRooms, ref _availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, roomDepth);
			}
			break;

		case Direction::WEST:
			if (!_gameBoard[coordinate.x - 1][coordinate.y])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x - 1, coordinate.y);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], ref _numRooms, ref _availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, roomDepth);
			}
			break;

		case Direction::SOUTH:
			if (!_gameBoard[coordinate.x][coordinate.y - 1])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x, coordinate.y - 1);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], ref _numRooms, ref _availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, roomDepth);
			}
			break;
		}
	}
}

/*****************************
 * FIRST ROOM FUNCTIONS ONLY
 *****************************/
List<CRoom> CRoom::GetEndRooms(List<CRoom> _rooms, int _depth)
{
	//Get all room with the same finalDepth
	List<CRoom> endRooms = new List<CRoom>();
	for (int i = 0; i < _rooms.Count; ++i)
	{
		if (_rooms[i].roomDepth >= _depth)
		{
			if (_rooms[i].nextCorridors.Count <= 0)
				endRooms.Add(_rooms[i]);
		}
	}

	return endRooms;

}
//Overlapping issue somewhere when forcing creation, mayb _gameboard is not registerig new rooms
void CRoom::CreateEndRooms(int _width, int _height, int _corridorLength, List<CRoom> _endRooms,
	ref int _numRooms, ref int _availableRooms, ref int _maxRooms, ref bool[][] _gameBoard, ref List<CRoom> _rooms, ref List<CCorridor> _corridors)
{
	Debug.Log("CreateEndRooms Called");
	for (int i = 0; i < _endRooms.Count; ++i)
	{
		if (_endRooms[i].nextCorridors.Count > 0)
			continue;

		_endRooms[i].SetupEndRoom(_width, _height, _corridorLength, ref _numRooms, ref _availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors);

		if (_numRooms >= _maxRooms)
			break;
	}
}

void CRoom::SetupEndRoom(int _width, int _height, int _corridorLength,
	ref int _numRooms, ref int _availableRooms, ref int _maxRooms, ref bool[][] _gameBoard, ref List<CRoom> _rooms, ref List<CCorridor> _corridors)
{
	//Safety measures
	if (nextCorridors.Count > 0)
		return;

	//Create Corridors
	Debug.Log("Setup EndRooms Called");
	Debug.Log("EndRm Coord: " + coordinate.x + ", " + coordinate.y);
	int startDir = Random.Range(0, (int)Direction::Size);
	for (int i = 0; i < (int)Direction::Size; ++i, ++startDir)
	{
		Direction nextDir = (Direction)(startDir % (int)Direction::Size);
		//if ((startDir % (int)Direction::Size) != (int)prevCorridor)
		{
			//Create Corridors
			if (Random.Range(0.0f, 1.0f) <= 0.5f - i * 0.1f)
			{
				// Safety Check  if not, create a corridor for the room
				switch (nextDir)
				{
				case Direction::NORTH:
					//if the next room will be out of board
					if (coordinate.y + 1 >= _gameBoard[0].Length)
						continue;
					//if corridor has a room already?
					if (_gameBoard[coordinate.x][coordinate.y + 1])
						continue;
					break;
				case Direction::SOUTH:
					if (coordinate.y - 1 < 0)
						continue;
					if (_gameBoard[coordinate.x][coordinate.y - 1])
						continue;
					break;
				case Direction::EAST:
					if (coordinate.x + 1 >= _gameBoard.Length)
						continue;
					if (_gameBoard[coordinate.x + 1][coordinate.y])
						continue;
					break;
				case Direction::WEST:
					if (coordinate.x - 1 < 0)
						continue;
					if (_gameBoard[coordinate.x - 1][coordinate.y])
						continue;
					break;
				}

				Debug.Log("prev: " + prevCorridor + " next: " + nextDir);
				CCorridor newCor = new CCorridor();
				newCor.SetupCorridor(this, _corridorLength, nextDir);
				_corridors.Add(newCor);
				nextCorridors.Add(newCor);
			}
		}
	}

	// Create 1 End Room
	if (nextCorridors.Count <= 0)
		return;

	_availableRooms += nextCorridors.Count;

	// Create Next Room
	CRoomCoordinate nextRoomCoord = new CRoomCoordinate(0, 0);

	for (int i = 0; i < nextCorridors.Count; ++i)
	{
		//if direction have a room alrdy base on the _gameboard, skip
		switch (nextCorridors[i].direction)
		{
		case Direction::NORTH:
			if (!_gameBoard[coordinate.x][coordinate.y + 1])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x, coordinate.y + 1);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], ref _numRooms, ref _availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, roomDepth, true);
			}
			break;

		case Direction::EAST:
			if (!_gameBoard[coordinate.x + 1][coordinate.y])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x + 1, coordinate.y);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], ref _numRooms, ref _availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, roomDepth, true);
			}
			break;

		case Direction::WEST:
			if (!_gameBoard[coordinate.x - 1][coordinate.y])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x - 1, coordinate.y);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], ref _numRooms, ref _availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, roomDepth, true);
			}
			break;

		case Direction::SOUTH:
			if (!_gameBoard[coordinate.x][coordinate.y - 1])
			{
				//Create next room
				CRoom newRoom = new CRoom();
				nextRoomCoord.setCoordinate(coordinate.x, coordinate.y - 1);
				_rooms.Add(newRoom);
				newRoom.SetupRoom(_width, _height, nextRoomCoord, nextCorridors[i], ref _numRooms, ref _availableRooms, ref _maxRooms, ref _gameBoard, ref _rooms, ref _corridors, roomDepth, true);
			}
			break;
		}
	}

}

