#pragma once
#include <string>
#include <SFML\Graphics.hpp>
class TexturedSprite
{
private:
	static constexpr float PI = 3.14;//i don't care
	sf::Texture Texture;
	sf::Sprite Sprite;
public:
	TexturedSprite();
	TexturedSprite(std::string location,sf::Vector2f size);
	~TexturedSprite();
	void Render(sf::RenderWindow & window, sf::Vector2f pos, float rot);
};
