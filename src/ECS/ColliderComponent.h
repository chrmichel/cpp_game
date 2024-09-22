#pragma once
#include "Components.h"
#include "../TextureManager.h"
#include<SDL.h>
#include<string>

class ColliderComponent : public Component {
public:
	std::string getKind() const override { return "collider"; }
	SDL_Rect collider{};
	int hit_x=0, hit_y=0;
	std::string tag{};
	TransformComponent* transform = nullptr;
	SDL_Texture* tex = nullptr;
	SDL_Rect srcR{}, destR{};

	ColliderComponent(std::string t) { tag = t; }

	ColliderComponent(std::string t, int x, int y, int size) {
		tag = t; 
		collider = { x, y, size, size };
	}

	ColliderComponent(std::string t, int x, int y, int w, int h) {
		tag = t;
		collider = { x, y, w, h };
	}

	ColliderComponent(std::string t, SDL_Rect hitbox) {
		tag = t;
		collider = hitbox;
		hit_x = hitbox.x;
		hit_y = hitbox.y;
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		tex = TextureManager::LoadTexture("images/coltex.png");
		srcR = { 0, 0, 32, 32 };
		if (tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x) + hit_x;
			collider.y = static_cast<int>(transform->position.y) + hit_y;
		}
		destR = collider;
	}

	void update() override {
		if (tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x) + hit_x;
			collider.y = static_cast<int>(transform->position.y) + hit_y;
		}

		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};