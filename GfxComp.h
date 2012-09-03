#ifndef GFXCOMP_H_INCLUDED
#define GFXCOMP_H_INCLUDED

#include "Components.h"
#include "Vector2d.h"
#include "TypeDefs.h"
#include <SFML/Graphics.hpp>

class GfxComp : public Component
{
    public:
        GfxComp(ObjectId id);
        void setSprite(sf::Image* image);
        sf::Sprite* getSprite();


    private:
        sf::Sprite currentSprite_;
};

#endif // GFXCOMP_H_INCLUDED
