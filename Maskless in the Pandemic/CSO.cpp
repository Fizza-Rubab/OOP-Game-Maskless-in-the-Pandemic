#include "CSO.hpp"
#include <string>
#include <iostream>

using namespace std;

CSO::CSO(SDL_Texture* p, SDL_Rect Src, SDL_Rect Mover):
tex(p) , Entity(Src, Mover, 800, 600){
    //states[0]={79, 74, 285,163};
    states[0] = {0,0,120,130};
    states[1] = {120, 0 , 120, 160};
    states[2] = {0, 140 , 120 , 130};
    states[3] = {120,140,120,130};
    states[4] = {0, 270 , 120,130};

    rad = mover;
    // states[5] = {120, 270 , 120 , 130};
    
}

void CSO::update() {

}

//for defining the radar of the cso
void CSO :: radius_define(int d){
    rad = mover;
    if (d == 4){
        rad.w += 40;
        rad.x -= 20;
        rad.h += 85;
        rad.y -= 85;
    }
    else if (d==1){
        rad.h += 80;
        rad.y -= 40;
        rad.w += 105;
    }
    else if (d==2){
        rad.w += 80;
        rad.x -= 40;
        rad.h += 105;
    }
    else{
        rad.h += 800;
        rad.y -= 40;
        rad.w += 105;
        rad.x -= 105;
    }

}

//for getting the radar of the cso
SDL_Rect CSO:: get_rad(){
    return rad;
}


void CSO:: moverx(int curr_room){

    if ( mover.y < 80 && ((680 - mover.x) < 160)) {
        frame++;
        if (frame==5)
        frame=0;
        mover.y += s;
        angle = 180;
        //radius_define(2);
    }
    else if (((680 - mover.x) < 160) && ((480 - mover.y) < 120)){
        frame++;
        if (frame==5)
        frame=0;
        mover.x -= s;
        angle = 270;
        //radius_define(3);
    }
    else if (((480 - mover.y) < 120) && (mover.x < 95)){
        frame++;
        if (frame==5)
        frame=0;
        mover.y -= s;
        angle = 0;
        radius_define(4);
    }
    else if ((mover.y < 80) && (mover.x < 96)){
        frame++;
        if (frame==5)
        frame=0;
        mover.x+= s;
        angle = 90;
        //radius_define(1);
    }
    else if (mover.y < 80){
        //SDL_RenderCopyEx(renderer, tex, &src[frame], &mover, 90, NULL, SDL_FLIP_NONE);
        frame++;
        if (frame==5)
        frame=0;
        mover.x += s;
        angle = 90;
        radius_define(1);
        
    }
    else if ((480 - mover.y) < 120){
        //SDL_RenderCopyEx(renderer, tex, &src[frame], &mover, 270, NULL, SDL_FLIP_NONE);
        frame++;
        if (frame==5)
        frame=0;
        mover.x -= s;
        angle = 270;
        radius_define(3);
    }
    else if ((680 - mover.x) < 160) {
        //SDL_RenderCopyEx(renderer, tex, &src[frame], &mover, 180, NULL, SDL_FLIP_NONE);
        frame++;
        if (frame==5)
        frame=0;
        mover.y += s;
        angle = 180;
        radius_define(2);
        
        
    }
    else{
        //SDL_RenderCopy(renderer, tex, &src[frame], &mover);
        frame++;
        if (frame==5) {frame=0;}
        mover.y-=s;
        angle = 0;
        //radius_define(4);
        rad = mover;
        rad.w += 60;
        rad.x -= 30;
        rad.h += 105;
        rad.y -= 105;
        
    }

} 



void CSO::render(SDL_Renderer *renderer) {
    src=states[frame];
    SDL_RenderCopyEx(renderer, tex, &src, &mover, angle,
                         NULL, SDL_FLIP_NONE);
                        
    SDL_RenderPresent(renderer);
}


//for checking collision 
bool CSO::checkCollisionAll(int curr_room){
    vector<Entity*> v=(*(entities))[curr_room];
    
    for (int i=0;i<4;i++){
        SDL_Rect m =v[i]->getMoverCoord();
        if (SDL_HasIntersection(&mover,&m))
        
        return true;
    }
    return false;
    

}
