#pragma once
#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component {
public:
	ProjectileComponent(int rng, int sp, Vector2D vel): range(rng), speed(sp), velocity(vel) {
	}
	~ProjectileComponent() {}
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity.normalize() * speed;
	}
	void update() override {
		distance += speed;
		if (
			distance > range ||
			transform->position.x < Game::camera.x ||
			transform->position.x > Game::camera.x + Game::camera.w ||
			transform->position.y < Game::camera.y ||
			transform->position.y > Game::camera.y + Game::camera.h
			) {
			entity->destroy();
		}
		else {
		}
	}
	void draw() override {}

private:
	TransformComponent* transform = nullptr;
	int range;
	int speed;
	int distance = 0;
	Vector2D velocity;
};