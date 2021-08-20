#pragma once

#include <SDL.h>
#include <iostream>
#include "player.hpp"
#include "roomObjects.hpp"
#include <vector>
#include "CSO.hpp"
using namespace std;

/**
* \brief This class is used  for creating the rooms in each level and allocate all the static roomObjects and the collectibles.
*/

class room{
    protected:
    //Source Mover Coordinate Rects
    SDL_Rect mover={0,0, 800, 600};
    SDL_Rect src={0,0, 1280, 960};
    SDL_Texture* asset;
    Door *door;
    //Room Objects
    std::vector<Entity*> roomObjects;
    //Room collectibles
    std::vector<Entity*> roomCollectibles;
    public:
    /**
     * This is a default no parameter constructor for romm
     */
    room();
    /**
     * This is a destructor for room entity which clears up any dynamically allocted memory.
     */
    ~room();
    /**
     * This is a constructor for room object which initializes the room with sdl texture of room, its source coordinate, mover coordinates.
     * It also takes in the vectors for roomObjects and the room collectibles.
     * It also allocates the Door within the room using its SDL_Rect coordinates passed in parameter D.
     */
    room( SDL_Texture* a,SDL_Rect s, SDL_Rect m, int r, SDL_Rect D, vector<Entity*> RO, vector<Entity*> C);
    /**
     * This method trakes in the SDL_Renderer and displays the room on the window.
     */
    void showRoom(SDL_Renderer * gRenderer);
    /**
     * This method taakes in the SDL_Renderer and clears it so that the room isnt visible anymore and is hidden
     */
    void hideRoom(SDL_Renderer * gRenderer);
    /** 
     * This method checks if the player wants to leave through the door of the current toom and move to next room flag.
     */
    bool doorLeave(Player *p);
    /**
     * This method returns the door objevct within the room
     */
    Door* getDoor();
};
