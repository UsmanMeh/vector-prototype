#pragma once
#include "Manager.h"
#include "ECS.h"
class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D scale;

	int height = 32;
	int width = 32;

	bool blocked = false;

	TransformComponent()
	{
		position.Zero();
		scale.One();
	}

	TransformComponent(int scX, int scY)
	{
		position.Zero();
		scale = Vector2D(scX, scY);
	}

	TransformComponent(float x, float y)
	{
		position.Zero();
	}

	TransformComponent(float x, float y, int w, int h, int scX, int scY)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = Vector2D(scX,scY);
	}

	void init() override
	{
	}
	void draw() override
	{
	}
	void update() override
	{
		//position.x = static_cast<int>(position.x - Manager::camera.x);
		//position.y = static_cast<int>(position.y - Manager::camera.y);
	}

	~TransformComponent() override
	{
	}

	int colorR = 1, colorG = 1, colorB = 1, colorA = 1;

	void SetColor(float* color)
	{
		colorR = color[0] * 255;
		colorG = color[1] * 255;
		colorB = color[2] * 255;
		colorA = color[3] * 255;
	}
};