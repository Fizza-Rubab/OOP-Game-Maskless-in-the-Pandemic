#pragma once

#include <SDL.h>
#include "entity.hpp"
#include "roomObjects.hpp"
#include <string>
#include <map>

using namespace std;


/**
 * \brief this class is used for creating Campus security Officers (CSOs) from whom the player has to hide.
 * It inherits from Entity Class
 * In the radius of CSO s the health of player starts to decrrease.
 */

class CSO: public Entity {

    vector<vector<Entity*>> *entities;

    int direction = 0;

    SDL_Rect states[6];
    SDL_Texture* tex;
    float angle = 0;
    int frame = 0;
    double s = 20;
    SDL_Rect rad;
    /**
     * This private method is used to define the radius of the CSO and set its direction in which it is moving
     */
    void radius_define(int dir);

    

public:
	
    /**
     * This constructor is initializing the CSO ibject with a SDL_Texture the source coordinates of the CSO in the texture and the mover coordinates of the CSO on the screen windown.
     */

	CSO(SDL_Texture* p, SDL_Rect Src, SDL_Rect Mover);
    /**
     * This is the virtual function of the entity class that updates the entity in this case the CSO.
     */
	void update();
    /**
     * This method(virtual function of entity class) is used to render the CSO on screen through the SDK_Renderer that is passed as an argument.
     */
	void render(SDL_Renderer *renderer);
    /**
     * This method is used to check the collision of the CSO woth entitites in the curren room.
     * \param cr  is the current room index in which the CSO is currentlty in.
     */

    bool checkCollisionAll(int cr);
    /**
     * This method allows the movement of the CSO in a circular patrolling fashion in the current room.
     */
    void moverx(int cr);
    /**
     * This method returns the radius of the CSO in the form of a SDL_Rect
     */
    SDL_Rect get_rad();
	
};



