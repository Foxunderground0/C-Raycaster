#include <iostream>
#include <math.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

#define mapWidth 8
#define mapHeight 8
#define mapSize 64

#define numberOfRays 8;

using namespace std;


const double PI = 3.14159265358;

double posX = ((double) mapWidth/2.0)-0.52 ,posY= (double) mapHeight/2.0,phi=0.0;

int rays[] = {1,2,3,4,5,6,7,8};

int kbhit() {
	struct timeval tv = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) == 1;
}

int map[8][8]={{1,1,1,1,1,1,1,1}
	,{1,0,0,0,0,0,0,1}
	,{1,0,0,1,0,0,0,1}
	,{1,0,0,0,0,0,0,1}
	,{1,0,0,0,0,0,0,1}
	,{1,0,0,1,0,0,0,1}
	,{1,0,0,0,0,0,0,1}
	,{1,1,1,1,1,1,1,1}};

bool gridHasPlayer(int x, int y){
	//x = mapWidth - x;
	//y = mapHeight - y;

	if(((int)posX == x) && ((int)posY == y)){
		return true;
	}
	return false;
}

void playerDirection(){
	if((phi < PI/6) && (phi > -PI/6)){
		cout << "F";
	}
	
	if((phi > PI/6) && (phi < PI/3)){
		cout << "FL";
	}

	if((phi > PI/3) && (phi < 2*(PI/3))){
		cout << "L";
	}
	
	if((phi > 2*(PI/2)) && (phi < 5*(PI/6))){
		cout << "BL";
	}


        if((phi > 5*(PI/6)) && (phi > -5*(PI/6))){
                cout << "B";
        }

        if((phi < -5*(PI/6)) && (phi > -2*(PI/2))){
                cout << "BR";
        }

        if((phi < -2*(PI/2)) && (phi > -(PI/3))){
                cout << "R";
        }

        if((phi < -(PI/3)) && (phi > -(PI/6))){
                cout << "FR";
        }

}

void getInput(){
	char ch = getchar();
	// Check for simple WASD key presses
	if (ch == 'w') {
		cout << "Moving up" << endl;
		posY += sin(phi);
		posX += cos(phi);
	} else if (ch == 'a') {
		cout << "Moving left" << endl;
		phi -= 0.05;
		phi = remainder(phi,(PI * 2));
	} else if (ch == 's') {
		cout << "Moving down" << endl;
		posY -= sin(phi);
		posX -= cos(phi);
	} else if (ch == 'd') {
		cout << "Moving right" << endl;
		phi += 0.1;
		phi = remainder(phi,(PI * 2));
	} else if (ch == 'q') {
		//break;
	}
}

void drawPlayer(){
	//playe
	double highOrLow = posY - (double)((int)posY);

	if(highOrLow >= 0.5){
		cout << " ";
		playerDirection();
	} else {
		playerDirection();
		cout << " ";
	}
}


void renderBuffer(){
	int displayBuffer[8][16]={0};

	//Draw map on displayBuffer
	for(int _ = 0; _ < 8; _++){
		for(int __ = 0; __ < 8; __++){
			displayBuffer[_][__] = map[_][__];
		}
		//cout << endl;
	}

	//Draw player
	//displayBuffer[posX][posY] = "⣿";


	// Draw Rays
	for(int _ = 0; _ < 8; _++){
		for(int __ = 8; __ < 16; __++){
			if((__-8) > ((9-rays[(__-8)])/2)){
				displayBuffer[_][__] = 0;
			} else if ((__-8) <= ((9+rays[(__-8)])/2)){
				displayBuffer[_][__] = 1;
				//cout << __;
			}
		}
		
	}

	//Draw displayBuffer
	for(int _ = 0; _ < 8; _++){
		for(int __ = 0; __ < 16; __++){
			if(!gridHasPlayer(_,__) || (__ >= 8)){
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
	cout << "posX: " << posX << " poxY: " << posY << " phi: " << phi;

}

int main(){
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);



	while(1){
		if(kbhit()){
			renderBuffer();
			getInput();
		}
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return 0;
}
