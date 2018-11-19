#include "CFloor.h"

void CFloor::InitNewLevel(int _columns, int _rows, int _numRooms, int _gridSize, int _roomWidth, int _roomHeight, int _corridorLength)
{
	columns = _columns;
	rows = _rows;

	// Set up Gameboard and Starting Room Coordinates
	StartingRoom = new CRoomCoordinate(0, 0);

	int gameboardColum;
	gameboardColum = _gridSize;
	StartingRoom.x = gameboardColum / 2;

	int gameboardRow;
	gameboardRow = _gridSize;
	StartingRoom.y = gameboardRow / 2;

	// Initialize GameBoard
	gameBoard = new bool[gameboardColum][];
	for (int i = 0; i < gameBoard.Length; ++i)
	{
		gameBoard[i] = new bool[gameboardRow];
	}


	SetupTilesArray();

	CreateRoomsAndCorridors(_numRooms, _roomWidth, _roomHeight, _corridorLength);

	SetTilesValuesForRooms();
	SetTilesValuesForCorridors();
}

void CFloor::SetupTilesArray()
{
	// Set the tiles jagged array to the correct width.
	tiles = new TileType[columns][];

	// Go through all the tile arrays...
	for (int i = 0; i < tiles.Length; i++)
	{
		// ... and set each tile array is the correct height.
		tiles[i] = new TileType[rows];
	}
}

void CFloor::CreateRoomsAndCorridors(int _numRooms, int _roomWidth, int _roomHeight, int _corridorLength)
{
	// Create the rooms array with a random size.
	rooms = new List<CRoom>();

	// There should be one less corridor than there is rooms.
	corridors = new List<CCorridor>();
	Debug.Log("Creating Room and Corridors" + corridors.Count);

	// Create the first room and corridor.
	CRoom firstRoom = new CRoom();
	rooms.Add(firstRoom);
	// Setup the first room, RMCount will start from 0
	int totalRooms = firstRoom.SetupAllRoom(columns, rows, _roomWidth, _roomHeight, _corridorLength, StartingRoom,
		_numRooms, ref gameBoard, ref rooms, ref corridors);
	Debug.Log("Total Rooms: " + rooms.Count + " GeneratedRooms: " + totalRooms);
}

void CFloor::SetTilesValuesForRooms()
{
	// Go through all the rooms...
	for (int i = 0; i < rooms.Count; ++i)
	{
		CRoom currentRoom = rooms[i];
		if (!currentRoom.generated)
			continue;

		// ... and for each room go through it's width.
		for (int j = 0; j < currentRoom.roomWidth; ++j)
		{
			int xCoord = currentRoom.xPos + j;

			// For each horizontal tile, go up vertically through the room's height.
			for (int k = 0; k < currentRoom.roomHeight; k++)
			{
				int yCoord = currentRoom.yPos + k;

				if (yCoord < 0)
					yCoord = 0;

				// The coordinates in the jagged array are based on the room's position and it's width and height.
				//                    Debug.Log("x " + xCoord + " : " + "  ||  " + " y " + yCoord + " : ");
				tiles[xCoord][yCoord] = TileType.Floor;
			}
		}
	}
}

void CFloor::SetTilesValuesForCorridors()
{
	// Go through every corridor...
	for (int i = 0; i < corridors.Count; ++i)
	{
		CCorridor currentCorridor = corridors[i];

		// and go through it's length.
		for (int j = 0; j < currentCorridor.corridorLength; ++j)
		{
			// Start the coordinates at the start of the corridor.
			int xCoord = currentCorridor.startXPos;
			int yCoord = currentCorridor.startYPos;

			// Depending on the direction, add or subtract from the appropriate
			// coordinate based on how far through the length the loop is.
			switch (currentCorridor.direction)
			{
			case Direction::NORTH:
				yCoord += j;
				break;
			case Direction::EAST:
				xCoord += j;
				break;
			case Direction::SOUTH:
				yCoord -= j;
				break;
			case Direction::WEST:
				xCoord -= j;
				break;
			}

			// Set the tile at these coordinates to Floor.
			tiles[xCoord][yCoord] = TileType.Floor;
		}
	}
}