#pragma once
#include <SDL2_gfxPrimitives.h>
#include "ECS.h"
#include "SelectionManager.h"
#include "TransformComponent.h"
#include "RectComponent.h"
#include "Manager.h"
#include "Vector2D.h"

class SelectableComponent : public Component , public Selectable
{
public:

	TransformComponent* transform;
	bool isSelected = false;
	SelectableComponent() = default;

	~SelectableComponent()
	{
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}
	bool Select(Vector2D);
	void UnSelect(); 

	void update() override
	{
		if (isSelected)
		{
			transform->SetColor(Manager::fillColor);
		}
	}

	void draw() override
	{
		drawGizmo();
	}

	void drawGizmo() override
	{
		if (isSelected)
		{
			float padding = 5;
			if(entity->hasComponent<RectComponent>())
				rectangleRGBA(Manager::renderer, transform->position.x - padding, transform->position.y - padding, transform->position.x + transform->width+ padding, transform->position.y + transform->height+ padding, 0, 0, 255, 255);
			else
				rectangleRGBA(Manager::renderer, transform->position.x, transform->position.y, transform->position.x + transform->width, transform->position.y + transform->height, 0, 0, 255, 255);
		}
	}
};