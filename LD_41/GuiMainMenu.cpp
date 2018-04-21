#include "GuiMainMenu.h"
#include <SFGUI\Button.hpp>
#include <SFGUI\ComboBox.hpp>



GuiMainMenu::GuiMainMenu() : GuiTemplate()
{
	ButtonStart = sfg::Button::Create("Start");
	ButtonHelp = sfg::Button::Create("Help");
	ButtonExit = sfg::Button::Create("Exit");

	ButtonStart->SetRequisition(sf::Vector2f(200, 100));
	ButtonHelp->SetRequisition(sf::Vector2f(200, 100));
	ButtonExit->SetRequisition(sf::Vector2f(200, 100));
	ButtonStart->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f - sf::Vector2f(0, 100));
	ButtonHelp->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f + sf::Vector2f(0, 0));
	ButtonExit->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f + sf::Vector2f(0, 100));
	GuiDesktop.Add(ButtonStart);
	GuiDesktop.Add(ButtonHelp);
	GuiDesktop.Add(ButtonExit);

}


GuiMainMenu::~GuiMainMenu()
{

}
