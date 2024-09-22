#pragma once
#include<map>
#include<string>
#include<SDL_ttf.h>
#include "TextureManager.h"
#include "ECS/ECS.h"
#include "Vector2D.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	//game objects
	void createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	//textures
	void addTexture(std::string id, const char* path);
	SDL_Texture* getTexture(std::string id);

	//fonts
	void addFont(std::string id, std::string path, int fontSize);
	TTF_Font* getFont(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};

