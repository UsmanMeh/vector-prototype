#include "Manager.h"

Manager* manager = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	manager = new Manager();
	manager->init("PainterWindow", WIDTH, HEIGHT, false);

	while (manager->running())
	{

		frameStart = SDL_GetTicks();

		manager->handleEvents();
		manager->update();
		manager->renderGUI();
		manager->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	manager->clean();
	return 0;
}