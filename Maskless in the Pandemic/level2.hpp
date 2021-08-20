#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "room.hpp"
#include "entity.hpp"
#include "player.hpp"
#include <vector>
#include "inputs.hpp"
#include "roomObjects.hpp"
#include "assignment.hpp"
#include "camera.hpp"
#include "watch.hpp"
#include "timer.hpp"
using namespace std;

/**
* \brief This class is used for the creating  managing the level 2 object and its distinct attributes
*/

class level2{
    private:
    int number;
    //by default current room set to 0
    int curr_room=0;
    //4 rooms in level1
    room* lrooms[4];
    string place;
    bool passed=0;
    bool pause=false;
    string state="Running";
    //Vectors and Nested vectors of entitities that include room objects, cameras, collectibles
    vector<Entity*> entities;
    vector<vector<Entity*>> collectibles;
    vector<vector<Entity*>> roomObjects;
    vector<camera *> cameras;
    const int limit=240000;
    Timer* t1;
    watch w;
    public:
    /**
     * This constructor is initializing the level 2 with textures of all objects within the level.
     * \param r is the SDL_Texture array for the 4 textures of the rooms in level1.
     * \param p is the SDL_Texture for the player object and contains its loaded spriteSheet.
     * \param O is the SDL_Texture for the all the  roomobjects and contains their loaded spriteSheet.
     * \param CS is the SDL_Texture for the CSO object and contains its loaded spriteSheet.
     * \param As is the SDL_Texture for the assignment objects and contains their loaded spriteSheet.
     * \param Cam is the SDL_Texture for the camera object and contains its loaded spriteSheet.
     * \param Al is the SDL_Texture for the health object and the time bject and contains their loaded spriteSheet.
     */
    level2( SDL_Texture *r, SDL_Texture *P, SDL_Texture *O, SDL_Texture *CS, SDL_Texture* As, SDL_Texture* Cam,  SDL_Texture* Al);
    /**
     * This method is used to begin the level 2, start the timer and start the game play by taking inputs from the user and making record in the outfile.
     * \param gRenderer is the SDL_Renderer used to display objects composing the level2 class.
     * \param inputs is the inputs for the player object which is being passed by reference.
     * \param quit is the boolean quit attribute of the game passed by refernce to check if the game has been exited during the level2.
     * \param outfile is output file in which player progress records have been written.
     */
    
    void startLevel(SDL_Renderer * gRenderer, Inputs *inputs, bool &quit, ofstream& outfile);
    /**
     * This methods written the state of the game in the form of string.
     * Game states can be "Lost, "Won", "Running"
     */
    string getLevelState();
    /**
     * This is the destructor for level2 class that deletes dynamically created objects and frees up memory.
     */
    ~level2();
};
