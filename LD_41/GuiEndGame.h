#pragma once
#include "GuiTemplate.h"
#include "World.h"
class GuiEndGame :
	public GuiTemplate
{
private:
	std::shared_ptr<sfg::Label> Title;
	std::shared_ptr<sfg::Label> LabelTime;
	std::shared_ptr<sfg::Label> LabelCrashes;
	std::shared_ptr<sfg::Button> ButtonMainMenu;
public:
	enum MoveState {
		None,
		MainMenu
	} State = MoveState::None;
	GuiEndGame(World * world);
	virtual ~GuiEndGame();
};

