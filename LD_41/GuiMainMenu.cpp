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
		std::bind(&GuiMainMenu::ButtonClickHelp,this)
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
	if (State == Help)
	{
		//Restor
		MoveToDefaultPosition();
		RemoveHelp();
		State = MoveState::None;
	}
	else
	{
		MoveToHelpPosition();
		State = MoveState::Help;
	}
}
void GuiMainMenu::MoveToDefaultPosition() {
	ButtonStart->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f - sf::Vector2f(0, 100));
	ButtonHelp->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f + sf::Vector2f(0, 0));
	ButtonExit->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f + sf::Vector2f(0, 100));
	Title->SetPosition((WindowSize - AllocationSize(Title->GetAllocation())) / 2.0f - sf::Vector2f(0, 300));
	Credits->SetPosition(sf::Vector2f(0, (WindowSize.y - AllocationSize(Title->GetAllocation()).y)));
}
void GuiMainMenu::MoveToHelpPosition() {
	ButtonStart->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f - sf::Vector2f(400, 100));
	ButtonHelp->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f + sf::Vector2f(-400, 0));
	ButtonExit->SetPosition((WindowSize - AllocationSize(ButtonStart->GetAllocation())) / 2.0f + sf::Vector2f(-400, 100));
	Title->SetPosition((WindowSize - AllocationSize(Title->GetAllocation())) / 2.0f - sf::Vector2f(400, 300));
	Credits->SetPosition(sf::Vector2f(0, (WindowSize.y - AllocationSize(Title->GetAllocation()).y)));

	Hints.push_back(sfg::Label::Create("Controls:"));
	Hints.push_back(sfg::Label::Create("W/A forwards/backwards"));
	Hints.push_back(sfg::Label::Create("A/D turn left/right"));
	Hints.push_back(sfg::Label::Create("E pick up/deliver patient"));
	Hints.push_back(sfg::Label::Create("Instructions:"));
	Hints.push_back(sfg::Label::Create("Due to severe budget cuts, ambulance drivers are being drafted from former drifters"));
	Hints.push_back(sfg::Label::Create("Your job is to pick up people from accidents (red circles) and deliver them to hospital (top left)"));
	Hints.push_back(sfg::Label::Create("Your aim is to do this as fast as possible"));
	Hints.push_back(sfg::Label::Create("Hints:"));
	Hints.push_back(sfg::Label::Create("Turning is hard, you don't have much traction - but a scandinavian flick will work"));
	int i = 0;
	for (auto & hint : Hints) {
		hint->SetPosition(sf::Vector2f(250,400 + (25*i++)));
		GuiDesktop.Add(hint);
	}
}
void GuiMainMenu::RemoveHelp() {
	for (auto & hint : Hints) {
		GuiDesktop.Remove(hint);
	}
	Hints.clear();
}