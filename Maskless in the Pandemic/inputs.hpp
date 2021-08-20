#ifndef INPUTS_H
#define INPUTS_H

#include <SDL.h>

// KEY CODE DEFINITIONS

#define KEY_P_MOVE_UP      SDL_SCANCODE_UP
#define KEY_P_MOVE_DOWN    SDL_SCANCODE_DOWN
#define KEY_P_MOVE_LEFT    SDL_SCANCODE_LEFT
#define KEY_P_MOVE_RIGHT   SDL_SCANCODE_RIGHT
#define KEY_P_OPEN_DOOR   SDL_SCANCODE_SPACE

//for taking the key inputs from the player


/**
* \brief This class is for the managing the inputs passed by the user to the game
*/
class Inputs {

	bool quit;
	int mouse_x;
	int mouse_y;
	bool isStatic;
	// Boolean array for all keys.
	const Uint8 *key_states;
	/**
	 * This private method checks if the ESC or 'X' button is pressed and returns true or false
	 */
	bool check_for_quit(SDL_Event event);

public:
	/**
	 * This is the default no paramater constructor for input class.
	 */
	Inputs();

	/**
	 * This method is used to update the inputs.
	 */
	void update();
	
	/**
	 * This method is used to return true when no key has been pressed by the user
	 */
	bool noKeyPressed();
	/**
	 * This method is used to handle the quit functionality.
	 * It checks has the ESC key or 'X' button been pressed?
	 */
	bool get_quit();
	/**
	 * This method is used to check if a paricular key referring to the keys defined above has been pressed or not.
	 */
	bool is_key_down(int key);

};

#endif