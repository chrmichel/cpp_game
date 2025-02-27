#include "AssetManager.h"
#include "ECS/Components.h"

AssetManager::AssetManager(Manager* man) : manager{ man } {
}

AssetManager::~AssetManager() {
}

void AssetManager::createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id) {
	auto& projectile = manager->addEntity();
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>("projectile");
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile", SDL_Rect{8, 8, 16, 16});
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::addTexture(std::string id, const char* path) {
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id) {
	return textures[id];
}

void AssetManager::addFont(std::string id, std::string path, int fontSize) {
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::getFont(std::string id) {
	return fonts[id];
}