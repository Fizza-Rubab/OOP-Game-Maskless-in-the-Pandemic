#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <iostream>
#include <fstream>
#include <SDL_mixer.h>
#include "button.hpp"
#include "level.hpp"
#include "level2.hpp"
#include "story.hpp"
#include "entity.hpp"
#include "timer.hpp"
using namespace std;

//

/**
 * \brief This is the main game class where the game is initialized, the media is loaded and the game loop is run
 */

class game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    bool MusicOn=false;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;
    SDL_Texture* slides[4]{NULL, NULL, NULL, NULL};
    bool exit=false;
    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* howToPlay = NULL;
    SDL_Texture* mainScreen=NULL;
    SDL_Texture* r1[4];
    SDL_Texture* r2;
    SDL_Texture* playerS;
    SDL_Texture* buttonSheet=NULL;
    SDL_Texture* objSprites;
    SDL_Texture* CSOs;
    SDL_Texture* Collectible;
    SDL_Texture* cameraS;
    SDL_Texture* heart;
    SDL_Texture* WinLose[3];
    Timer *t;
    
  
    //for the buttons on the start screen
  
    button *bPlay=new button("Play Button", "Main Screen", SDL_Rect({435,465,197,58}),{285,240,190,60}, false);
    button *bOptions=new button("Options Button", "Main Screen", {255,981,277,56},{265,320,230,60}, false);
    button *bExit=new button("Exit Button", "Main Screen", {435,920,197,57},{285,400,190,60}, false);

    //background music
    Mix_Music *bgMusic2 = NULL;
    Mix_Music *bgMusic3 = NULL;
    



public:
    /**
     * This is tge default constructor of game which initializes the game welcome screen timer to 6seconds.
     */
    game():t(new Timer(6000)){}
    /** 
     * This method initializes all the relevant variables, SDL renderer, mixer, window, events etc.
     */
    bool init();
    /**
     * This method loads the media, spritesheets, music and textures in the respective variables.
     */
    bool loadMedia();
    /**
     * This method closes the game, frees the memory and sets all the textures back to NULL.
     */
    void close();
    /**
     * This method returns if the game exit key has been pressed or not.
     */
    bool isExit();
    /**
     * This method loads the game music from the respective file into the Mix_music* attributes.   
     */
    void loadGameMusic();
    /**
     * This method loads the welcome screen music from the respective file into the Mix_music* attributes.   
     */
    void loadWelcomeMusic();
    /**
     * This method shows the button onject attributes on the game welcome screen.   
     */
    void showButtons();
    /**
     * This method is used to return a SDL_Texture pointer by loading the file path passed as a parameter.
     */
    SDL_Texture* loadTexture( std::string path );
    /**
     * This method is used show the production screen and the game slides for a specific amount of time.
     */
    void showProdStory();
    /**
     * This method is used to show the game welcome screen with its respective buttons.
     */
    void runWelcomeScreen();
    /**
     * This method is used to run teh first level of teh game. Inputs by the user are passed to level1 function as paramter and output is written in the outfile.
     */
    void runGamePlayLevel1(Inputs inputs, ofstream& outfile);
    /**
     * This method is used to run the second level of teh game. Inputs by the user are passed to level2 function as paramter and output is written in the outfile.
     */
    void runGamePlayLevel2(Inputs inputs, ofstream& outfile);
    /**
     * This method is used to show the results of the first level. Whether player lost or won.
     * The output is written down in the output file.
     */
    void displayResultL1(Inputs inputs, string state, ofstream& outfile);
    /**
     * This method is used to show the results of the second level. Whether player lost or won.
     *  The output is written down in the output file.
     */
    void displayResultL2(string state);
};

