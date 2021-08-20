#pragma once

#include <SDL.h>
#include <cmath>
/**
 *  \brief This class is used for generating and displaying clocks corresponding to the timer indicating how much time is left in the level2 of the game.
 */

class watch{
    //Spritesheet texture
    SDL_Texture* alTex;
    //Total number of minutes/clocks
    int MaxWatches; 
    //storing curent total no of watches
    int TotalWatches;
    //source coordinates on the texture
    SDL_Rect Src = {688,267,212,229};
    SDL_Rect MoverWatches[4];

public:
    /**
     * This is the default no paramter constructor for a watch
     */
    watch();
    /**
     * This is the constructor for a watch which intializes it with it's Spritesheet texture and tells the total time or clocks in the game
     */
	watch(SDL_Texture* w, int nWatches);
    /**
     * This method renders and dispays the clock on screen
     */
	void render(SDL_Renderer *renderer, int count);
    /**
     * This method updates the watch and decrements the totalwatches everytime 1 minute has passed by checking the curren time passsed as a parameter.
     */
    void update(Uint32 time);
    /**
     * This method returns the total no of clocks/minutes left in the level
     */
    int getClocks(); 
};
