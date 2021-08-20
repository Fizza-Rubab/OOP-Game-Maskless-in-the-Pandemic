#include "roomObjects.hpp"

roomObj::roomObj(SDL_Texture* a, SDL_Rect s, SDL_Rect m, float n):Entity(s,m,800, 600), asset(a), angle(n){}
roomObj::~roomObj(){
    delete asset;
    //delete this;
}

//for updating room object status
void roomObj::update(){}
void roomObj::render(SDL_Renderer *renderer){
    SDL_RenderCopyEx(renderer,asset,&src,&mover, angle, NULL, SDL_FLIP_NONE);
    
}


