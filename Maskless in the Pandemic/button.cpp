#include "button.hpp"


button::button(string n, string l, SDL_Rect s, SDL_Rect m, bool c):name(n),location(l), src(s), mover(m), isClicked(c){}   
void button::showButton(SDL_Renderer *gRenderer, SDL_Texture * asset){
    SDL_RenderCopy(gRenderer, asset, &src, &mover);
}

//to check if the button has been pressed or not and to change screen if it has been
bool button::checkPress(int x, int y){
    if (x>=mover.x && x<(mover.x+mover.w) && y>=mover.y && y<(mover.y +mover.h))
    return true;
    else return false;
    }