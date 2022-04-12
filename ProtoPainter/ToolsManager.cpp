#include "ToolsManager.h"

Tools ToolsManager::m_activeTool;

ToolsManager::ToolsManager()
{
	ToolsManager::m_activeTool = Tools::selection;
}
