#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
using namespace std;


/**
 * \brief this class is used for making buttons that are rendered on the main welcome screen of th game.
 * It inherits from Entity Class
 */

class button{
    string name;
    string location;
    SDL_Rect mover;
    SDL_Rect src;
    bool isClicked; //to store whether the button has been clicked or not
    public:
    /**
     * This constructor is initializing the button with a name location and  isClicked attribute.
     */

    button():name("None"),location("undecided"),isClicked(false){}
    button(string n, string l, SDL_Rect s, SDL_Rect m, bool c);

    /**
     * This method is rendering the button on screen using the button asset and the SDL_Renderer
     */
    void showButton(SDL_Renderer *gRenderer, SDL_Texture *asset);
    /**
     * This method is used to check if the button is pressed when user click on the screen.
     * If the mmouse click coordinates collide with the SDL_Rect of the button then this function will return true
     */
    bool checkPress(int x, int y);
};