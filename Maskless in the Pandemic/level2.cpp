#pragma once
#include "level2.hpp"

level2::level2( SDL_Texture *r, SDL_Texture *P, SDL_Texture *O, SDL_Texture *CS, SDL_Texture* As, SDL_Texture* Cam,  SDL_Texture* Al){
   //generating all objects for that level
    t1=new Timer(limit);
    w=watch(Al, 4);
    cameras={new camera(Cam, {26, 13, 184,159}, {20,430,180,140}, 0),
    new camera(Cam, {26, 13, 184,159}, {20,5,180,140}, 0),
    new camera(Cam, {26, 13, 184,159}, {630,130,140,180}, 90),
        new camera(Cam, {26, 13, 184,159}, {30,390,180,140}, 0)};
    roomObjects={
        {new roomObj(O,{118,169, 160,160},{635,30,150,150}, 0),new roomObj(O,{9,23,211,90}, {275, 10,250,110},0),new roomObj(O,{442,335,223,168}, {290,180, 250,195},0),new roomObj(O,{397,942,157,146}, {30,268, 100,100},0)}
        ,{new roomObj(O,{432,59, 190,213},{620,370,160,190}, 0),new roomObj(O,{238,13,194,92}, {30,505,180, 100},180),new roomObj(O,{26,848,156,100}, {330,220, 200,150},0),new roomObj(O,{246,849,108,34}, {10,250, 130,80},270)}
        ,{new roomObj(O,{118,169, 160,160},{620,30,150,150}, 0),new roomObj(O,{9,23,211,90}, {500, 480,250,110},180),new roomObj(O,{442,335,223,168}, {290,180, 250,195},0),new roomObj(O,{9,524,259,131}, {-25,420, 220,100},270)}
        ,{new roomObj(O,{118,169, 160,160},{635,5,150,150}, 0),new roomObj(O,{9,524,259,131}, {270,490, 220,100},180), new roomObj(O,{394,543,287,199}, {300,190, 250,200},0),new roomObj(O,{598,836,91,331}, {200,-10, 80,180},90)}
        };
    collectibles={
        {new assignment(As,{417,53, 241,149},{100,200,70,50}, 0),new assignment(As,{41,2,186,251}, {550, 420,100, 140},0)}
        ,{new assignment(As,{49,293, 216,146},{400,120,150,70}, 0),new assignment(As,{383,230,275,209}, {630, 30,150, 100},0)}
        ,{new assignment(As,{52,508, 213,179},{20,20,130,70}, 0),new assignment(As,{383,469,265,262}, {680, 280, 80, 80},0)}
        ,{new assignment(As,{52,731, 202,189},{530,300,150,70}, 0),new assignment(As,{379,760,268,185}, {110, 500,120, 70},0)}
        };
    
    lrooms[0]=new room(r,{0,0, 800, 600}, {0,0,800,600}, 0, {380,580,20,30}, roomObjects[0], collectibles[0]);
    lrooms[1]=new room(r,{800,0, 800, 600}, {0,0,800,600}, 1, {380,580,20,30}, roomObjects[1], collectibles[1]);
    lrooms[2]=new room(r,{0,600, 800, 600}, {0,0,800,600}, 2, {20,290,20,30}, roomObjects[2], collectibles[2]);
    lrooms[3]=new room(r,{800,600, 800, 600}, {0,0,800,600}, 3, {380,10,20,30}, roomObjects[3], collectibles[3]);
    entities.push_back(new Player(P, {857,837,271,233},  {550,250, 60,60}, &roomObjects, &collectibles, Al));
    entities.push_back(new CSO(CS, {857,837,271,233}, {95,380,120,120}));
    t1->startTimer();

}
void level2::startLevel(SDL_Renderer * gRenderer, Inputs *inputs, bool &quit, ofstream& outfile){
    Uint32 currentTime=t1->getTime();
    w.update(currentTime);
    if (t1->shouldStop(currentTime) || (w.getClocks()==0)|| !(((Player*)entities[0])->is_alive()) ){
        t1->stopTimer();
        state="Lost";
        quit=true;
        return;
    }
    if (((Player*)entities[0])->allItemsCollected()){
        t1->stopTimer();
        state="Won";
        quit=true;
        return;
    }
    if (lrooms[curr_room]->doorLeave(((Player*)entities[0]))){
        curr_room++;
        outfile<<"Player currently in room "<<curr_room<<endl;
        outfile<<"Assignments left "<<((Player*)entities[0])->getAssignments()<<endl;
        outfile<<"Health left "<<((Player*)entities[0])->getHealth()<<endl;
    
    }
        lrooms[curr_room]->showRoom(gRenderer);
        ((Player*)entities[0])->handle_inputs(inputs, lrooms[curr_room]->getDoor(), cameras[curr_room],((CSO*)entities[1])->get_rad(), curr_room);
        ((Player*)entities[0])->render(gRenderer);
        ((CSO*)entities[1])->moverx(curr_room);
        ((CSO*)entities[1])->render(gRenderer);
        cameras[curr_room]->render(gRenderer);
        for (int i =0; i<w.getClocks() ; i++){
            w.render(gRenderer, i);
            //SDL_RenderPresent(gRenderer);
        }
        SDL_RenderPresent(gRenderer); 
    }
string level2::getLevelState(){
    return state;
}
level2::~level2(){
    t1->~Timer();
    delete t1;
    int i=0;
    int sz=roomObjects.size();
    while (i<sz){
    for ( Entity* indic : roomObjects[i]){
        delete indic;
        indic = NULL;
    }
    i++;
    }
    i=0;
    sz=collectibles.size();
    while (i<sz){
    for ( Entity* indic : collectibles[i]){
        delete indic;
        indic = NULL;
    }
    i++;
}
    for ( Entity* b : entities){
    delete b;
    b = NULL;
    }
    for ( camera* c : cameras){
    delete c;
    c = NULL;
    }
    for ( room* r : lrooms){
    delete r;
    r = NULL;
    }
}
