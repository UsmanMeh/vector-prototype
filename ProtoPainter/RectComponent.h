#pragma once
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "TransformComponent.h"
#include <iostream>
#include <cmath>
#include "ECS.h"
#define BORDER	10
class RectComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect destRect;
	TransformComponent* transform;
	
	RectComponent() = default;

	~RectComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		destRect = { static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), transform->width, transform->height };
		std::cout << destRect.x <<" | " << destRect.y << " | " << destRect.x + destRect.w << " | " << destRect.y + destRect.h << std::endl;
		transform->SetColor(Manager::fillColor);
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
		Sint16 xPoints[] = { destRect.x,destRect.x + destRect.w,destRect.x + destRect.w,destRect.x };
		Sint16 yPoints[] = { destRect.y,destRect.y,destRect.y+ destRect.h,destRect.y + destRect.h };
		filledPolygonRGBA(Manager::renderer, xPoints, yPoints,4, transform->colorR, transform->colorG, transform->colorB, transform->colorA);
	}
private:


};