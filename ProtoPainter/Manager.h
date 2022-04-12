#pragma once

#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include <iostream>
#include <vector>
#include "ToolsManager.h"
#include "Vector2D.h"
//class AssetManager;
/* Screen size */
#define WIDTH	1080
#define HEIGHT	1080

class Manager
{
public:
	Manager();
	~Manager();

	void init(const char* title, int width, int height, bool fullscreen);
	void initGUI();

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void renderGUI();
	void clean();

	static void SelectEntity(Vector2D selectionPos);
	static float fillColor[];
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	//static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		controllerGroup,
		rectsGroup
	};

private:

	int cnt = 0;
	SDL_Window* window;
};