#include "CFloor.h"

void CFloor::InitNewLevel(int _columns, int _rows, int _numRooms, int _gridSize, int _roomWidth, int _roomHeight, int _corridorLength)
{
	columns = _columns;
	rows = _rows;

	// Set up Gameboard and Starting Room Coordinates
	StartingRoom = new CRoomCoordinate(0, 0);

	int gameboardColum;
	gameboardColum = _gridSize;
	StartingRoom->x = gameboardColum / 2;

	int gameboardRow;
	gameboardRow = _gridSize;
	StartingRoom->y = gameboardRow / 2;

	// Initialize GameBoard
	for (int i = 0; i < gameboardColum; ++i)
	{
		vector<bool> newset;
		for (int j = 0; j < gameboardRow; j++)
		{
			newset.push_back(false);
		}
		gameBoard.push_back(newset);
	}

	SetupTilesArray();

	CreateRoomsAndCorridors(_numRooms, _roomWidth, _roomHeight, _corridorLength);

	SetTilesValuesForRooms();
	SetTilesValuesForCorridors();
}

void CFloor::SetupTilesArray()
{
	// Set the tiles jagged array to the correct width.
	// Go through all the tile arrays...
	for (int i = 0; i < columns; i++)
	{
		vector<TileType> newColum;
		for (int j = 0; j < rows; j++)
		{
			newColum.push_back(TileType::None);
		}
		tiles.push_back(newColum);
	}
}

void CFloor::CreateRoomsAndCorridors(int _numRooms, int _roomWidth, int _roomHeight, int _corridorLength)
{
	// Create the rooms array with a random size.
	rooms.clear();
	corridors.clear();

	// Create the first room and corridor.
	CRoom* firstRoom;
	rooms.push_back(firstRoom);
	// Setup the first room, RMCount will start from 0
	int totalRooms = firstRoom->SetupAllRoom(columns, rows, _roomWidth, _roomHeight, _corridorLength, StartingRoom,
		_numRooms, gameBoard, rooms, corridors);
}

void CFloor::SetTilesValuesForRooms()
{
	// Go through all the rooms...
	for (int i = 0; i < rooms.size; ++i)
	{
		for (int i = 0; i < rooms.size; ++i)
		{
			CRoom* currentRoom = rooms[i];
			if (!currentRoom->generated)
				continue;

			// ... and for each room go through it's width.
			for (int j = -1; j <= currentRoom->roomWidth; ++j)
			{
				int xCoord = currentRoom->xPos + j;

				// For each horizontal tile, go up vertically through the room's height.
				for (int k = -1; k <= currentRoom->roomHeight; k++)
				{
					int yCoord = currentRoom->yPos + k;

					if (yCoord < 0)
						yCoord = 0;

					//Set wall
					if (k < 0)
					{
						tiles[xCoord][yCoord] = TileType::Wall;
						continue;
					}
					if (k >= currentRoom->roomHeight)
					{
						tiles[xCoord][yCoord] = TileType::Wall;
						continue;
					}
					if (j < 0)
					{
						tiles[xCoord][yCoord] = TileType::Wall;
						continue;
					}
					if (j >= currentRoom->roomWidth)
					{
						tiles[xCoord][yCoord] = TileType::Wall;
						continue;
					}

					tiles[xCoord][yCoord] = TileType::Floor;
				}
			}
		}
	}
}

void CFloor::SetTilesValuesForCorridors()
{
	// Go through every corridor...
	for (int i = 0; i < corridors.size; ++i)
	{
		CCorridor* currentCorridor = corridors[i];

		// and go through it's length.
		for (int j = 0; j < currentCorridor->corridorLength; ++j)
		{
			// Start the coordinates at the start of the corridor.
			int xCoord = currentCorridor->startXPos;
			int yCoord = currentCorridor->startYPos;

			// Depending on the direction, add or subtract from the appropriate
			// coordinate based on how far through the length the loop is.
			switch (currentCorridor->direction)
			{
			case Direction::NORTH:
				yCoord += j;
				tiles[xCoord + 1][yCoord] = TileType::Wall;
				tiles[xCoord - 1][yCoord] = TileType::Wall;
				break;
			case Direction::EAST:
				xCoord += j;
				tiles[xCoord][yCoord + 1] = TileType::Wall;
				tiles[xCoord][yCoord - 1] = TileType::Wall;
				break;
			case Direction::SOUTH:
				yCoord -= j;
				tiles[xCoord + 1][yCoord] = TileType::Wall;
				tiles[xCoord - 1][yCoord] = TileType::Wall;
				break;
			case Direction::WEST:
				xCoord -= j;
				tiles[xCoord][yCoord + 1] = TileType::Wall;
				tiles[xCoord][yCoord - 1] = TileType::Wall;
				break;
			}

			// Set the tile at these coordinates to Floor.
			tiles[xCoord][yCoord] = TileType::Floor;
		}
	}
}