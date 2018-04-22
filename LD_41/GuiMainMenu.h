#pragma once
#include "GuiTemplate.h"
class GuiMainMenu : public GuiTemplate
{
private:
	std::shared_ptr<sfg::Button> ButtonStart;
	std::shared_ptr<sfg::Button> ButtonHelp;
	std::shared_ptr<sfg::Button> ButtonExit;
	std::shared_ptr<sfg::Label> Title;
	std::shared_ptr<sfg::Label> Credits;
public:
	enum MoveState {
		None,
		Start,
		Help,
		Exit
	} State = MoveState::None;
	GuiMainMenu();
	virtual ~GuiMainMenu();
	void ButtonClickHelp();
	void MoveToDefaultPosition();
	void MoveToHelpPosition();
};

