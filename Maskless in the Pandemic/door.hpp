#include <SDL.h>
#pragma once


/**
 * \brief this structure is used for defining the door within the room texture.
 * The door can make the player move from one room to another in a particular level.
 */

struct Door{
    int R_no; //no of the room it is in
    SDL_Rect src;
    /**
     * This is the constructor method for the door objects which creates a door with a particular rrom no r and its SDL_Rect coordinate location on the room image.
     */
    
    Door(int r, SDL_Rect S):R_no(r), src(S){}
    /**
     * This is the destructor for Door objects.
     */
   ~Door(){
       delete this;
   } 
};