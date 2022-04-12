#include "ECS.h"
#include "Vector2D.h";
#include "SelectableComponent.h";

void Entity::addGroup(Group mGroup)
{
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}

bool ECSManager::SelectEntityAt(Vector2D selectionPoint)
{
	UnselectAllEntities();
	for (size_t i = entities.size() - 1; i > 0; i--)
	{
		if (entities[i]->hasComponent<SelectableComponent>())
		{
			if (entities[i]->getComponent<SelectableComponent>().Select(selectionPoint))
			{
				return true;
			}
		}
	}
	return false;
}

void ECSManager::UnselectAllEntities()
{
	if(entities.size() != 0)
		for (size_t i = 0; i < entities.size(); i++)
		{
			if (entities[i]->hasComponent<SelectableComponent>())
			{
				entities[i]->getComponent<SelectableComponent>().UnSelect();
			}
		}
}
