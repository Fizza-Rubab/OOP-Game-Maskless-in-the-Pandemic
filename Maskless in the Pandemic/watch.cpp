#include "watch.hpp"
#include <string.h>


watch::watch(){}
watch::watch(SDL_Texture* alrm, int min): alTex(alrm), TotalWatches(min), MaxWatches(min){
    MoverWatches[0] = {280,60,35,35};
    for (int i = 1; i <TotalWatches; i++){

        MoverWatches[i] = {((MoverWatches[i-1]).x+=40), 60, 35, 35};
    }
}

//update the game clocks
void watch::update(Uint32 time){
    TotalWatches=(MaxWatches*60000-time)/60000;
}
//rendering clocks
void watch::render(SDL_Renderer *renderer, int count) {
    SDL_RenderCopy(renderer, alTex, &Src, &MoverWatches[count]);
    SDL_RenderPresent(renderer);
}
//return the game clocks
int watch::getClocks(){
    return TotalWatches;
}