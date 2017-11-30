#include "Enemy.hpp"
#include "DEFINITIONS.hpp"
#include "ResourcePath.hpp"

Enemy::Enemy(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) : animation(texture, imageCount, switchTime){
    //Initialize position
    startPosX = ENEMY_POSX;
    startPosY = ENEMY_POSY;
    row = ZOMBIE_IDLE_ROW; //Starts in idle position
    moveLoop = false;
    health = 3;

    //Sets enemy position and texture
    enemySprite.setPosition(startPosX, startPosY);
    enemySprite.setTexture(*texture);
    enemySprite.setTextureRect(animation.uvRect);
    
    //Initialize attributes
    faceRight = false;
    animationSwitch = true;
    deathSwitch = false;
    hit = false;
    enemyState = Idle;
}

//Overloaded constructor to set alternative position
Enemy::Enemy(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, bool faceRight, float x, float y) : faceRight(faceRight), startPosX(x), startPosY(y), animation(texture, imageCount, switchTime){

    row = ZOMBIE_IDLE_ROW; //Starts in idle position
    moveLoop = false;
    health = 3;
    
    //Sets enemy position and texture
    enemySprite.setPosition(startPosX, startPosY);
    enemySprite.setTexture(*texture);
    enemySprite.setTextureRect(animation.uvRect);
    
    //Initialize attributes
    animationSwitch = true;
    deathSwitch = false;
    hit = false;
    enemyState = Idle;
}

sf::Sprite* Enemy::getSprite(){
    return &enemySprite;
}

//Probably could just have a "getState" method

//Returns Dying state
bool Enemy::getDying(){
    if (enemyState == Dying)
        return true;
    else
        return false;
}

//Returns Dead state
bool Enemy::getDead(){
    if (enemyState == Dead)
        return true;
    else
        return false;
}

//Sets scale of enemy (can make bigger or larger)
void Enemy::setScale(float factorX, float factorY){
    enemySprite.setScale(factorX, factorY);
}

//This method is used for collision detection, it is more involved than the Character
//collision detection because I hard coded some state changes into it since there is no user input.
void Enemy::Collision(sf::Sprite *other){
    if (enemySprite.getTexture() == &deadTexture || (enemyState == Dying))
        return;
    
    int deltaX = enemySprite.getGlobalBounds().left - other->getGlobalBounds().left;
    
    if (abs(deltaX) < 300.0f){
        enemyState = Collide;
        if (deltaX > 0.0f && faceRight)
            faceRight = false;
        else if (deltaX < 0.0f && !faceRight)
            faceRight = true;
        
        if (animationSwitch == true){
            animation.setuvRect(ZATTACK_WIDTH, ZATTACK_HEIGHT, 1, 8);
            animationSwitch = false;
        }
    }
    else{
        if (moveLoop)
            enemyState = Run;
        else
            enemyState = Idle;
        animationSwitch = true;
        animation.resetuvRect();
    }
}

//The enemy update function which updates animation and movement
void Enemy::Update(float deltaTime){
    animation.Update(row, deltaTime, faceRight);
    enemySprite.setTextureRect(animation.uvRect);
    if (enemyState != Dead)
        Movement(deltaTime);
}

//Draws the enemy to the window
void Enemy::Draw(sf::RenderWindow &window){
    window.draw(enemySprite);
}

//The enemy movement class has a very basic movement pattern as well as a switch statement that checks on the
//enemies current state and proceeds with different actions based on this state. I would like to seperate the
//movement pattern into its own method and call on it inside this one at a later point.
void Enemy::Movement(float deltaTime){
    sf::Vector2f movement(0.0f, 0.0f);
    //When moveLoop, a timed movement action occurs at the bottom of this method
    if (enemyState != Dead){
        if (timer.getElapsedTime().asSeconds() > 5.0f){
            moveLoop = !moveLoop;
            if (!moveLoop && enemyState != Dying)
                enemyState = Idle;
            timer.restart();
        }
        switch (enemyState){
            case Idle:
            {
                row = ZOMBIE_IDLE_ROW;
                if (animation.getImageCountX() >= LAST_IDLE_COLUMN)
                    animation.setImageCountX(0);
                break;
            }
            case Run:
            {
                row = ZOMBIE_RUN_ROW;
                if (animation.getImageCountX() >= LAST_RUN_COLUMN)
                    animation.setImageCountX(0);
                if (movement.x > 0.0f){
                    faceRight = true;
                }
                else if (movement.x < 0.0f){
                    faceRight = false;
                }
                break;
            }
            case Collide:
            {
                //Changes animation to attack when in a collision with the character
                animation.setSwitchTime(ZOMBIE_ATTACK_SPEED);
                row = ZOMBIE_ATTACK_ROW;
                if (animation.getImageCountX() >= LAST_ATTACK_COLUMN)
                    animation.setImageCountX(0);
                takeHit();
                break;
            }
            case Dying:
            {
                //Calls on the Die() method once (hence the switch), to initialize the die animation and position
                if (deathSwitch){
                    Die();
                    deathSwitch = false;
                }
                if (animation.getImageCountX() >= LAST_DEAD_COLUMN){
                    animation.setImageCountX(LAST_DEAD_COLUMN - 1);
                    enemyState = Dead;
                }
                break;
            }
            case Dead:
            {
                //Does nothing...this walking dead isn't walking anymore
                break;
            }
        }
        //The moveLoop actions as long as the enemy isn't in a state of collision or death
        if (moveLoop && ((enemyState != Collide) && (enemyState != Dying) && (enemyState != Dead))){
            enemyState = Run;
            
            if (faceRight){
                movement.x += speed * deltaTime;
            }
            else{
                movement.x -= speed * deltaTime;
            }
        }
        enemySprite.move(movement);
    }
}

//This method simulates the enemy taking a hit by flashing red on his texture, it also takes away points
//from his health which sets up the dying animation
void Enemy::takeHit(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !hit){
        hit = true;
        hitTimer.restart();
    }
    if (hit == true){
        if (hitTimer.getElapsedTime().asSeconds() > 0.3f){
            enemySprite.setColor(sf::Color::Red);
            hit = false;
            health--;
            if (health <= 0){
                deathSwitch = true;
                enemyState = Dying;
            }
        }
    }
    else if (hitTimer.getElapsedTime().asSeconds() > 0.6f){
        enemySprite.setColor(sf::Color::White);
    }
}

void Enemy::Die(){
    //Sets speed and position of animation
    animation.setSwitchTime(ZOMBIE_DEATH_SPEED);
    if (faceRight)
        enemySprite.setPosition(enemySprite.getPosition().x + 50.0f, enemySprite.getPosition().y + 25.0f);
    else
        enemySprite.setPosition(enemySprite.getPosition().x - 175.0f, enemySprite.getPosition().y + 25.0f);
    
    //Initializes death texture / state
    enemySprite.setColor(sf::Color::White);
    animation.setImageCountX(0);
    deadTexture.loadFromFile(resourcePath() + DEAD_BOY_ZOMBIE_FILE);
    enemySprite.setTexture(deadTexture);
    animation.setuvRect(ZDEAD_WIDTH, ZDEAD_HEIGHT, 1, LAST_DEAD_COLUMN);
}
