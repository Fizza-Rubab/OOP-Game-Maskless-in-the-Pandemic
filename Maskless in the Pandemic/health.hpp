#pragma once
#include <SDL.h>
#include <iostream>
#include <cmath>
using namespace std;


/**
* \brief This class is for the health or lives of the player in a particular level of the game/
*/
class health{
    SDL_Texture* alTex;  //spriteSheet texture
    float TotalLives=10; //total no of lives
    SDL_Rect Src = {250,71,417,386};
    SDL_Rect MoverLives[10];

public:
    /**
     * This constructor is used to initialize a health objet by passing it a loaded texture for its image and the total number of lives of payer.
     */
	health(SDL_Texture* alrm, float Lives);
    /**
     * This method is used to display the health on the top of game screen.
     * It takes in a SDL_Renderer and the number of lives count as paramters.
     */
	void render(SDL_Renderer *renderer, int count);
    /**
     * This is a overloaded operator method that is used to inccrement the total Lives by a certain float value
     */
    void operator += (float val);
    /**
     * This is a overloaded operator method that is used to decrement the total Lives by a certain float value
     */
    void operator -=(float val);
    /**
     * This is a overloaded friend function method that is used to round the health by rounding the total Lives to a whole number and returning the whole number.
     */
	friend int round(health h); 
    /**
     * This is a overloaded friend extraction operator method that is display total lives in health object.
     */
    friend ostream &operator<<( ostream &output, const health &h ) { 
         output << h.TotalLives;
         return output;
         }
};
