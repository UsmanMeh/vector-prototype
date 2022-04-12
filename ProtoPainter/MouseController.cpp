#include "MouseController.h"
#include "Components.h"
#include <imgui.h>

MouseController::MouseController(ECSManager* ecsMgr) : ecsManager(ecsMgr) {}
MouseController::~MouseController()
{
}

void MouseController::init()
{
	transform = &entity->getComponent<TransformComponent>();
}

std::pair <int, int > startClick;
std::pair <int, int > endClick;
bool mouseDown = false;

void MouseController::update()
{
	if (ImGui::GetIO().WantCaptureMouse)
	{
		mouseDown = false;
		return;
	}
	if (Manager::event.type == SDL_MOUSEBUTTONDOWN)
	{
		std::cout << "\n";
		if (Manager::event.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "Left";
			SDL_GetMouseState(&startClick.first, &startClick.second);
			mouseEvent(MouseState::down,Vector2D(startClick.first, startClick.second));
		}
		else if (Manager::event.button.button == SDL_BUTTON_RIGHT)
			std::cout << "Right";
		std::cout << " Click DOWN";
	}
	if (Manager::event.type == SDL_MOUSEBUTTONUP)
	{
		std::cout << "\n";
		if (Manager::event.button.button == SDL_BUTTON_LEFT)
		{
			std::cout << "Left";
			SDL_GetMouseState(&endClick.first, &endClick.second);
			mouseEvent(MouseState::up, Vector2D(endClick.first, endClick.second));
		}
		else if (Manager::event.button.button == SDL_BUTTON_RIGHT)
			std::cout << "Right";
		std::cout << " Click Up";
	}
	SDL_GetMouseState(&currentMousePos.first, &currentMousePos.second);
}
Vector2D start;
void MouseController::mouseEvent(MouseState ms, Vector2D position)
{
	switch (ms)
	{
		case MouseState::down:
			start = position;
			OnMouseDown(start);
			mouseDown = true;
			break;
		case MouseState::up:
			OnMouseUp(start, position);
			mouseDown = false;
			start.Zero();
			break;
		default:
			break;
	}
}
void MouseController::draw()
{
	if(mouseDown)
		rectangleRGBA(Manager::renderer, startClick.first, startClick.second, currentMousePos.first,currentMousePos.second,0,255,0,255);

}
void MouseController::OnMouseDown(Vector2D pos)
{
	if (ToolsManager::m_activeTool == Tools::selection)
	{
		Manager::SelectEntity(pos);
	}
}
void MouseController::OnMouseUp(Vector2D startPos, Vector2D endPos)
{
	if (ToolsManager::m_activeTool != Tools::selection)
	{
		auto& shape(ecsManager->addEntity());
		shape.addComponent<TransformComponent>(startPos.x, startPos.y, endPos.x - startPos.x, endPos.y - startPos.y, 1, 1);
		shape.addComponent<SelectableComponent>();
		shape.addGroup(Manager::rectsGroup);
		switch (ToolsManager::m_activeTool)
		{
			case Tools::line:
				break;
			case Tools::triangle:
				shape.addComponent<TriangleComponent>();
				break;
			case Tools::square:
				break;
			case Tools::rectangle:
				shape.addComponent<RectComponent>();
				break;
			case Tools::circle:
				shape.addComponent<CircleComponent>();
				break;
			case Tools::pen:
				break;
			default:
				break;
		}
	}
	
}