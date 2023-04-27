#include <iostream>
#include <math.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

#define mapWidth 8
#define mapHeight 8
#define mapSize 64

using namespace std;

double posX = ((double) mapWidth/2.0)-0.52 ,posY= (double) mapHeight/2.0,phy=0.0;

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
	x = mapWidth - x;
	//y = mapHeight - y;

	if(((int)posX == x) && ((int)posY == y)){
		return true;
	}
	return false;
}

void getInput(){
	char ch = getchar();
	// Check for simple WASD key presses
	if (ch == 'w') {
		cout << "Moving up" << endl;
		posX += 0.1;
	} else if (ch == 'a') {
		cout << "Moving left" << endl;
		posY -= 0.1;
	} else if (ch == 's') {
		cout << "Moving down" << endl;
		posX -= 0.1;
	} else if (ch == 'd') {
		cout << "Moving right" << endl;
		posY += 0.1;
	} else if (ch == 'q') {
		//break;
	}
}

void drawPlayer(){
	//playe
	double highOrLow = posY - (double)((int)posY);

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
