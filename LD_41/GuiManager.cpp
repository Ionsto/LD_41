#include "GuiManager.h"
#include <SFGUI\Button.hpp>


GuiManager::GuiManager()
{
	GuiWindow = sfg::Window::Create();
	GuiWindow->SetTitle("Hi");
	GuiDesktop.Add(GuiWindow);
	testbutton = sfg::Button::Create("Hello");
	GuiWindow->Add(testbutton);
}


GuiManager::~GuiManager()
{
}
void GuiManager::Update(float dt)
{
	GuiDesktop.Update(dt);
}
void GuiManager::UpdateEvent(sf::Event & const event)
{
	GuiDesktop.HandleEvent(event);
}
void GuiManager::Render(sf::Window & const window)
{
	sfgui.Display(window);
}