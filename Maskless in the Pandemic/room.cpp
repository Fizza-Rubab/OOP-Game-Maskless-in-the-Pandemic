#include "room.hpp"
using namespace std;

room::room(){}
room::~room(){
    delete asset;
    delete door;
    for ( Entity* &index : roomObjects){
        delete index;
        index = NULL;
    }
    for ( Entity* &index : roomCollectibles){
        delete index;
        index = NULL;
    }
    
}
room::room( SDL_Texture* a,SDL_Rect s, SDL_Rect m, int r, SDL_Rect D, vector<Entity*> RO, vector<Entity*> C):asset(a), src(s), mover(m),door(new Door(r, D)), roomObjects(RO), roomCollectibles(C){}
void room::showRoom(SDL_Renderer * gRenderer){
    SDL_RenderCopy(gRenderer, asset, &src, &mover);
    for (auto d: roomObjects){
        d->render(gRenderer);
    }
    for (auto e: roomCollectibles){
        e->render(gRenderer);
    }
    SDL_RenderPresent(gRenderer);   
}

//to hide the room upon completion
void room::hideRoom(SDL_Renderer * gRenderer){
    SDL_RenderClear(gRenderer);
}

//to check if the next door can be accessed or not
bool room::doorLeave(Player *p)
{
    return p->nextRoom();
}

//to get the door
Door* room::getDoor(){
    return door;
}