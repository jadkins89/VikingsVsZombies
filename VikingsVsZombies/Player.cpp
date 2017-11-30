#include "Player.hpp"
#include "ResourcePath.hpp"
#include <iostream>

Player::Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) : animation(texture, imageCount, switchTime){
    
    // Sets Player size and position
    rect.setSize(sf::Vector2f(rectWidth, rectHeight));
    rect.setPosition(startPositionX,startPositionY);
    
    // Initializes attributes
    faceRight = true;
    attack = false;
    speed = 400.0f;
    
    //Sets Texture
    rect.setTexture(texture);
}

void Player::Update(float deltaTime){
    sf::Vector2f movement(0.0f, 0.0f);

    if (!attack){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movement.x -= speed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movement.x += speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        attack = true;
        animation.setSwitchTime(0.075f);
        row = 2;
    }
    //Movement when in idle position
    if(!attack){
        if (movement.x == 0.0f){
                animation.setSwitchTime(0.15f);
                row = 1;
        }
        else{ //Position and movement when sprite moves
            row = 0;
            animation.setSwitchTime(0.05f);
            if (movement.x > 0.0f){
                faceRight = true;
            }
            else{
                faceRight = false;
            }
        }
    }
    // Ends attack animation
    if (attack)
        if (animation.getImageCountX() >= 9) // End of row
            attack = false;
   
    //Updates animation based on row, delta time, and position
    animation.Update(row, deltaTime, faceRight);
    rect.setTextureRect(animation.uvRect);
    rect.move(movement);
}

void Player::Draw(sf::RenderWindow &window){
    window.draw(rect);
}

sf::Vector2f Player::getPosition(){
    return rect.getPosition();
}
