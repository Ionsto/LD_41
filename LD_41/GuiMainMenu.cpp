#include "GuiMainMenu.h"
#include <SFGUI\Button.hpp>
#include <SFGUI\ComboBox.hpp>
#include <SFGUI\Label.hpp>
#include <functional>


GuiMainMenu::GuiMainMenu() : GuiTemplate()
{
	ButtonStart = sfg::Button::Create("Start");
	ButtonHelp = sfg::Button::Create("Help & Controls");
	ButtonExit = sfg::Button::Create("Exit");
	Title = sfg::Label::Create("Need for a paramedic");
	Credits = sfg::Label::Create("by ionsto");

	ButtonStart->SetRequisition(sf::Vector2f(200, 100));
	ButtonHelp->SetRequisition(sf::Vector2f(200, 100));
	ButtonExit->SetRequisition(sf::Vector2f(200, 100));
	ButtonStart->GetSignal(sfg::Button::OnLeftClick).Connect(
		std::bind([this] {this->State = Start; })
	);
	ButtonHelp->GetSignal(sfg::Button::OnLeftClick).Connect(
		std::bind([this] {this->State = Help; })
	);
	ButtonExit->GetSignal(sfg::Button::OnLeftClick).Connect(
		std::bind([this] {this->State = Exit; })
	);
	MoveToDefaultPosition();
	GuiDesktop.Add(Title);
	GuiDesktop.Add(Credits);
	GuiDesktop.Add(ButtonStart);
	GuiDesktop.Add(ButtonHelp);
	GuiDesktop.Add(ButtonExit);
}


GuiMainMenu::~GuiMainMenu()
{
	GuiDesktop.RemoveAll();
	//sfg::Button::Remove(ButtonStart);
}
void GuiMainMenu::ButtonClickHelp()
{

}
void GuiMainMenu::MoveToDefaultPosition() {
	ButtonStart->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f - sf::Vector2f(0, 100));
	ButtonHelp->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f + sf::Vector2f(0, 0));
	ButtonExit->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f + sf::Vector2f(0, 100));
	Title->SetPosition((WindowSize - AllocationSize(Title->GetAllocation())) / 2.0f - sf::Vector2f(0, 300));
	Credits->SetPosition(sf::Vector2f(0, (WindowSize.y - AllocationSize(Title->GetAllocation()).y)));
}
void GuiMainMenu::MoveToHelpPosition() {
	ButtonStart->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f - sf::Vector2f(0, 100));
	ButtonHelp->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f + sf::Vector2f(0, 0));
	ButtonExit->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f + sf::Vector2f(0, 100));
	Title->SetPosition((WindowSize - AllocationSize(Title->GetAllocation())) / 2.0f - sf::Vector2f(0, 300));
	Credits->SetPosition(sf::Vector2f(0, (WindowSize.y - AllocationSize(Title->GetAllocation()).y)));
}