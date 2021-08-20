

#include "game.hpp"
#include "inputs.hpp"
#include <iostream>
#include <fstream>
/**
* the main function from where the program starts 
*/
int main(int argc, char *argv[]){
    //game object 
    game game;
    //file to store game status and how much of the game the player has completed
    ofstream outfile("Game State Records.txt"); 
    srand(time(NULL));

    //initializing game
    if( !game.init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}
	//Load media
    if( !game.loadMedia() ){
        printf( "Failed to load media!\n" );
        return 0;
    }
    
    game.showProdStory();
    if (game.isExit())
        game.close();
    else
        game.runWelcomeScreen();
    if (game.isExit())
        game.close();
    else
    {
        Inputs inputs;
        game.runGamePlayLevel1(inputs, outfile);
    }
    //closing the game if exit has been pressed
    if (game.isExit())
        game.close();
    //Closing the output file
    outfile.close();
    
}