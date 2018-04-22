#pragma once

#include <SFGUI\SFGUI.hpp>
#include "GuiMainMenu.h"
#include "TexturedSprite.h"
#include <memory>
class GuiManager
{
private:
	sf::Vector2f WindowSize = sf::Vector2f(1000,1000);
	/*
	Main menu
	*/
public:
	std::unique_ptr<TexturedSprite> MainMenu;
	sfg::SFGUI sfgui;
	std::unique_ptr<GuiTemplate> Menu;
	GuiManager();
	~GuiManager();
	//Probably stuff in some control systems
	void Update(float Dt);
	void UpdateEvent(sf::Event & const event);
	void Render(sf::RenderWindow & const window);
};

