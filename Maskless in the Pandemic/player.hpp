#pragma once
#include <string>
#include <map>
#include <SDL.h>
#include "health.hpp"
#include "entity.hpp"
#include "inputs.hpp"
#include <SDL_mixer.h>
#include "door.hpp"
#include "roomObjects.hpp"
#include "assignment.hpp"
#include "camera.hpp"
#include <cmath>
using namespace std;


/**
* \brief This class is used generating the player object and player attributes and functions and handling its movement
*/
class Player: public Entity {
    bool isStatic;
    Door* currDoor; //for storing the current door 

    //sounds
    Mix_Music *sirenNoise = NULL;
    Mix_Music *footsteps = NULL;
    Mix_Music *doorNoise = NULL;
    Mix_Music *congrats= NULL;
	//vectors of enntitis which include collectibles and assignent
    vector<vector<Entity*>> *entities;
    vector<vector<Entity*>> *collectibles;
    //nested bool vector to check if each corresponding assignment in the room has been collected or not
    vector<vector<bool>> CollectAssignArray={{false, false},{false, false}, {false, false}, {false, false}};
	
    //3 sprite states for the player
    SDL_Rect states[3];
    SDL_Texture* spriteSheet;
    float reset=0;
    float angle=0;
    int frame=0;
    bool dooraccess=false;
    int level1assign=8;
	// General Variables
	float vx=25, vy=25;
    bool alive=false;
    health alLives;
	
    void openDoor();

public:
	/**
     * Thsi is the contsurctor for player class which intializes the player
     * \param p SDL_Texture* of the loaded spritesheet of the player
     * \param Src source SDL_Rect coordinate of the player in spritesheet 
     * \param Mover mover SDL_Rect coordinate of the player on the game window.
     * \param entities array of stationary objects in the room that player can collide with
     * \param Centities array of collectibles and assignments which player has to collect.
     * \param Al SDL_Texture* of the loaded spritesheet of the player's health
     */
	Player(SDL_Texture* p, SDL_Rect Src, SDL_Rect Mover, vector<vector<Entity*>> *entities, vector<vector<Entity*>> *Centities,SDL_Texture * Al);
	/**
     * This is the method to update the player within every game frame
     * it is the virtual mehtod of the parent  abstract class 'Entity' of the player.
     */
    void update();
    /**
     * This is the method to render the player on the screen by using SDL_Renderer passed as a paramter.
     * it is the virtual mehtod of the parent abstract class 'Entity' of the player.
     */
	void render(SDL_Renderer *renderer);
    /**
     * This is the method to handle the inpputs user makes for the player
     * It moves the player up down left right, space to open the dors in the curret room.
     * It also checks for camera and CSO radius and make changes to health accordingly.
     */
	void handle_inputs(Inputs *inputs, Door *door, camera* c,SDL_Rect rad, int cr);
    /**
     * This method returns whther the player is alive or dead if his health finsihes.
     */
	bool is_alive();
    /**
     * This method makes siren noises when the player gets into the vicinity of a camera.
     */
    void makeSirenNoise();
    /**
     * This method makes footstep noises when the player moves
     */
    void makeFootstepsNoise();
    /**
     * This method makes door creak noises when the player opens a door
     */
    void makeDoorNoise();
    /**
     * This method makes assignment collection noises when the player collects an assignment
     */
    void makeAssignNoise();
    /**
     * This method chcks if the the player is in the camera radar.
     * if yes, it decrements the health of player
     */
    void checkCameraRadar(camera *c);
    /**
     * This method checks player is standing at the door of the current room and pressing space bar to go to the next room.
     */
    bool checkDoor(Door* curD);
    /**
     * This method checks if the the player is in the radius of the CSO.
     * if yes, it decrements the health of player
     */
    bool checkCSO(SDL_Rect rad);
    /**
     * This method checks if the the player has to move to the next room
     */
    bool nextRoom();
    /**
     * This method checks the collision of player with all entities/room objects in the current room
     */
    
    bool checkCollisionAll(int cr);
    /**
     * This method checks the collision of player with all collectible assignment in the current room
     */
    void checkCollisionAssign(int curr_room);
    /**
     * This method returns if all 8 assignments have been collecte or not
     */
    bool allItemsCollected();
    /**
     * This method returns the number of assignment that are left and have to be collected in a particuar level.
     */
    int getAssignments(){return level1assign;}
    /**
     * This method returns the health of the player
     */
    health getHealth();
    /**
     * This is the destructor for the player class which deletes any dynamically allocated memory and frees up space.
     */
    ~Player();	
};
