#include "SVGComponent.h"
#include "ECS.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
void SVGComponent::init()
{
	transform = &entity->getComponent<TransformComponent>();
	destRect = { static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), transform->width, transform->height };

}
void SVGComponent::update()
{
}
void SVGComponent::draw()
{
	
	std::string w= "' width='";
	std::string svg =
		"<svg height='"+ std::to_string(transform->height/2) + w + std::to_string(transform->width/2) + "'><circle cx='" + std::to_string(transform->position.x) + "' cy='" + std::to_string(transform->position.y) + "' r='80' stroke='white' stroke-width='5' fill='black'/></svg>";
	svg = "<svg height = '1024' width = '1024'><circle cx = '500' cy = '500' r = '500' stroke = 'black' stroke - width = '3' fill = 'red' / >< / svg>";
	SDL_RWops* rw = SDL_RWFromConstMem(svg.c_str(), svg.size());
	SDL_Surface* surface = IMG_Load_RW(rw, 1);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Manager::renderer, surface);
	SDL_SetRenderDrawColor(Manager::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderCopyEx(Manager::renderer, texture, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);
	//SDL_RenderDrawRect(Manager::renderer, &destRect);
}