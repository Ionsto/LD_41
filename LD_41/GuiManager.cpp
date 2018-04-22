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
	if (Menu) {
		Menu->Update(dt);
	}
}
void GuiManager::UpdateEvent(sf::Event & const event)
{
	if (Menu) {
		Menu->UpdateEvent(event);
	}
}
void GuiManager::Render(sf::RenderWindow & const window)
{
	if (Menu) {
		window.setView(window.getDefaultView());
		window.resetGLStates();
		sfgui.Display(window);
	}
}