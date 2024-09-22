#pragma once

#include "Components.h"
#include "Animation.h"
#include "../TextureManager.h"
#include "AssetManager.h"
#include<SDL.h>
#include<iostream>
#include<map>

class SpriteComponent : public Component {
private:
	TransformComponent* transform = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect srcRect{}, destRect{};

	int frames = 0;
	bool animated = false;
	int speed = 100;

public:
	std::string getKind() const override { return "sprite"; }

	int animIndex{};
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	std::map<const char*, Animation> animations;
	SpriteComponent() = default;
	SpriteComponent(std::string id) {
		setTex(id);
	}
	SpriteComponent(std::string id, int nFrames, int _speed)
		: frames{ nFrames }, speed{ _speed }, animated{ true } {
		setTex(id);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}
	void setTex(std::string id) {
		texture = Game::assets->getTexture(id);
		if (!texture)
			std::cout << "Could not load asset " << id << std::endl;
	}

	void init() override {

		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		srcRect.y = animIndex * transform->height;
		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = srcRect.w * transform->scale;
		destRect.h = srcRect.h * transform->scale;
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect, flip);
	}
};