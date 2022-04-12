#pragma once
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "TransformComponent.h"
#include <iostream>
#include <cmath>
#include "ECS.h"
#define BORDER	10
class TriangleComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect destRect;
	TransformComponent* transform;

	TriangleComponent() = default;

	~TriangleComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		destRect = { static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), transform->width, transform->height };
		std::cout << destRect.x << " | " << destRect.y << " | " << destRect.x + destRect.w << " | " << destRect.y + destRect.h << std::endl;
	}
	void update() override
	{
	}
	void SetViewport(SDL_Renderer* renderer, int x1, int y1, int x2, int y2)
	{
		SDL_Rect clip;
		clip.x = x1 + BORDER;
		clip.y = y1 + BORDER;
		clip.w = x2 - x1 - 2 * BORDER;
		clip.h = y2 - y1 - 2 * BORDER;
		SDL_RenderSetViewport(renderer, &clip);
	}
	void draw() override
	{
		//SDL_SetRenderDrawColor(Manager::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		//SetViewport(Manager::renderer, 0, 60, 500 / 2, 60 + (500 - 80) / 2);
		//roundedRectangleColor(Manager::renderer, 20, 20, 5, 5, 5, 255);

		//roundedBoxColor(Manager::renderer, destRect.x, destRect.y, destRect.x + destRect.w, destRect.y + destRect.h, 5, 0x80000000);
		//filledCircleColor(Manager::renderer, (destRect.x + destRect.w / 2), (destRect.y + destRect.h / 2), std::abs(std::abs(destRect.w) < std::abs(destRect.h)?destRect.w / 2: destRect.h / 2), 0x800000ff);
		filledTrigonRGBA(Manager::renderer, (destRect.x + destRect.w / 2), (destRect.y), destRect.x, destRect.y+destRect.h, destRect.x + destRect.w, destRect.y+destRect.h, 255, 0, 0, 255);
		//rectangleColor(Manager::renderer, destRect.x, destRect.y, destRect.x + destRect.w, destRect.y + destRect.h, 0xff000000);
		//SDL_SetRenderDrawColor(Manager::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		//SDL_RenderDrawRect(Manager::renderer, &destRect);
	}
};