#pragma once

#include "Components.h"
#include "ECS.h"

	enum class MouseState : std::size_t
	{
		down,
		up,
	};
class MouseController : public Component
{
public:
	MouseController(ECSManager* ecsMgr);
	~MouseController();
	TransformComponent* transform;
	std::pair <int, int > currentMousePos;
	void init() override;
	void update() override;
	void draw() override;
	void mouseEvent(MouseState ms, Vector2D position);
	void OnMouseUp(Vector2D startPos, Vector2D endPos);
	void OnMouseDown(Vector2D Pos);
private:
	ECSManager* ecsManager;
};