#include "TexturedSprite.h"



TexturedSprite::TexturedSprite()
{
}
TexturedSprite::TexturedSprite(std::string Location)
{
	Texture = sf::Texture();
	Texture.loadFromFile(Location);
	Sprite = sf::Sprite();
	Sprite.setTexture(Texture, true);
	Sprite.setScale(sf::Vector2f(1.0 / 18.0, 1.0 / 18.0));
	Sprite.setOrigin(Texture.getSize().x / 2, Texture.getSize().y / 2);
}


TexturedSprite::~TexturedSprite()
{
}

void TexturedSprite::Render(sf::RenderWindow & window, sf::Vector2f pos, float rot) {
	Sprite.setRotation((rot * (180.0 / PI)) + 90);
	Sprite.setPosition(pos);
	window.draw(Sprite);
}