#pragma once

#include <SFGUI\SFGUI.hpp>
#include "GuiMainMenu.h"
class GuiManager
{
private:
	sf::Vector2f WindowSize = sf::Vector2f(1000,1000);
	/*
	Main menu
	*/
	std::shared_ptr<sfg::Button> ButtonStart;
	std::shared_ptr<sfg::Button> ButtonHelp;
	std::shared_ptr<sfg::Button> ButtonExit;
public:
	sfg::SFGUI sfgui;
	std::unique_ptr<GuiTemplate> Menu;
	GuiManager();
	~GuiManager();
	//Probably stuff in some control systems
	void Update(float Dt);
	void UpdateEvent(sf::Event & const event);
	void Render(sf::Window & const window);
};

