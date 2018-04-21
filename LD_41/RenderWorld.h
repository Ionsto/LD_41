#pragma once
#include <SFML\Graphics.hpp>
#include "World.h"
#include "TexturedSprite.h"
class RenderWorld
{
private:
	sf::RenderWindow * window;
	sf::Vector2f CameraLocation = sf::Vector2f(0,0);
	sf::Vector2f CameraSize = sf::Vector2f(1000,1000);
	TexturedSprite Ambulance;//canae spell
	std::vector<TexturedSprite> Cars;//grab these guys oof
	std::vector<TexturedSprite> Buildings;//grab these guys oof
	TexturedSprite Road;//canae spell
public:
	RenderWorld(sf::RenderWindow * window = nullptr);
	~RenderWorld();
	void InitRes();
	void Render(World & world);
	void RenderEntites(World &const world);
	void RenderTerrain(World &const world);
	void RenderEntity(Entity &const entity);
};

