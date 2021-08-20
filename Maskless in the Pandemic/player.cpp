#include "player.hpp"
#include "inputs.hpp"
#include <iostream>
#include <SDL.h>
#include <cmath>
#define BLINK_INTERVAL 0.2f

#define WIDTH 36
#define HEIGHT 40

using namespace std;


Player::Player(SDL_Texture* p, SDL_Rect Src, SDL_Rect Mover, vector<vector<Entity*>> *Entities, vector<vector<Entity*>> *Centities, SDL_Texture * Al):
spriteSheet(p) , Entity(Src, Mover, 800, 600), entities(Entities), collectibles(Centities), level1assign(8),alLives(health(Al, 10)){
    
    states[0]={465, 849, 276,300};
    states[1]={857, 37, 276, 300};
    states[2]={73, 848, 276, 300};
	sirenNoise = Mix_LoadMUS( "Siren.mp3" );
    footsteps=Mix_LoadMUS( "footstep.ogg" );
    doorNoise=Mix_LoadMUS( "door.wav" );
    congrats=Mix_LoadMUS( "congratulations.ogg" );
}
Player::~Player(){
    SDL_DestroyTexture(spriteSheet);
	Mix_FreeMusic(sirenNoise);
	Mix_FreeMusic(footsteps);
    Mix_FreeMusic(doorNoise);
    Mix_FreeMusic(congrats);
    delete [] states;
	sirenNoise =NULL;
    footsteps =NULL;
    doorNoise =NULL;
    congrats =NULL;
	entities->clear();
    collectibles->clear();
    vector<vector<Entity*>>().swap(*entities);    
    vector<vector<Entity*>>().swap(*collectibles);
}

//for getting health of player
health Player::getHealth(){
    return alLives;

}

//for checking collision of player with room objects 
bool Player::checkCollisionAll(int curr_room){
    vector<Entity*> v=(*(entities))[curr_room];
    
    for (int i=0;i<4;i++){
        SDL_Rect m=v[i]->getMoverCoord();
        if (SDL_HasIntersection(&mover,&m))
        return true;
    }
    return false;
}

//for performing relevant tasks if collided
void Player::checkCollisionAssign(int curr_room){
    vector<Entity*> c=(*(collectibles))[curr_room];
    for (int i=0;i<2;i++){
        SDL_Rect m=c[i]->getMoverCoord();
        if (SDL_HasIntersection(&mover,&m) && !(CollectAssignArray[curr_room][i]))
        {
            ((assignment*)c[i])->ifCollide();
            makeAssignNoise();
            level1assign--;
            CollectAssignArray[curr_room][i]=true;
        }
    }
    
}

//for sound playing
void Player::makeSirenNoise(){
    Mix_PlayMusic( sirenNoise, 1 );
}			

void Player::makeFootstepsNoise(){
    Mix_PlayMusic( footsteps, 1 );
}

void Player::makeDoorNoise(){
    Mix_PlayMusic( doorNoise, 1 );
}

void Player::makeAssignNoise(){
    Mix_PlayMusic( congrats, 1 );
}

//for checking if the player is under camera radar or not
void Player::checkCameraRadar(camera *c){
    SDL_Rect m=c->getMoverCoord();
    if (SDL_HasIntersection(&mover,&m))
    {
        alLives-=0.25;
        makeSirenNoise();
    }
    
}
void Player::update() {
}

void Player::render(SDL_Renderer *renderer) {
    for (int i =0; i<round(alLives) ; i++){
        alLives.render(renderer, i);
    }
    src=states[frame];
    SDL_RenderCopyEx(renderer, spriteSheet, &src, &mover, angle,
                         NULL, SDL_FLIP_NONE);
                        
    SDL_RenderPresent(renderer);
}

//to check if the player is at the door
bool Player::checkDoor(Door* d)
{
    if (SDL_HasIntersection(&mover,&(d->src))){
        return true;
    }
    return false;
}

//to check if the player is in the radar of the cso or not
bool Player :: checkCSO(SDL_Rect rad){
    if (SDL_HasIntersection(&mover,&rad)){
        return true;
    }
    return false;
}

//to handle inputs and move the player sprite accordingly
void Player::handle_inputs(Inputs *inputs, Door *door,camera *c, SDL_Rect rad, int curr_room) {
    dooraccess=false; //to set that the player cannot access the door until all tasks completed
    checkCameraRadar(c);
    checkCollisionAssign(curr_room);
        if(inputs->is_key_down(KEY_P_MOVE_UP)) {
            frame++;
            if (frame==3)
            frame=0;            
            angle=0;
            if (!(mover.y-vy<10))
            makeFootstepsNoise();
            mover.y-=vy;
            if (checkCollisionAll(curr_room))
            mover.y+=vy;

        }
        if(inputs->is_key_down(KEY_P_MOVE_DOWN)) {
            frame++;
            if (frame==3)
            frame=0;
            angle=180;
            if (!(mover.y+vy>=572))
            mover.y+=vy;
            makeFootstepsNoise();
            if (checkCollisionAll(curr_room))
            mover.y-=vy;
        }
        if(inputs->is_key_down(KEY_P_MOVE_RIGHT)) {
            frame++;
            if (frame==3)
            frame=0;
            angle=90;
            if (!(mover.x+vx>=765)){
                mover.x+=vx;
                makeFootstepsNoise();
            if (checkCollisionAll(curr_room))
            mover.x-=vx;
            }
        }
        if(inputs->is_key_down(KEY_P_MOVE_LEFT)) {
            frame++;
            if (frame==3)
            frame=0;
            angle=270;
            if (!(mover.x-vx<=10)){
                mover.x-=vx;
                makeFootstepsNoise();
            if (checkCollisionAll(curr_room))
            mover.x+=vx;
            }

        }
        if(inputs->is_key_down(KEY_P_OPEN_DOOR)) {
            if (checkDoor(door)){
                makeDoorNoise();
                dooraccess=true;
            }
        }
        else
        {
            isStatic=true;
        }
        
    if (checkCSO(rad)){
        alLives-=0.25;
    }


    }
//to check if the player is alive or not
bool Player::is_alive(){
    if (round(alLives)==0)
    return false;
    else
    return true;
}

//to check if the player can access the next room or not
bool Player::nextRoom(){
    return dooraccess;

}

//to check if the player has collected all objects or not
bool Player::allItemsCollected(){
    return (level1assign==0);
}
