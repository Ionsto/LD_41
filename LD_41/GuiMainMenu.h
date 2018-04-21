#pragma once
#include "GuiTemplate.h"
class GuiMainMenu : public GuiTemplate
{
private:
	std::shared_ptr<sfg::Button> ButtonStart;
	std::shared_ptr<sfg::Button> ButtonHelp;
	std::shared_ptr<sfg::Button> ButtonExit;
public:
	GuiMainMenu();
	~GuiMainMenu();
};

