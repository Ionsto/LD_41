#include "GuiGame.h"



GuiGame::GuiGame()
{
}


GuiGame::~GuiGame()
{
	GuiDesktop.RemoveAll();
}

void GuiGame::Update(float dt)
{
	GuiTemplate::Update(dt);
}