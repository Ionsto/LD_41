#include "GuiEndGame.h"
#include <SFGUI\Label.hpp>
#include <SFGUI\Button.hpp>


GuiEndGame::GuiEndGame(World * world)
{
	Title = sfg::Label::Create("Results:");
	LabelCrashes = sfg::Label::Create("Crash count: " + std::to_string(world->Player.CrashCount));
	LabelTime = sfg::Label::Create("Your time: " + std::to_string(world->Player.Timer/60.0) + " seconds");
	LabelTime->SetPosition((WindowSize - AllocationSize(LabelTime->GetAllocation())) / 2.0f - sf::Vector2f(0, 100));
	LabelCrashes->SetPosition((WindowSize - AllocationSize(LabelCrashes->GetAllocation())) / 2.0f + sf::Vector2f(0, 0));
	ButtonMainMenu = sfg::Button::Create("Main menu");
	ButtonMainMenu->SetRequisition(sf::Vector2f(200, 100));
	//ButtonMainMenu->SetPosition((WindowSize - AllocationSize(ButtonMainMenu->GetAllocation())) / 2.0f - sf::Vector2f(0, 100));
	ButtonMainMenu->GetSignal(sfg::Button::OnLeftClick).Connect(
		std::bind([this] {this->State = MainMenu; })
	);
	Title->SetPosition((WindowSize - AllocationSize(Title->GetAllocation())) / 2.0f - sf::Vector2f(0, 300));
	ButtonMainMenu->SetPosition(sf::Vector2f(0, (WindowSize.y - AllocationSize(ButtonMainMenu->GetAllocation()).y)));
	GuiDesktop.Add(Title);
	GuiDesktop.Add(LabelCrashes);
	GuiDesktop.Add(LabelTime);
	GuiDesktop.Add(ButtonMainMenu);
	//GuiDesktop.Update(1);
	//GuiDesktop.Refresh();
}


GuiEndGame::~GuiEndGame()
{
	GuiDesktop.RemoveAll();
}
