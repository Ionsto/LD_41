#include "GuiManager.h"

GuiManager::GuiManager()
{
	Menu = std::make_unique<GuiMainMenu>();
}


GuiManager::~GuiManager()
{
}
void GuiManager::Update(float dt)
{
	Menu->Update(dt);
}
void GuiManager::UpdateEvent(sf::Event & const event)
{
	Menu->UpdateEvent(event);
}
void GuiManager::Render(sf::Window & const window)
{
	sfgui.Display(window);
}