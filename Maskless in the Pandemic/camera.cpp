#include "camera.hpp"
camera::camera(SDL_Texture* a, SDL_Rect s, SDL_Rect m, float n):Entity(s,m,800, 600), asset(a), angle(n){}

camera::~camera(){
    delete asset;
}

void camera::update(){}
void camera::render(SDL_Renderer *renderer){
    SDL_RenderCopyEx(renderer,asset,&src,&mover, angle, NULL, SDL_FLIP_NONE);
    
}
//collision detection
bool camera::checkCollision(Entity * e){
}

