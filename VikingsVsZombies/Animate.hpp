#pragma once

#include <SFML/Graphics.hpp>

class Animate{
public:
    //Constructor & Destructor
    Animate(){};
    Animate(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
    ~Animate(){};
    
    //Setters & Getters
    void setSwitchTime(float switchTime);
    void setImageCountX(unsigned int column);
    unsigned int getImageCountX();
    void setuvRect(float width, float height, int row, int column);
    void resetuvRect();
    
    //Public Methods
    void Update(int row, float deltaTime, bool faceRight);
    
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    sf::Texture *texture;
    float totalTime;
    float switchTime;
};
