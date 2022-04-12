#pragma once
#include <iostream>
enum class Tools : std::size_t
{
	selection,
	line,
	triangle,
	square,
	rectangle,
	circle,
	pen
};
class ToolsManager
{
public:
	ToolsManager();
	static Tools m_activeTool;
};

