#include "GuiTemplate.h"

GuiTemplate::GuiTemplate(){
	
}

GuiTemplate::~GuiTemplate(){
}

void GuiTemplate::Update(float dt) {
	GuiDesktop.Update(dt);
}

void GuiTemplate::UpdateEvent(sf::Event & const event) {
	GuiDesktop.HandleEvent(event);
}

//void GuiTemplate::Render(sf::Window & const window)
//{
//
//}