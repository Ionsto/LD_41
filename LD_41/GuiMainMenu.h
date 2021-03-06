#pragma once
#include "GuiTemplate.h"
#include <SFML\Graphics.hpp>
class GuiMainMenu : public GuiTemplate
{
private:
	std::shared_ptr<sfg::Button> ButtonStart;
	std::shared_ptr<sfg::Button> ButtonHelp;
	std::shared_ptr<sfg::Button> ButtonExit;
	std::shared_ptr<sfg::Label> Title;
	std::shared_ptr<sfg::Label> Credits;
	std::vector<std::shared_ptr<sfg::Label>> Hints;
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
	void RemoveHelp();
};

