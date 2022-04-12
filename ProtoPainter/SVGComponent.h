#pragma once
#include "SDL.h"
#include "TransformComponent.h"
#include "Manager.h"
class SVGComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect destRect;
	TransformComponent* transform;

	SVGComponent() = default;

	~SVGComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void init() override;
	void update() override;
	void draw() override;
};