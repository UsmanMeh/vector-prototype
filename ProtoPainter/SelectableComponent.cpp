#include "SelectableComponent.h"

bool SelectableComponent::Select(Vector2D selectionPos)
{
	SDL_Point point{ selectionPos.x,selectionPos.y};
	SDL_Rect rect{transform->position.x , transform->position.y,transform->width,transform->height};
	if (SDL_PointInRect(&point, &rect))
	{
		isSelected = true;
		return true;
	}
	return false;
}

void SelectableComponent::UnSelect()
{
	 isSelected = false; ;
}
