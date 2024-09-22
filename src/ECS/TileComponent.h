#pragma once
#include "ECS.h"
#include "../TextureManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include<SDL.h>
#include<array>

struct TileData {
	std::size_t id;
	const char* name;
	bool walkable = false;
	int ssx, ssy;
};


class TileComponent : public Component {
public:
	SDL_Rect srcR{}, destR{};
	SDL_Texture* texture = nullptr;
	Vector2D position;
	std::string getKind() const override { return "tile"; }

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int x, int y, int tsize, int tscale, std::string id) {
		position = { (float)x, (float)y };
		texture = Game::assets->getTexture(id);
		//data = tiles[id];
		srcR = { srcX * tsize, srcY * tsize, tsize, tsize };
		destR = { x, y, tsize * tscale, tsize * tscale };

		/*if (!data.walkable) {
			entity->addComponent<ColliderComponent>(data.name);
		}*/
	}

	/*TileComponent(int id, int x, int y, int tsize, int tscale, const char* path) {
		position = { (float)x, (float)y };
		texture = TextureManager::LoadTexture(path);
		data = tiles[id];
		srcR = { data.ssx, data.ssy, tsize, tsize };
		destR = { x, y, tsize*tscale, tsize * tscale };
		if (!data.walkable) {
			entity->addComponent<ColliderComponent>(data.name);
		}
	}*/

	void update() override {
		destR.x = position.x - Game::camera.x;
		destR.y = position.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::draw(texture, srcR, destR, SDL_FLIP_NONE);
	}
};