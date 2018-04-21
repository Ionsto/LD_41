#pragma once

#include <SFGUI\SFGUI.hpp>
#include <SFGUI\Desktop.hpp>
#include <SFGUI\Window.hpp>
class GuiManager
{
private:
	std::shared_ptr<sfg::Button> testbutton;
public:
	sfg::SFGUI sfgui;
	sfg::Desktop GuiDesktop;
	std::shared_ptr<sfg::Window> GuiWindow;
	GuiManager();
	~GuiManager();
	//Probably stuff in some control systems
	void Update(float Dt);
	void UpdateEvent(sf::Event & const event);
	void Render(sf::Window & const window);
};

