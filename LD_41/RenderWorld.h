#pragma once
#include <SFML\Graphics.hpp>
#include "World.h"
#include "TexturedSprite.h"
class RenderWorld
{
private:
	static constexpr float Scale = 20;
	sf::RenderWindow * window;
	sf::Vector2f CameraLocation = sf::Vector2f(0,0);
	sf::Vector2f CameraSize = sf::Vector2f(1000,1000);
	sf::CircleShape Marker;
	std::unique_ptr<sf::RectangleShape> BackGround;
	std::unique_ptr<TexturedSprite> Ambulance;//canae spell
	std::unique_ptr<TexturedSprite> RoadSprite;
	std::unique_ptr<TexturedSprite> OuterRoadSprite;
	std::unique_ptr<TexturedSprite> HospitalSprite;
	std::vector<std::unique_ptr<TexturedSprite>> Cars;//grab these guys oof
	std::vector<std::unique_ptr<TexturedSprite>> Buildings;//grab these guys oof
	TexturedSprite Road;//canae spell
	sf::View CameraView;
	sf::View MiniMap;
public:
	RenderWorld(sf::RenderWindow * window = nullptr);
	~RenderWorld();
	void InitRes();
	void Render(World & world);
	void RenderEntites(World &const world);
	void RenderNodes(World &const world);
	void RenderTerrain(World &const world);
	void RenderEntity(Entity &const entity);
	void RenderMiniMap(World & world);
	void ResetDrawSpace();
};

