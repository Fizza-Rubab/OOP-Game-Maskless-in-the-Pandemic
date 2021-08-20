#pragma once
#include <vector>
#include <string>
#include "entity.hpp"
#include <SDL.h>


/**
 *  \brief This class is used to create any random stationary object within any room in a level.
 * It inherits from the entity class.
 */

class roomObj:public Entity{
    //roomObjects spritessheet texture
    SDL_Texture* asset;
    float angle;
    public:
    /**
     * This is theh constructor for a room object which takes in source and mover SDL_Rects with its spritesheet texture and the angle at which the object has to be displayed.
     */
    roomObj(SDL_Texture* a, SDL_Rect s, SDL_Rect m, float n);
    /**
     * This is the detructor for a room object which deallocates any dynamically allocated memory.
     */
    ~roomObj();
    /**
     * This is the method to update the roomObjects within every game frame
     * it is the virtual mehtod of the parent  abstract class 'Entity' of the roomObject.
     */
	void update();
    /**
     * This method is used to display the room object on the screen by using SDL_Renderer passed as a parameter.
     * It is a pure virtual method of entity (abstract parent class) of room object
     */
	void render(SDL_Renderer *renderer);

};

