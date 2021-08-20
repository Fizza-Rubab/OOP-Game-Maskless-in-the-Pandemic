#pragma once
#include <vector>
#include <string>
#include "entity.hpp"
#include <SDL.h>

/**
 * \brief this class is storing the collectible items that the main player has to collect in order ot win the game
 * It inherits from Entity Class
 */

class assignment:public Entity{
    bool collected=false; //whether the player has collected this object or not
    SDL_Texture* asset;
    float angle; //angle at which it is rendered at
    public:
    /**
     * This constructor is initializing the asignment with its texture, source, mover coordinates and its angle
     * \param a is the SDL_Texture pointer for the assignment's texture.
     * \param s is the SDL_Rect coordinates for object from the source image.
     * \param m is the SDL_Rect coordinates for mover assignment to be rendered on window.
     * \param n is the angle at which assignment is to be rendered.
     */

    assignment(SDL_Texture* a, SDL_Rect s, SDL_Rect m, float n);
    /**
     * This is a destructor for assignment class.
     */
    ~assignment();
    /**
     * This function updates the Assignment. 
     * It is the virtual function inherited from entity class.
     */
	void update();
    /** 
     * This function renders the Assignment on screen.
     */
	void render(SDL_Renderer *renderer);
    /**
     * This function calls the action when a player collects/collides with assignment.
     */
    void ifCollide();

};

