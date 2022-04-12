#pragma once

#include "ECS.h"
//#include "../AssetManager.h"
#include "Manager.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component
{
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) :
		labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		SetLabelText(labelText, labelFont);
	}
	~UILabel()
	{}

	void SetLabelText(std::string text, std::string font)
	{
		//SDL_Surface* surf = TTF_RenderText_Blended(Manager::assets->GetFont(font), text.c_str(), textColour);
		//labelTexture = SDL_CreateTextureFromSurface(Manager::renderer, surf);
		//SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void draw() override
	{
		SDL_RenderCopy(Manager::renderer, labelTexture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};

