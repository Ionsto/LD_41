#pragma once
#include "GuiTemplate.h"
#include <queue>
class GuiGame :
	public GuiTemplate
{
std::shared_ptr<sfg::Label> LabelCurrentScore;
std::shared_ptr<sfg::Label> LabelScoreIncrementer;
public:
	std::queue<std::string> ScoreIncrements;
	std::string CurrentScore;
	float SizeMax = 2;
	float SizeCounter = 0;
	float SizeDecay = 0.1;
	bool SizeRamp = false;
	float SizeRampAmount = 0.7;
	//Gucci game?
	GuiGame();
	virtual ~GuiGame();
	virtual void Update(float dt);
};

