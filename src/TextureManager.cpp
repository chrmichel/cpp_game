#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tmpSrf = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSrf);
	SDL_FreeSurface(tmpSrf);

	return tex;
}


void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}