#include "assignment.hpp"


assignment::assignment(SDL_Texture* a, SDL_Rect s, SDL_Rect m, float n):Entity(s,m,800, 600), asset(a), angle(n){}
assignment::~assignment(){}
void assignment::update(){}
void assignment::render(SDL_Renderer *renderer){
    if (!collected)
    SDL_RenderCopyEx(renderer,asset,&src,&mover, angle, NULL, SDL_FLIP_NONE);
}

//to check that if object has collided with player then make the collected status true
void assignment::ifCollide(){
    collected=true;
}


