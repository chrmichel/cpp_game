#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Collision.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "AssetManager.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera{ 0, 0, 800, 640 };
int cam_max_x = 800;
int cam_max_y = 640;

const char* mapfile = "images/texture_atlas.png";

Manager manager;
auto& player(manager.addEntity());
auto& label(manager.addEntity());

auto& tiles = manager.getGroup(Game::groupMap);
auto& players = manager.getGroup(Game::groupPlayers);
auto& enemies = manager.getGroup(Game::groupEnemies);
auto& colliders = manager.getGroup(Game::groupColliders);
auto& projectiles = manager.getGroup(Game::groupProjectiles);
auto& labels = manager.getGroup(Game::groupLabels);

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;
bool Game::debug_mode = false;

Game::Game() {
}

Game::~Game() {
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, bool debug) {
	debug_mode = debug;
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		printf("Subsystems initialized\n");
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			printf("Window created\n");
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			printf("Renderer created\n");
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	else
		isRunning = false;

	if (TTF_Init() < 0) {
		printf("TTF error\n");
	}

	map = new Map("terrain", 32, 2);

	assets->addTexture("terrain", "images/texture_atlas.png");
	assets->addTexture("player", "images/player.png");
	assets->addTexture("projectile", "images/projectile.png");

	assets->addFont("normal", "fonts/NunitoSans_10pt-Medium.ttf", 32);

	map->loadMap("maps/lvl1.map", 20, 16);
	cam_max_x = 20 * 32 * 2;
	cam_max_y = 16 * 32 * 2;

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("player");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player", SDL_Rect{ 16, 96, 32, 32 });
	player.addGroup(groupPlayers);
	SDL_Color white = {255, 255, 255, 255};
	label.addComponent<UILabel>(10, 10, "hello", "normal", white);
	label.addGroup(groupLabels);

	assets->createProjectile(Vector2D(100, 190), Vector2D(3, 2), 200, 2, "projectile");
}

void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	cnt++;
	manager.refresh();
	manager.update();
	Vector2D& playerPos = player.getComponent<TransformComponent>().position;
	SDL_Rect& playerCol = player.getComponent<ColliderComponent>().collider;
	camera.x = playerPos.x - 400;
	camera.y = playerPos.y - 320;

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > cam_max_x - camera.w) camera.x = cam_max_x - camera.w;
	if (camera.y > cam_max_y - camera.h) camera.y = cam_max_y - camera.h;

	for (auto cc : colliders) {
		auto& col = cc->getComponent<ColliderComponent>();
		if (col.tag == "player") continue;
		SDL_Rect cCol = col.collider;
		if (Collision::AABB(playerCol, cCol)) {
			std::cout << "player hit " << col.tag << std::endl;
			playerPos = player.getComponent<TransformComponent>().lastPos;
			player.getComponent<TransformComponent>().velocity.Zero();
		}
	}
	for (auto& p : projectiles) {
		if (Collision::AABB(playerCol, p->getComponent<ColliderComponent>().collider)) {
			p->destroy();
			std::cout << "Ouch!" << std::endl;
		}
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw(debug_mode);
	}
	for (auto& p : players) {
		p->draw(debug_mode);
	}
	if (debug_mode) {
		for (auto& c : colliders) {
			c->draw(debug_mode);
		}
	}
	for (auto& p : projectiles) {
		p->draw(debug_mode);
	}
	for (auto& l : labels) {
		l->draw(debug_mode);
	}
	//manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	//delete player;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	printf("Game cleaned\n");
}