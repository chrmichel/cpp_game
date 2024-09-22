#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<vector>

class AssetManager;
class ColliderComponent;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, bool debug=false);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() {
		return isRunning;
	}

	static SDL_Renderer* renderer;
	static SDL_Event event;
	//static std::vector<ColliderComponent*> colliders;
	static bool isRunning;
	static SDL_Rect camera;
	static bool debug_mode;
	static AssetManager* assets;

	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectiles,
		groupLabels,
	};

private:
	int cnt = 0;
	SDL_Window* window = nullptr;
};

