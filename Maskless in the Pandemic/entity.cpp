#include "entity.hpp"



SDL_Rect Entity::getMoverCoord() const{
    return mover;
}

Entity::Entity(SDL_Rect Src,SDL_Rect Mover, int screen_W, int screen_H):src(Src),mover(Mover), screen_w(screen_W),
screen_h(screen_H){}


Entity::~Entity() {}
