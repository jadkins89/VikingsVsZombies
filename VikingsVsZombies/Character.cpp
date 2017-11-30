#include "Character.hpp"
#include "DEFINITIONS.hpp"

Character::Character(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) : animation(texture, imageCount, switchTime){
    //Initialize position
    startPosX = PLAYER_POSX;
    startPosY = PLAYER_POSY;
    row = 1; //Starts in idle position
    
    //Sets character position and texture
    characterSprite.setPosition(startPosX, startPosY);
    characterSprite.setTexture(*texture);
    characterSprite.setTextureRect(animation.uvRect);
    
    //Initialize attributes
    faceRight = true;
    attack = false;
    collisionIndicator = "false";
    speed = CHARACTER_SPEED;
}
//Return's current position of Character
sf::Vector2f Character::getPosition(){
    return characterSprite.getPosition();
}

sf::Sprite* Character::getSprite(){
    return &characterSprite;
}

void Character::setCollisionIndicator(std::string collisionIndicator){
    this->collisionIndicator = collisionIndicator;
}

//Updates animation (image) by adjusting the row or column of the image and setting it with "setTextureRect", then runs movement
void Character::Update(float deltaTime){
    animation.Update(row, deltaTime, faceRight);
    characterSprite.setTextureRect(animation.uvRect);
    Movement(deltaTime);
}

void Character::Draw(sf::RenderWindow &window){
    window.draw(characterSprite);
}

bool Character::Collision(sf::Sprite *other){
    int characterHalfSize = abs(characterSprite.getTextureRect().width / 2);
    int otherHalfSize = abs(other->getTextureRect().width / 2);
    int deltaX = (characterSprite.getGlobalBounds().left + characterHalfSize) - (other->getGlobalBounds().left + otherHalfSize);
    
    // Different collision windows depending on which way the sprites are facing
    if (abs(deltaX) < 250.0f){
        if (deltaX > 0.0f && deltaX < 150.0f){
            collisionIndicator = "left";
            return true;
        }
        else if (deltaX < 0.0f){
            collisionIndicator = "right";
            return true;
        }
    }
    else{
        return false;
    }
}

void Character::Movement(float deltaTime){
    movement = sf::Vector2f(0.0f, 0.0f);

    if (!attack && collisionIndicator == "false"){
        Input(deltaTime);
    }
    else if (attack){ // Goes through attack animation
        if (animation.getImageCountX() >= 9) // End of row
            attack = false;
    }
    else if (collisionIndicator != "false"){
        Input(deltaTime);
    }
    characterSprite.move(movement);
}

bool Character::Attack(){
    animation.setSwitchTime(SWING_SPEED);
    row = ATTACK_ROW;
    if (animation.getImageCountX() >= 9) //End of animation
        return false;
    return true;
}

void Character::Input(float deltaTime){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && collisionIndicator != "left")
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && collisionIndicator != "right")
        movement.x += speed * deltaTime;
    
    //Movement when in idle position
    if (movement.x == 0.0f){
        animation.setSwitchTime(0.15f);
        row = IDLE_ROW;
    }
    else{ //Position and movement when sprite moves
        row = RUN_ROW;
        animation.setSwitchTime(0.05f);
        if (movement.x > 0.0f){
            faceRight = true;
        }
        else{
            faceRight = false;
        }
    }
    //Checks for space hit to begin attack animation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        attack = true;
        animation.setSwitchTime(0.075f);
        row = ATTACK_ROW;
    }
}
