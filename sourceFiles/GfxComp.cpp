#include "GfxComp.h"
#include "Store.h"
#include <SFML/Graphics.hpp>

GfxComp::GfxComp(ObjectId id) : Component(id, cType::Gfx)
{
    std::cout << "Creating GfxComp" << std::endl;
}



void GfxComp::setSprite(sf::Image* image)
{
    std::cout << "Setting gfx" << std::endl;
    currentSprite_.SetImage(*image);
}


sf::Sprite* GfxComp::getSprite()
{
    return &currentSprite_;
}

