#include "GameManager.h"
#include "GuiGame.h"
#include "GuiEndGame.h"
#include <SFGUI\Renderer.hpp>
#include <iostream>

GameManager::GameManager()
{
	srand(time(NULL));
	InitVideo();
	//Debug
	//State = GameState::Game;
	//WorldInstance = std::make_unique<World>();
}


GameManager::~GameManager()
{
}
void GameManager::InitVideo(){
	//CurrentGame = std::make_unique<GameInstance>();
	Window.create(sf::VideoMode(1000, 1000), "Need for a paramedic!");
	//Utilise unique ptr so we don't realoc if I make multiple gms
	Gui = std::make_unique<GuiManager>();
	//Window.create(sf::VideoMode::getFullscreenModes()[0], "Wolf hunt SP", sf::Style::Fullscreen);
	RenderEngine = std::make_unique<RenderWorld>(&Window);
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
	case Menu:
		//I hate myself
		if (static_cast<GuiMainMenu*>(Gui->Menu.get())->State == GuiMainMenu::MoveState::Start)
		{
			WorldInstance = std::make_unique<World>();
			Gui->Menu = std::make_unique<GuiGame>();
			RenderEngine->ResetDrawSpace();
			State = Game;
			this->clock.restart();
			break;
		}
		if (static_cast<GuiMainMenu*>(Gui->Menu.get())->State == GuiMainMenu::MoveState::Exit)
		{
			Running = false;
		}
		break;
	case GameState::End:
		//I hate myself
		if (static_cast<GuiEndGame*>(Gui->Menu.get())->State == GuiEndGame::MoveState::MainMenu)
		{
			State = Menu;
			Gui->Menu = std::make_unique<GuiMainMenu>();
			RenderEngine->ResetDrawSpace();
			break;
		}
		break;
	case Game:
		for (int i = 0; TimeDifference >= World::DeltaTime; TimeDifference -= World::DeltaTime)
		{
			ProcessInputs();
			WorldInstance->Update();
			//UpdateCamera();
		}
		if (WorldInstance->Player.AccidentCount >= WorldInstance->Player.AccidentCountMax)
		{
			Window.setView(Window.getDefaultView());
			Window.resetGLStates();
			Gui->Menu = std::make_unique<GuiEndGame>(WorldInstance.get());
			State = End;

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
		if (static_cast<GuiMainMenu*>(Gui->Menu.get())->State != GuiMainMenu::MoveState::Help) {
			Gui->MainMenu->Render(Window, sf::Vector2f(500, 500), -3.14 / 2);
		}
		Gui->Render(Window);
		break;
	case End:
		Gui->Render(Window);
		break;
	}
	Window.display();
	Window.setView(Window.getDefaultView());
	Window.resetGLStates();
}
void GameManager::PollInputs(){
	//More stuff ripped out of another project 
	sf::Event event;
	Mouse.Update();
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
				//std::cout << "Going down " << (char)event.key.code << "\n";
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code >= 0 && event.key.code <= 255)
			{
				this->KeyArray[event.key.code].Key = ButtonState::GoingUp;
				//std::cout <<"Going up " << (char)event.key.code << "\n";
			}
			break;
		default:
			break;
		}
	}
	if (State != Game)
	{
		for (int i = 0; i < KeyArray.size(); ++i)
		{
			KeyArray[i].Update();
		}
	}
}
void GameManager::ProcessInputs(){
	WorldInstance->Player.Controls.Right = KeyArray[sf::Keyboard::D].Key == ButtonState::Down;
	WorldInstance->Player.Controls.Left = KeyArray[sf::Keyboard::A].Key == ButtonState::Down;
	WorldInstance->Player.Controls.Forward = KeyArray[sf::Keyboard::W].Key == ButtonState::Down;
	WorldInstance->Player.Controls.Backward = KeyArray[sf::Keyboard::S].Key == ButtonState::Down;
	WorldInstance->Player.Controls.PickUp = KeyArray[sf::Keyboard::E].Key == ButtonState::GoingDown;
	for (int i = 0; i < KeyArray.size(); ++i)
	{
		KeyArray[i].Update();
	}
	if (KeyArray[sf::Keyboard::Escape].Key == ButtonState::Down)
	{
		State = Menu;
		Gui->Menu = std::make_unique<GuiMainMenu>();
	}
}