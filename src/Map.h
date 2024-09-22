#pragma once
#include "ECS/Components.h"
#include<string>
class Map
{
public:
	Map(std::string tID, int ms, int ts);
	~Map();

	void loadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);

private:
	std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;
};

