#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Game.h"
class KeyboardController: public Component
{
public:
	TransformComponent* transform = nullptr;
	SpriteComponent* sprite = nullptr;

	std::string getKind() const override {
		return "keyboard";
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = -1;
				transform->velocity.normalize() *= transform->speed; break;
			case SDLK_a:
				sprite->flip = SDL_FLIP_HORIZONTAL;
				transform->velocity.x = -1;
				transform->velocity.normalize() *= transform->speed; break;
			case SDLK_s:
				transform->velocity.y = 1;
				transform->velocity.normalize() *= transform->speed; break;
			case SDLK_d:
				transform->velocity.x = 1;
				transform->velocity.normalize() *= transform->speed; break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			case SDLK_F3:
				Game::debug_mode = !Game::debug_mode;
			default:break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				transform->velocity.y = 0; break;
			case SDLK_a:
				sprite->flip = SDL_FLIP_NONE;
				transform->velocity.x = 0; break;
			case SDLK_s:
				transform->velocity.y = 0; break;
			case SDLK_d:
				transform->velocity.x = 0; break;
			default:break;
			}

		}
	}
};

