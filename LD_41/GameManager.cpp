#include "GameManager.h"
#include <iostream>

GameManager::GameManager()
{
	InitVideo();
	//Debug
	State = GameState::Game;
}


GameManager::~GameManager()
{
}
void GameManager::InitVideo(){
	//CurrentGame = std::make_unique<GameInstance>();
	Window.create(sf::VideoMode(1000, 1000), "Need for a parmedic");
	//Utilise unique ptr so we don't realoc if I make multiple gms
	Gui = std::make_unique<GuiManager>();
	//Window.create(sf::VideoMode::getFullscreenModes()[0], "Wolf hunt SP", sf::Style::Fullscreen);
	RenderEngine = std::make_unique<RenderWorld>();
	Running = true;
	Mouse = MouseState();
	Window.setKeyRepeatEnabled(false);
	std::cout << "Init complete" << std::endl;
}


void GameManager::Start(){
	MainLoop();
}

void GameManager::MainLoop() {
	//Bootstrap restart loop
	this->clock.restart();
	while (Running) {
		Update();
		DeltaTime = this->clock.restart().asSeconds();
		TimeDifference += DeltaTime;
		Render();
		PollInputs();
	}
}
void GameManager::Update(){
	switch (State) {
	case Game:
		for (int i = 0; TimeDifference >= World::DeltaTime; TimeDifference -= World::DeltaTime)
		{
			WorldInstance->Update();
			//UpdateCamera();
		}
		break;
	}
	Gui->Update(DeltaTime);
}

void GameManager::Render()
{
	Window.clear();
	switch (State) {
	case Game:
		RenderEngine->Render(*WorldInstance.get());
		break;
	case Menu:
	case Paused:
		Gui->Render(Window);
		break;
	}
	Window.display();
}
void GameManager::PollInputs(){
	//More stuff ripped out of another project 
	sf::Event event;
	Mouse.Update();
	for (int i = 0; i < KeyArray.size(); ++i)
	{
		KeyArray[i].Update();
	}
	while (Window.pollEvent(event))
	{
		Gui->UpdateEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			Running = false;
			break;
		case sf::Event::MouseButtonPressed:
			Mouse.Location.x = event.mouseButton.x;
			Mouse.Location.y = event.mouseButton.y;
			if (event.mouseButton.button == 0)
			{
				Mouse.Left = ButtonState::GoingDown;
			}
			if (event.mouseButton.button == 1)
			{
				Mouse.Right = ButtonState::GoingDown;
			}
			break;
		case sf::Event::MouseMoved:
			Mouse.Location.x = event.mouseMove.x;
			Mouse.Location.y = event.mouseMove.y;
			break;
		case sf::Event::MouseButtonReleased:
			Mouse.Location.x = event.mouseButton.x;
			Mouse.Location.y = event.mouseButton.y;
			if (event.mouseButton.button == 0)
			{
				Mouse.Left = ButtonState::GoingUp;
			}
			if (event.mouseButton.button == 1)
			{
				Mouse.Right = ButtonState::GoingUp;
			}
			break;
		case sf::Event::KeyPressed:
			if (event.key.code >= 0 && event.key.code <= 255)
			{
				this->KeyArray[event.key.code].Key = ButtonState::GoingDown;
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code >= 0 && event.key.code <= 255)
			{
				this->KeyArray[event.key.code].Key = ButtonState::GoingUp;
			}
			break;
		default:
			break;
		}
	}
}