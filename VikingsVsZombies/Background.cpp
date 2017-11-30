#include "Background.hpp"

Background::Background(std::string fileName, sf::IntRect textRect, sf::Vector2f Position){
    texture.loadFromFile(resourcePath() + fileName);
    sprite.setTexture(texture);
    sprite.setPosition(Position);
    texture.setRepeated(true);
    sprite.setTextureRect(textRect);
}

sf::Sprite Background::getSprite(){
    return sprite;
}

//Draws background to window
void Background::Draw(sf::RenderWindow &window){
    window.draw(sprite);
}
