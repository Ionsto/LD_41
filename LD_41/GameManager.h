#pragma once
class GameManager
{
public:
	bool Running = true;
	GameManager();
	~GameManager();
	void Start();
	void MainLoop();
};

