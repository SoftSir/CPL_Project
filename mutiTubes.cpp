#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#include <stdio.h>

#define GRAPH_HEIGHT 512
#define GRAPH_WIDTH 288
#define PI 3.14159265359
// the width and height depend on the resolution ratio of backgroundImage
/*
IMAGE base;
IMAGE back;
IMAGE TubeUp;
IMAGE TubeDown;
int tubeGap = 75;
int tubeWidth = 50;
int startTime = (unsigned int) time(NULL);
int tubeMoveStep = 50;
int currentBase = 0;
int baseMoveStep = 10;

typedef struct TubeStruct {
	int xLeft;
	int width;
	int xRight;
	int gap[2];
	int gapHeight;
} Tube;

typedef struct TubesNodeStruct {
	Tube* tube;
	TubesNodeStruct* next;
} TubesNode;

typedef struct TubesStruct {
	int num;
	TubesNode* head;
} Tubes;

Tubes tubes = {
	0, NULL
};

void moveGround();
void loadTestImages();
void drawTubes(Tube*); // *********

void initRandom();
void getRandomGap(Tube*);
void createConstantTube();
void moveAllTubes();
void drawBackground();
void drawBase();
void drawAllTubes();
void draw();
void move();
TubesNode* deleteFirstTube();

// test function
void continueCreation();

void main() {
	loadTestImages();
	initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);
	initRandom();

	int baseHeight = base.getheight();
	putimage(0, 0, &back);
	putimage(0, GRAPH_HEIGHT - baseHeight, &base);

	
	for (int i = 0; i < 100; i++) {
		createConstantTube();
		draw();
		_getch();
		move();
		draw();
		_getch();
		move();
		draw();
		_getch();
		move();
	}
	createConstantTube();
	_getch();
	drawAllTubes();
	_getch();
}	

void drawBackground() {
	putimage(0, 0, &back);
}

void drawBase() {
	int y = GRAPH_HEIGHT - base.getheight();
	putimage(currentBase, y, &base);
	putimage(GRAPH_WIDTH + currentBase, y, &base);
}

void draw() {
	drawBackground();
	drawBase();
	drawAllTubes();
	// draw Bird
}

void move() {
	moveGround();
	moveAllTubes();
}

TubesNode* deleteFirstTube() {
	if (tubes.head == NULL) {
		return NULL;
	}
	TubesNode* next = tubes.head->next;
	free(tubes.head);
	tubes.head = next;
	tubes.num--;
	return next;
}

void moveAllTubes() {
	TubesNode* node = tubes.head;
	while (node != NULL) {
		node->tube->xLeft -= tubeMoveStep;
		node->tube->xRight -= tubeMoveStep;

		if (node->tube->xRight <= 0) {
			node = deleteFirstTube();
		}
		else {
			node = node->next;
		}
	}
}

void drawAllTubes() {
	TubesNode *node = tubes.head;
	while (node != NULL) {
		drawTubes(node->tube);
		node = node->next;
	}
}

void createConstantTube() {
	Tube *tube = (Tube*)malloc(sizeof(Tube));
	TubesNode *node = (TubesNode*)malloc(sizeof(TubesNode));
	tube->xLeft = GRAPH_WIDTH;
	tube->width = tubeWidth;
	tube->xRight = tube->xLeft + tube->width;
	tube->gapHeight = tubeGap;
	getRandomGap(tube);

	node->tube = tube;
	node->next = NULL;

	if (tubes.head == NULL) {
		tubes.head = node;
	}
	else {
		TubesNode* current = tubes.head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = node;
	}
	tubes.num++;
}

void initRandom() {
	srand((unsigned int)time(NULL));
}

void getRandomGap(Tube* ptube) {
	int upper = rand() % (GRAPH_HEIGHT - base.getheight() - tubeGap);
	int lower = upper + tubeGap;
	ptube->gap[0] = upper;
	ptube->gap[1] = lower;
}

void loadTestImages() {
	loadimage(&base, _T("images\\base.png"));
	Resize(&base, GRAPH_WIDTH, base.getheight());
	loadimage(&back, _T("images\\background-day.png"));
	loadimage(&TubeDown, _T("images\\pipe-green.png"));
	rotateimage(&TubeUp, &TubeDown, PI);
}

void moveGround() {
	int baseHeight = base.getheight();
	int y = GRAPH_HEIGHT - baseHeight;
	currentBase -= baseMoveStep;
	if (currentBase + GRAPH_WIDTH <= 0) {
		currentBase = 0;
	}
}


void drawTubes(Tube* tube) {
	IMAGE upTemp, downTemp;
	rotateimage(&upTemp, &TubeDown, 0);
	rotateimage(&downTemp, &TubeDown, 0);
	int x = tube->xLeft;
	int hUp = tube->gap[0];
	int hDown = tube->gap[1];

	Resize(&upTemp, upTemp.getwidth(), hUp);
	rotateimage(&upTemp, &upTemp, PI);
	Resize(&downTemp, downTemp.getwidth(), GRAPH_HEIGHT - base.getheight() - hDown);
	putimage(x, 0, &upTemp);
	putimage(x, hDown, &downTemp);

}
*/

