#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
	: xpos{x}, ypos{y}
{
	objTexture = TextureManager::LoadTexture(textureSheet);
}

void GameObject::update() {
	xpos++;
	ypos++;
	srcR.h = 64;
	srcR.w = 32;
	srcR.x = 0;
	srcR.y = 0;

	destR.x = xpos;
	destR.y = ypos;
	destR.w = srcR.w * 2;
	destR.h = srcR.h * 2;
}

void GameObject::render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcR, &destR);
}