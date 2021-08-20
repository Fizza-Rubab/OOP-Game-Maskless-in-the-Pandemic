#pragma once
#include "story.hpp"
using namespace std;

//for playing music
void story::makeBgMusic(){
bgMusic = Mix_LoadMUS( "music.mp3" );
Mix_PlayMusic( bgMusic, 2 );
}

//for displaying story slide
void story::showSlide(SDL_Renderer* gRenderer, SDL_Texture* s[]){
    SDL_RenderClear(gRenderer);
    makeBgMusic();
    Uint32 timeout = SDL_GetTicks() + 7000;
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
        SDL_RenderCopy(gRenderer, s[0], NULL, NULL);
        SDL_RenderPresent(gRenderer); 
            
        }
    SDL_RenderClear(gRenderer);
    Uint32 timeout2 = SDL_GetTicks() + 7000;
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout2)) {
        SDL_RenderCopy(gRenderer, s[1], NULL, NULL);
        SDL_RenderPresent(gRenderer); 
            
    }
    SDL_RenderClear(gRenderer);
    Uint32 timeout3 = SDL_GetTicks() + 7000;
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout3)) {
        SDL_RenderCopy(gRenderer, s[2], NULL, NULL);
        SDL_RenderPresent(gRenderer); 
            
    }
    SDL_RenderClear(gRenderer);
    Uint32 timeout4 = SDL_GetTicks() + 7000;
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout3)) {
        SDL_RenderCopy(gRenderer, s[3], NULL, NULL);
        SDL_RenderPresent(gRenderer); 
            
    }
}

story::~story(){
    Mix_FreeMusic(bgMusic);
    bgMusic = NULL;
    //delete this;
}


