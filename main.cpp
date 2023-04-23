#include <iostream>
#include <math.h>

#define mapWidth 8
#define mapHeight 8
#define mapSize 64

using namespace std;

double posX=0.0,posY=0.0,phy=0.0;

int map[8][8]={{1,1,1,1,1,1,1,1}
				,{1,0,0,0,0,0,0,1}
				,{1,0,0,1,0,0,0,1}
				,{1,0,0,0,0,0,0,1}
				,{1,0,0,0,0,0,0,1}
				,{1,0,0,1,0,0,0,1}
				,{1,0,0,0,0,0,0,1}
				,{1,1,1,1,1,1,1,1}};

char displayBuffer[16][16]={0};

void renderBuffer(){
				for(int _ = 0; _ < 16; _++){
								for(int __ = 0; __ < 16; __++){
												if (displayBuffer[_][__]){
																cout << "█";
												} else {
																cout << " ";
												}
								}
								cout << endl;
				}
				cout << "-----------------------" << endl;
}

int main(){
				while(1){
								for(int _ = 0; _ < 16; _++){
												for(int __ = 0; __ < 16; __++){
																if (displayBuffer[_][__]){
																				cout << "█";
																} else {
																				cout << " ";
																}
												}
												cout << endl;
								}
								cout << "-----------------------" << endl;
				}

				return 0;
}
