#pragma once

#include <vector>
#include <string>
#include <SDL.h>

#include "inputs.hpp"


//the parent abstra ct class for all game objects

/**
 * \brief the parent abstract class for all game objects
 * It has basic virtual functions associated to entitties such as render, update.
 */

class Entity {

protected:

	SDL_Rect src;
	SDL_Rect mover;
	int screen_w=800, screen_h=600; //Default screen coordinates

public:

	/**
	 * This is the constructor for entity class that takes in Src coordinates of the enity, its mover coordinates and the width and heoght of the game screen.
	 */
	Entity(SDL_Rect Src, SDL_Rect Mover, int screen_w, int screen_h);
	
	/**
	 * This method returns the mover Coordinates in the form of SDL_Rect of the entity object.
	 */
	SDL_Rect getMoverCoord() const;
	/**
	 * This is a pure virtual function-a destrcutor for entity class objects.
	 */
	virtual ~Entity() = 0;
	/**
	 * This is a pure virtual method to update the enity in every game frame.
	 */
	virtual void update() = 0;
	/**
	 * This is a pure virtual method to render the entity on screen by using the SDL_Renderer which is passed as a parameter.
	 */
	virtual void render(SDL_Renderer *renderer) = 0;
	
};
