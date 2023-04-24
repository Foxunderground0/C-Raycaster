#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>

#define mapWidth 8
#define mapHeight 8
#define mapSize 64

using namespace std;

double posX = ((double) mapWidth/2.0)-0.52 ,posY= (double) mapHeight/2.0,phy=0.0;

int map[8][8]={{1,1,1,1,1,1,1,1}
				,{1,0,0,0,0,0,0,1}
				,{1,0,0,1,0,0,0,1}
				,{1,0,0,0,0,0,0,1}
				,{1,0,0,0,0,0,0,1}
				,{1,0,0,1,0,0,0,1}
				,{1,0,0,0,0,0,0,1}
				,{1,1,1,1,1,1,1,1}};


bool gridHasPlayer(int x, int y){
				if(((int)posX == x) && ((int)posY == y)){
								return true;
				}
				return false;
}

void drawPlayer(){
				//playe
				double highOrLow = posX - (double)((int)posX);

				if(highOrLow >= 0.5){
								cout << " " << "⣿";
				} else {
								cout << "⣿" << " ";
				}
}

void renderBuffer(){
				char displayBuffer[8][16]={" "};

				//Draw map on displayBuffer
				for(int _ = 0; _ < 8; _++){
								for(int __ = 0; __ < 8; __++){
												displayBuffer[_][__] = map[_][__];
								}
								cout << endl;
				}

				//Draw player
				//displayBuffer[posX][posY] = "⣿";

				//Draw displayBuffer
				for(int _ = 0; _ < 8; _++){
								for(int __ = 0; __ < 16; __++){
												if(!gridHasPlayer(_,__) || (_ >= 8)){
																if (displayBuffer[_][__]){
																				cout << "██";
																} else {
																				cout << "  ";
																}
												} else {
																drawPlayer();
												}
								}
								cout << endl;
				}
				cout << "-----------------------" << endl;
				cout << "posX: " << posX << " poxY: " << posY;

}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVENTS);

    //SDL_Window* window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                std::cout << "Hello World!" << std::endl;
            }
        }
        SDL_Delay(10);
    }

    //SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

/*
int main(){
				
				//while(1){
				renderBuffer();
				//}

				return 0;
} */
