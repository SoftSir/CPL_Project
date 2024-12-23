#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
/*
#define GRAPH_HEIGHT 512
#define GRAPH_WIDTH 288
#define PI 3.14159265359
// the width and height depend on the resolution ratio of backgroundImage

IMAGE base;
IMAGE back;
IMAGE TubeUp;
IMAGE TubeDown;
int tubeGap = 75;

void moveGround();
void loadTestImages();
void continueMove();
void drawTubes();
void moveTubes();
void moveAll();

void testmain() {
	loadTestImages();
	initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);
	DWORD* p = GetImageBuffer(&base);
	int baseHeight = base.getheight();
	putimage(0, 0, &back);
	putimage(0, GRAPH_HEIGHT - baseHeight, &base);
	drawTubes();
	_getch();
	moveGround();
	_getch();
	continueMove();
}

void loadTestImages() {
	loadimage(&base, _T("images\\base.png"));
	Resize(&base, GRAPH_WIDTH, base.getheight());
	loadimage(&back, _T("images\\background-day.png"));
	loadimage(&TubeDown, _T("images\\pipe-green.png"));
	Resize(&TubeDown, TubeDown.getwidth(), (GRAPH_HEIGHT - base.getheight() - tubeGap) / 2);
	rotateimage(&TubeUp, &TubeDown, PI);
}

void moveGround() {
	static int currentX = 0;
	int moveStep = 10;
	int baseHeight = base.getheight();
	int y = GRAPH_HEIGHT - baseHeight;    
	currentX -= moveStep;
	if (currentX + GRAPH_WIDTH <= 0) {
		currentX = 0;      
	}
	putimage(currentX, y, &base);
	putimage(GRAPH_WIDTH + currentX, y, &base);
}	

void continueMove() {
	while (true) {
		putimage(0, 0, &back);
		moveAll();
		_getch();
	}
}

void drawTubes() {
	int x = GRAPH_WIDTH;
	int hUp = 0;
	int hDown = TubeUp.getheight() + tubeGap;
	putimage(x, hUp, &TubeUp);
	putimage(x, hDown, &TubeDown);
}

void moveTubes() {
	static int x = GRAPH_WIDTH;
	int moveStep = 20;
	x -= moveStep;
	int hUp = 0;
	int hDown = TubeUp.getheight() + tubeGap;
	putimage(x, hUp, &TubeUp);
	putimage(x, hDown, &TubeDown);
}

void moveAll() {
	moveTubes();
	moveGround();
}

*/