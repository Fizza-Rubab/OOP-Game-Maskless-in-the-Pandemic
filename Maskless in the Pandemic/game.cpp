#include "game.hpp"

//for initialization of game
bool game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "HU Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
				Mix_AllocateChannels(32);				
			}
		}
	}

	return success;
}

//for loading game media
bool game::loadMedia()

{
	//Loading success flag
	bool success = true;
	//Assets loading
	mainScreen=loadTexture("Welcome Screen.png");
    gTexture = loadTexture("Production Screen.png");
	buttonSheet = loadTexture("bt1.png");
	slides[0]=loadTexture("Background Story/Slide1.png");
    slides[1]=loadTexture("Background Story/Slide 2.png");
    slides[2]=loadTexture("Background Story/slide 3 .png");
	slides[3]=loadTexture("Background Story/Slide 4.png");
	howToPlay=loadTexture("Background Story/Slide 4.png");
	r1[0]=loadTexture("rooms/1.jpg");
	r1[1]=loadTexture("rooms/2.jpg");
	r1[2]=loadTexture("rooms/3.jpg");
	r1[3]=loadTexture("rooms/4.jpg");
	r2=loadTexture("rooms/l2.png");
	playerS=loadTexture("player.png");
	objSprites=loadTexture("assets.png");
	CSOs = loadTexture("asset.png");
	Collectible = loadTexture("assignment.png");
	cameraS=loadTexture("camera.png");
	heart=loadTexture("heart.png");
	WinLose[0]=loadTexture("Win.jpg");
	WinLose[1]=loadTexture("Lose.jpg");
	WinLose[2]=loadTexture("l1.png");
	
	if(mainScreen==NULL || gTexture==NULL||playerS==NULL||WinLose[0]==NULL||WinLose[1]==NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	return success;	
	//return success;
}

//for showing buttons on the screen
void game::showButtons(){
	bPlay->showButton(gRenderer, buttonSheet);
	bOptions->showButton(gRenderer, buttonSheet);
	bExit->showButton(gRenderer, buttonSheet);
	}

//for closing the game
void game::close()
{
	//Free loaded images
	SDL_DestroyTexture(buttonSheet);
	buttonSheet=NULL;
	SDL_DestroyTexture(mainScreen);
	mainScreen=NULL;
	SDL_DestroyTexture(gTexture);
	Mix_FreeMusic(bgMusic2);
	Mix_FreeMusic(bgMusic3);
	bgMusic2 = NULL;
	bgMusic3 = NULL;
	//Quit SDL subsystems
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	Mix_Quit();
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//for loading the texture on the window
SDL_Texture* game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

//to exit the game
bool game::isExit(){
	return exit;
}

//to show the production screen in the start of the game
void game::showProdStory(){
	SDL_Event e;
	story s;
	bool prodCheck=false;
	bool quit=false;
	bool slidesCheck=false;
	//While application is running
	while( !quit )
	{
		//Handle events on queue
		 while( SDL_PollEvent( &e ) != 0 )
		 {
		 	//User requests quit
		 	if( e.type == SDL_QUIT )
		 	{
				exit=true;
				quit = true;
				
		 	}
			if (!prodCheck){
				SDL_RenderClear(gRenderer); //removes everything from renderer
				Uint32 timeout = SDL_GetTicks() + 5000;
				while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
				SDL_RenderPresent(gRenderer); 
				prodCheck=true;
				}
			}
			if (prodCheck && !slidesCheck){
				SDL_RenderClear(gRenderer); //removes everything from renderer
				s.showSlide(gRenderer, slides);
				SDL_RenderPresent(gRenderer); 
				slidesCheck=true;
				quit=true;
			}
		}
	}
	s.~story();
	for (int i=0;i<4;i++){
		SDL_DestroyTexture(slides[i]);
	}
}

//for loading the music in the start of the game
void game::loadWelcomeMusic(){
	Mix_Music *bgMusic2 = Mix_LoadMUS( "music.mp3" );
    Mix_PlayMusic( bgMusic2, 3 );
}	

//for loading the music while the game is running
void game::loadGameMusic(){
	Mix_Music *bgMusic3 = Mix_LoadMUS( "main.mp3" );
    Mix_PlayMusic( bgMusic3, 4 );
}

//for running the Welcome Screen or the start screen
void game::runWelcomeScreen()
{
	SDL_RenderClear( gRenderer );
	bool disable=false;
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	loadGameMusic();
	
	
	//While application is running
	while( !quit )
	{
		//Handle events on queue
		 while( SDL_PollEvent( &e ) != 0 )
		 {
		 	//User requests quit
		 	if( e.type == SDL_QUIT )
		 	{
				exit=true;
				quit = true;
				
		 	}

		if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
            int xMouse, yMouse;
			SDL_GetMouseState(&xMouse,&yMouse);
            if (bPlay->checkPress(xMouse, yMouse)){
			quit=true;
			}
			if (bOptions->checkPress(xMouse, yMouse)){
			Uint32 timeout5 = SDL_GetTicks() + 6000;
        	while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout5)) {
			SDL_RenderCopy(gRenderer, howToPlay, NULL, NULL);
			SDL_RenderPresent(gRenderer); 
		}
		}
			if (bExit->checkPress(xMouse, yMouse))
			quit=true;

				
		}
		}
		SDL_RenderClear(gRenderer); //removes everything from renderer
		SDL_RenderCopy(gRenderer, mainScreen, NULL, NULL);
		showButtons();
		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds

			
	}
}
		

//for running level 1
void game::runGamePlayLevel1(Inputs inputs, ofstream& outfile)
{

	outfile<<"Level 1 has begun \n"<<"Player currently in room 0 \n";
    SDL_RenderClear( gRenderer );
	level l1(r1, playerS, objSprites, CSOs, Collectible,cameraS, heart);
	//screen time
	bool disable=false;
	string state;
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	//While application is running
	while( !quit )
	{
		
		//currentTime = SDL_GetTicks();
		 while( SDL_PollEvent( &e ) != 0 )
		 {
		 	//User requests quit
		 	if( e.type == SDL_QUIT )
		 	{
				exit=true;
		 		quit = true;
		 	}
			inputs.update();
			if (inputs.get_quit()){
			exit=true;
			quit=true;
			}
		 }
			//if (i==5000) quit=true;
		SDL_RenderClear(gRenderer); //removes everything from renderer
		loadGameMusic();
	
		l1.startLevel(gRenderer, &inputs, quit, outfile);
		state=l1.getLevelState();
		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
	//i++;
	}
	//l1.~level();
	outfile<<"Game is "<<state<<endl;
	return displayResultL1(inputs, state, outfile);
			
}

//for displaying level 1 results both on the screen and by writing to a file
void game::displayResultL1(Inputs inputs, string state, ofstream& outfile){
	SDL_RenderClear( gRenderer );
	t->startTimer();
	loadWelcomeMusic();
	//screen time
	bool disable=false;
	//Main loop flag
	bool quit = false;
	Uint32 currentTime;
	//Event handler
	SDL_Event e;
	//While application is running
	while( !quit )
	{
		//currentTime = SDL_GetTicks();
		currentTime=t->getTime();
		 while( SDL_PollEvent( &e ) != 0 )
		 {
		 	//User requests quit
		 	if( e.type == SDL_QUIT )
		 	{
				exit=true;
		 		quit = true;
		 	}
		 }
			//if (i==5000) quit=true;
		if (t->shouldStop(currentTime))
		quit=true;
		SDL_RenderClear(gRenderer); //removes everything from renderer
		if (state=="Won")
		SDL_RenderCopy(gRenderer, WinLose[2], NULL, NULL);
		else if (state=="Lost")
		SDL_RenderCopy(gRenderer, WinLose[1],  NULL, NULL);
		loadGameMusic();
		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
	}
	delete t;
	if (state=="Lost") 
	return runWelcomeScreen();
	else if (state=="Won") 
	return runGamePlayLevel2(inputs, outfile);		
}

//for running level 2
void game::runGamePlayLevel2(Inputs inputs, ofstream& outfile)
{

	outfile<<"Level 2 has begun \n"<<"Player currently in room 0 \n";
 
    SDL_RenderClear( gRenderer );
	level2 l(r2, playerS, objSprites, CSOs, Collectible,cameraS, heart);
	//screen time
	bool disable=false;
	string state;
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	//While application is running
	while( !quit )
	{
		
		//currentTime = SDL_GetTicks();
		 while( SDL_PollEvent( &e ) != 0 )
		 {
		 	//User requests quit
		 	if( e.type == SDL_QUIT )
		 	{
				exit=true;
		 		quit = true;
		 	}
			inputs.update();
			if (inputs.get_quit()){
			exit=true;
			quit=true;
			}
		 }
			//if (i==5000) quit=true;
		SDL_RenderClear(gRenderer); //removes everything from renderer
		loadGameMusic();
	
		l.startLevel(gRenderer, &inputs, quit, outfile);
		state=l.getLevelState();
		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
	//i++;
	}
	//l.~level2();
	outfile<<"Level 2 is "<<state<<endl;
	return displayResultL2(state);	
}

//for displaying level 2 results
void game::displayResultL2(string state){
	SDL_RenderClear( gRenderer );
	t->startTimer();
	loadWelcomeMusic();
	//screen time
	bool disable=false;
	//Main loop flag
	bool quit = false;
	Uint32 currentTime;
	//Event handler
	SDL_Event e;
	//While application is running
	while( !quit )
	{
		
		currentTime=t->getTime();
		 while( SDL_PollEvent( &e ) != 0 )
		 {
		 	//User requests quit
		 	if( e.type == SDL_QUIT )
		 	{
				exit=true;
		 		quit = true;
		 	}
		 }
			//if (i==5000) quit=true;
		if (t->shouldStop(currentTime))
		quit=true;
		SDL_RenderClear(gRenderer); //removes everything from renderer
		if (state=="Won")
		SDL_RenderCopy(gRenderer, WinLose[0], NULL, NULL);
		else if (state=="Lost")
		SDL_RenderCopy(gRenderer, WinLose[1],  NULL, NULL);
		loadGameMusic();
		SDL_RenderPresent(gRenderer); //displays the updated renderer
		SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
	}
	delete t;
	return runWelcomeScreen();	
}
