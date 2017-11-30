#pragma once
#include "Animate.hpp"
#include <SFML/Graphics.hpp>

//Different states for the enemy, used enum over booleans (they were getting out of control)
enum State{
    Idle,
    Run,
    Collide,
    Dying,
    Dead
};

class Enemy{
public:
    //Constructors & Destructor
    Enemy(){};
    Enemy(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
    //Overloaded to set alternate position
    Enemy(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, bool faceRight, float x, float y);
    ~Enemy(){};
    
    //Setters & Getters
    sf::Sprite* getSprite();
    void setScale(float x, float y);
    bool getDying();
    bool getDead();
    
    //Public Methods
    void Update(float deltaTime);
    void Draw(sf::RenderWindow &window);
    void Collision(sf::Sprite *other);
    void takeHit();
    void Die();
    
private:
    //Private Methods
    void Movement(float deltaTime);
    
    //Animation attributes
    Animate animation;
    sf::Texture deadTexture;
    sf::Sprite enemySprite;
    
    //Timers
    sf::Clock timer;
    sf::Clock hitTimer;
    
    //Entity attributes
    float startPosX;
    float startPosY;
    unsigned int row;
    float speed = 100.0f;
    int health;
    
    //Boolean switches
    bool faceRight;
    bool animationSwitch;
    bool deathSwitch;
    bool hit;
    bool moveLoop;
    State enemyState;
};
