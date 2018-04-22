#pragma once
#include <SFGUI\SFGUI.hpp>
#include <SFML\Graphics.hpp>
#include <SFGUI\SFGUI.hpp>
#include <SFGUI\Desktop.hpp>
class GuiTemplate
{
protected:
	//Idk
	sf::Vector2f WindowSize = sf::Vector2f(1000, 1000);
	sf::Vector2f AllocationSize(sf::FloatRect alloc)
	{
		return sf::Vector2f(alloc.width, alloc.height);
	}
	sf::Vector2f AllocationPosition(sf::FloatRect alloc)
	{
		return sf::Vector2f(alloc.top, alloc.left);
	}
public:
	sfg::Desktop GuiDesktop;
	GuiTemplate();
	virtual ~GuiTemplate();
	virtual void Update(float Dt);
	virtual void UpdateEvent(sf::Event & const event);
	//virtual void Render(sf::Window & const window);
};

