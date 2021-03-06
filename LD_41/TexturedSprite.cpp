#include "TexturedSprite.h"



TexturedSprite::TexturedSprite()
{
}
TexturedSprite::TexturedSprite(std::string Location,sf::Vector2f size)
{
	Texture = sf::Texture();
	Texture.loadFromFile(Location);
	Sprite = sf::Sprite();
	Sprite.setTexture(Texture, true);
	Sprite.setOrigin(Texture.getSize().x / 2, Texture.getSize().y / 2);
	Sprite.setScale(size);
}


TexturedSprite::~TexturedSprite()
{
}

void TexturedSprite::Render(sf::RenderWindow & window, sf::Vector2f pos, float rot) {
	Sprite.setRotation((rot * (180.0 / PI)) + 90);
	Sprite.setPosition(pos);
	window.draw(Sprite);
}