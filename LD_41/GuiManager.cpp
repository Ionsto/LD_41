#include "GuiManager.h"

GuiManager::GuiManager()
{
	Menu = std::make_unique<GuiMainMenu>();
	MainMenu = std::make_unique<TexturedSprite>("./Resources/Images/MainMenu.png",sf::Vector2f(2,2));
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