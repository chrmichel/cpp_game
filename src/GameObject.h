#pragma once
#include "Game.h"
class GameObject
{
public:
	GameObject(const char* textureSheet, int x=0, int y=0);
	~GameObject();

	void update();
	void render();
private:
	int xpos, ypos;
	SDL_Texture* objTexture = nullptr;
	SDL_Rect srcR, destR;
};

