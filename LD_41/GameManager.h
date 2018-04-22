#pragma once
#include <memory>
#include <SFML\Graphics.hpp>
#include "RenderWorld.h"
#include "World.h"
#include "KeyState.h"
#include "MouseState.h"
#include "GuiManager.h"
class GameManager
{
private:
	//I am a big fan of seprating everything out in this layout
	std::unique_ptr<RenderWorld> RenderEngine;
	std::unique_ptr<World> WorldInstance;
	sf::Clock clock;
	float TimeDifference;
	//Similar to previous SFML projects in boilerplate
	MouseState Mouse;
	std::array<KeyState, 255> KeyArray;
	float DeltaTime = 0;
	enum GameState {
		Menu,
		Game,
		End
	} State;
public:
	sf::RenderWindow Window;
	std::unique_ptr<GuiManager> Gui;
	bool Running = true;
	GameManager();
	~GameManager();
	void InitVideo();
	void Start();
	void MainLoop();
	void Update();
	void Render();
	void PollInputs();
	//Minor differences
	void ProcessInputs();
};

