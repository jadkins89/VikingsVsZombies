#pragma once

#include "Animate.hpp"
#include <SFML/Graphics.hpp>

class Character{
public:
    //Constructor & Destructor
    Character(){};
    Character(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
    ~Character(){};
    
    //Setters & Getters
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setCollisionIndicator(std::string collisionIndicator);
    
    //Public Methods
    void Update(float deltaTime);
    void Draw(sf::RenderWindow &window);
    bool Collision(sf::Sprite *other);
    
private:
    //Private Methods
    void Movement(float deltaTime);
    bool Attack();
    void Input(float deltaTime);
    
    //Private Data Members
    Animate animation;
    sf::Sprite characterSprite;
    sf::Vector2f movement;
    float startPosX;
    float startPosY;
    bool faceRight;
    bool attack;
    std::string collisionIndicator;
    float speed;
    unsigned int row;
};
