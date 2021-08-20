#pragma once
#include <vector>
#include <string>
#include "entity.hpp"
#include <SDL.h>
// for generating camera object and the camera radar



/**
 * \brief this class is used for generating the camera object and its radar under which the player health starts to decrease.
 * It inherits from Entity Class
 */

class camera:public Entity{
    SDL_Texture* asset;
    float angle;
    public:
    /**
     * This constructor is initializing the camera with a SDL_Texture the source coordinates of the camera in the texture and the mover coordinates of the camera on the screen window and an angle n at which it will be displayed on screen.
     */

    camera(SDL_Texture* a, SDL_Rect s, SDL_Rect m, float n);
    /**
     * This is the destructor for the camera class object.
     */
    ~camera();
    /**
     * This is the virtual function of thge entity class that updates the entity in this case the camera.
     */
	void update();
    /**
     * This method(virtual function of entity class) is used to render the camera on screen through the SDK_Renderer that is passed as an argument.
     */
	void render(SDL_Renderer *renderer);
    /**
     * This method is used to check collision of the camera with an enoty passed as a function parameter.
     */
    bool checkCollision(Entity * e);

};

