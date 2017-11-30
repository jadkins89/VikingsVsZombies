#include "Animate.hpp"

Animate::Animate(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) : texture(texture){
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0; //start at first image
    
    //Initializes the pixel dimensions of each sprite
    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animate::Update(int row, float deltaTime, bool faceRight){
    //If row has been changed, reset column to 0
    if (currentImage.y !=row)
        currentImage.x = 0;
    currentImage.y = row;
    
    // Sets the y pixel coordinate on sprite spreadsheet
    uvRect.top = currentImage.y * uvRect.height;
    
    //Standard, right facing animation
    if (faceRight){
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    //Inverted, left facing animation
    else{
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
    //Tracking framerate
    totalTime += deltaTime;
    
    if (totalTime >= switchTime){
        totalTime -=switchTime;
        currentImage.x++;
        //Restarts animation when it reaches the last image
        if (currentImage.x >= imageCount.x){
            currentImage.x = 0;
        }
    }
}

void Animate::setSwitchTime(float switchTime){
    this->switchTime = switchTime;
}
void Animate::setImageCountX(unsigned int column){
    currentImage.x = column;
}
unsigned int Animate::getImageCountX(){
    return currentImage.x;
}

void Animate::setuvRect(float width, float height, int row, int column){
    uvRect.width = width / float(column);
    uvRect.height = height / float(row);
}

void Animate::resetuvRect(){
    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}



