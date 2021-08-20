#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_mixer.h>
using namespace std;
/**
 *  \brief This class is used to create and display the background story of the game.
 */

class story{
    //Background music
    Mix_Music *bgMusic = NULL;
    
    public:
    /**
     * This method is used to play the background msuic while story is being displayed.
     */
    void makeBgMusic();
    /**
     * This method is used to display each slide of the story after a 6s interval
     * it takes in the loaded SDL_Textures for each of the slode in form of array
     * It uses SDL_renderer passed asa paramter to display all slides
     */
    void showSlide(SDL_Renderer* gRenderer, SDL_Texture* s[]);
    /**
     * This is a destryctor used to deallocated any dynaic memory used in this class.
     */
    ~story();
};

