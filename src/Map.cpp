#include "Map.h"
#include "Game.h"
#include "ECS/ECS.h"
#include<fstream>

extern Manager manager;

Map::Map(std::string tID, int ms, int ts) 
	: texID{ tID }, mapScale{ ms }, tileSize{ ts } {
	scaledSize = ms * ts;
}

Map::~Map() {
}

void Map::loadMap(std::string path, int sizeX, int sizeY) {
	char c{};
	std::fstream mapFile;
	mapFile.open(path);
	int srcX, srcY;

	auto& border_up = manager.addEntity();
	border_up.addGroup(Game::groupColliders);
	border_up.addComponent<ColliderComponent>("terrain", -1 * scaledSize, -1 * scaledSize, (sizeX+2) * scaledSize, 1 * scaledSize);
	auto& border_left = manager.addEntity();
	border_left.addComponent<ColliderComponent>("terrain", -1 * scaledSize, 0 * scaledSize, 1 * scaledSize, sizeY * scaledSize );
	border_left.addGroup(Game::groupColliders);
	auto& border_right = manager.addEntity();
	border_right.addComponent<ColliderComponent>("terrain", sizeX * scaledSize, 0 * scaledSize, 1 * scaledSize, sizeY * scaledSize );
	border_right.addGroup(Game::groupColliders);
	auto& border_down = manager.addEntity();
	border_down.addComponent<ColliderComponent>("terrain", -1 * scaledSize, sizeY * scaledSize, (sizeX + 2) * scaledSize, 1 * scaledSize );
	border_down.addGroup(Game::groupColliders);

	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();

			if (srcX == 0 && srcY == 0) {
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, x, y, mapScale, tileSize, texID);
	tile.addGroup(Game::groupMap);
}