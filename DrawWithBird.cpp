#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#include <stdio.h>

// the width and height depend on the resolution ratio of backgroundImage
#define GRAPH_HEIGHT 512
#define GRAPH_WIDTH 288
#define PI 3.14159265359
#define SPEED_FACTOR 10

IMAGE base;
IMAGE back;
IMAGE TubeUp;
IMAGE TubeDown;
IMAGE BirdImages[3]; //0:down 1:mid 2:up
int tubeGap = 75;
int tubeWidth = 50;
int tubeMoveStep = 10 * SPEED_FACTOR;
int currentBase = 0;
int baseMoveStep = 10 * SPEED_FACTOR;
int createInterval = 2;
double refreshTime = 0.03;

// With Bird
double gravity = 30;
typedef struct BirdStruct {
	int x;
	int y;
	double v;
} Bird;

// Before
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
// Bird

Bird bird = {
	80, (GRAPH_HEIGHT - 112)/ 2, 0
};

void moveGround(double interval);
void loadTestImages(); // load Birds
void drawTubes(Tube*); // *********
void moveTubes(double interval);

void initRandom();
void getRandomGap(Tube*);
void createConstantTube();
void moveAllTubes(double interval);
void drawBackground();
void drawBase();
void drawAllTubes();
void draw();
void move(double interval);
TubesNode* deleteFirstTube();

// With Bird
void drawBird(int flap);
void moveBird(double interval); // Improve: when up and down
void wing();
int isClick();
// Test 
void WithTimeTest();

void main() {
	loadTestImages();
	initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);
	initRandom();

	int baseHeight = base.getheight();
	putimage(0, 0, &back);
	putimage(0, GRAPH_HEIGHT - baseHeight, &base);

	WithTimeTest();
}

void WithTimeTest() {
	clock_t startTime = clock();
	clock_t lastAddTube = startTime;
	while (true) {
		clock_t curTime = clock();
		while ((double)(curTime - startTime) / CLOCKS_PER_SEC < refreshTime) {   
			curTime = clock();
		}
		double interval = (double)(curTime - startTime) / CLOCKS_PER_SEC;
		move(interval);
		draw();
		if ((double)(curTime - lastAddTube) / CLOCKS_PER_SEC > createInterval) {
			createConstantTube();
			lastAddTube = curTime;
		}
		startTime = curTime;
		if (isClick()) {
			wing();
		}
		Sleep(10);
	}
}

int isClick() {
	MOUSEMSG msg;
	while (MouseHit()) {
		msg = GetMouseMsg();
		if (msg.mkLButton)
			return true;
	}
	return false;
}

void wing() {
	if (bird.v <= 0) {
		bird.v = 20;
	}
	else if (bird.v > 50)
		bird.v = 50;
	else {
		bird.v += 10;
	}
}

void drawBird(int flap) {
	putimage(bird.x, bird.y, &BirdImages[flap]);
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
	drawBird(1);
}

void move(double interval) {
	moveGround(interval);
	moveAllTubes(interval);
	moveBird(interval);
}

void moveBird(double interval) {
	bird.y -= bird.v * interval * SPEED_FACTOR;
	if (bird.y < 0) {
		bird.y = 0;
	}
	else if (bird.y > GRAPH_HEIGHT) {
		bird.y = GRAPH_HEIGHT;
	}
	bird.v -= gravity * interval;
	printf("Current v = %lf\n", bird.v);
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

void moveAllTubes(double interval) {
	TubesNode* node = tubes.head;
	while (node != NULL) {
		node->tube->xLeft -= tubeMoveStep * interval;
		node->tube->xRight -= tubeMoveStep * interval;

		if (node->tube->xRight <= 0) {
			node = deleteFirstTube();
		}
		else {
			node = node->next;
		}
	}
}

void drawAllTubes() {
	TubesNode* node = tubes.head;
	while (node != NULL) {
		drawTubes(node->tube);
		node = node->next;
	}
}

void createConstantTube() {
	Tube* tube = (Tube*)malloc(sizeof(Tube));
	TubesNode* node = (TubesNode*)malloc(sizeof(TubesNode));
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
	loadimage(&BirdImages[0], _T("images\\bluebird-downflap.png"));
	loadimage(&BirdImages[1], _T("images\\bluebird-midflap.png"));
	loadimage(&BirdImages[2], _T("images\\bluebird-upflap.png"));
}

void moveGround(double interval) {
	int baseHeight = base.getheight();
	int y = GRAPH_HEIGHT - baseHeight;
	currentBase -= baseMoveStep * interval;
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

