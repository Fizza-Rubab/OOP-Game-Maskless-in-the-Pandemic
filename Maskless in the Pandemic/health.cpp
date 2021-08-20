#include "health.hpp"
#include <string.h>

//for returning the total lives left of player
int round(health hea){
    return round(hea.TotalLives);
}

health::health(SDL_Texture* alrm, float lives): alTex(alrm), TotalLives(lives){
    MoverLives[0] = {190,15,35,35};
    for (int i = 1; i < round(TotalLives); i++){

        MoverLives[i] = {((MoverLives[i-1]).x+=35), 15, 35, 35};
    }

}

//operator overloads for increasing and decreasing health of player
void health:: operator += (float val){
        TotalLives+=val;
}

void health:: operator -= (float val){
        TotalLives-= val;
}
void health::render(SDL_Renderer *renderer, int count) {
    SDL_RenderCopy(renderer, alTex, &Src, &MoverLives[count]);
    //SDL_RenderPresent(renderer);
}

