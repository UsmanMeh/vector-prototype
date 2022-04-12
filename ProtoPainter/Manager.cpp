#include "Manager.h"
#include "Components.h"
#include "MouseController.h"
#include "ToolsManager.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include <sstream>

ECSManager entityManager;

SDL_Renderer* Manager::renderer = nullptr;
SDL_Event Manager::event;

SDL_Rect Manager::camera = { 0,0,800,640 };

bool Manager::isRunning = false;
float Manager::fillColor[] = { 1,1,1,1 };;
auto& controller(entityManager.addEntity());
auto& rects(entityManager.getGroup(Manager::groupLabels::rectsGroup));
auto& controllers(entityManager.getGroup(Manager::groupLabels::controllerGroup));

bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

Manager::Manager()
{
	window = nullptr;
}

Manager::~Manager()
{}

void Manager::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	flags = SDL_WINDOW_RESIZABLE;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	initGUI();
	//controller.addComponent<TransformComponent>();
	controller.addComponent<MouseController>(&entityManager);
	controller.addGroup(controllerGroup);
	std::cout << " init ";
	//if (TTF_Init() == -1)
	//{
	//	std::cout << "Error : SDL_TTF" << std::endl;
	//}
}

void Manager::initGUI()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);
}


void Manager::handleEvents()
{

	ImGui_ImplSDL2_ProcessEvent(&event);
		SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		std::cout << "exit";
		break;
	default:
		break;
	}
}

void Manager::update()
{
	entityManager.refresh();
	entityManager.update();

	//camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	//camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

	//if (camera.x < 0)
	//	camera.x = 0;
	//if (camera.y < 0)
	//	camera.y = 0;
	//if (camera.x > camera.w)
	//	camera.x = camera.w;
	//if (camera.y > camera.h)
	//	camera.y = camera.h;
}

void Manager::render()
{
	SDL_SetRenderDrawColor(Manager::renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);
	for (auto& r : rects)
	{
		r->draw();
	}
	for (auto& c : controllers)
	{
		c->draw();
	}
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(renderer);
}
void Manager::renderGUI()
{
	// Start the Dear ImGui frame
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		//ImGui::Checkbox("Another Window", &show_another_window);

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//	counter++;
		bool selection;
		if (ImGui::RadioButton("Selection Tool", ToolsManager::m_activeTool == Tools::selection))
			ToolsManager::m_activeTool = Tools::selection;
		if (ImGui::RadioButton("Circle Tool", ToolsManager::m_activeTool == Tools::circle))
			ToolsManager::m_activeTool = Tools::circle;
		if (ImGui::RadioButton("rectangle Tool", ToolsManager::m_activeTool == Tools::rectangle))
			ToolsManager::m_activeTool = Tools::rectangle;
		if (ImGui::RadioButton("triangle Tool", ToolsManager::m_activeTool == Tools::triangle))
			ToolsManager::m_activeTool = Tools::triangle;
		
		ImGui::ColorPicker4("Select color", fillColor,ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float);
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	//if (show_another_window)
	//{
	//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	//	ImGui::Text("Hello from another window!");
	//	if (ImGui::Button("Close Me"))
	//		show_another_window = false;
	//	ImGui::End();
	//}

	// Rendering
	ImGui::Render();
}

void Manager::SelectEntity(Vector2D selectionPos)
{
	entityManager.SelectEntityAt(selectionPos);
}

void Manager::clean()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

