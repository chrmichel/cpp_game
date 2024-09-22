#pragma once
#include "ECS.h"
#include "../Vector2D.h"

class TransformComponent : public Component {
public:
	std::string getKind() const override { return "transform"; }
	Vector2D position;
	Vector2D lastPos;
	Vector2D velocity;
	int height = 64;
	int width = 32;
	int scale = 1;
	int speed = 3;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(int sc) {
		position = { 400, 320 };
		scale = sc;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int w, int h, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.Zero();
		lastPos = position;
	}

	void update() override {
		lastPos = position;
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};