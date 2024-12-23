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
#define BIRD_X 80

// �������
typedef struct BirdStruct {
	int x;						// ˮƽ����
	int y;						// ��ֱ����
	double v;					// ��ֱ������ٶȣ�����0����
} Bird;

/*
	��������洢���йܵ�
*/
typedef struct TubeStruct {		// �����ܵ�������
	int xLeft;					// ���Ե����
	int width;					// �ܵ�ˮƽ���
	int xRight;					// �ұ�Ե����
	int gap[2];					// �ܵ���϶���ڵ�y���꣬gap[0]Ϊ�ϱ�Ե��gap[1]Ϊ�±�Ե
	int gapHeight;				// �ܵ���϶�ĸ߶�
	double nothing;
} Tube;

typedef struct TubesNodeStruct {// �����ܵ�������ڵ�
	Tube* tube;
	struct TubesNodeStruct* next;
} TubesNode;

typedef struct TubesStruct {	// �������йܵ���
	int num;					// ����
	TubesNode* head;			// ͷ��㣨��ΪNULLʱ�ǵ�һ��Ԫ�أ�
} Tubes;

// ������Ҫ���ص�ͼ��
IMAGE base;
IMAGE back;
IMAGE TubeUp;
IMAGE TubeDown;
IMAGE BirdImages[3]; //0:down 1:mid 2:up

// ��������
int tubeGap = 75;						// �ܵ���϶�߶�
int tubeWidth = 50;						// �ܵ���϶���
int tubeMoveStep = 10 * SPEED_FACTOR;	// ÿ���ƶ�ʱ�ܵ���ÿ���ƶ�����
int currentBase = 0;					// ���ڵĵ���ͼ������꣨�����ڻ�ͼ��
int baseMoveStep = 10 * SPEED_FACTOR;	// ����ÿ���ƶ�����
int createInterval = 2;					// �����¹ܵ���ʱ����
double refreshTime = 0.03;				// ˢ�½����ʱ�䣨�����»��ƣ�
double gravity = 30;					// �������ٶ�

// ���йܵ�������
Tubes tubes = {
	0, NULL
};

// ��ʵ��
Bird bird = {
	BIRD_X, (GRAPH_HEIGHT - 112)/ 2, 0
};

// ���ֳ�ʼ��
void loadTestImages();		// ��������ͼƬ
void initRandom();			// �����������ʹ��rand()���һ�������
void createConstantTube();	// ����һ���µĹܵ�
void getRandomGap(Tube*);	// Ϊ�ܵ���϶����ȡ���ֵ

/*
	�ƶ���Ϸ�е��������������interval�����ʱ����
*/
void move(double interval);			// �ƶ��������
void moveGround(double interval);	// �ƶ�����
void moveAllTubes(double interval);	// �ƶ����йܵ�
TubesNode* deleteFirstTube();		// ɾ����һ���ܵ�
void moveBird(double interval); // Improve: when up and down

/*
*	��ͼ����
*/	
void draw();			// �����������
void drawTubes(Tube*);	// ����ָ���ܵ�
void drawBackground();	// ���Ʊ���
void drawBase();		// ���Ƶ���
void drawAllTubes();	// �������йܵ�
void drawBird(int flap);

/*
	��Ϸʱ���躯��
*/
void wing();
int isClick();
int isHit(); //*********
int isDie(); //*********

// Test 
void WithTimeTest();

// help function
void printTubesAndBird() {
	TubesNode* node = tubes.head;
	int i = 0;
	while (node != NULL) {
		printf("Bird.x = %d		Bird.y = %d\n", bird.x, bird.y);
		printf("Node %d:\n", i);
		printf("\txleft = %d\n\txright = %d\n\tupper = %d\n\tlower = %d\n",\
			node->tube->xLeft, node->tube->xRight, node->tube->gap[0], node->tube->gap[1]);
		node = node->next;
		i++;
	}
	printf("\n\n\n");
}


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
	while (!isDie()) {
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
		printTubesAndBird();
		Sleep(10);
	}
	draw();
	printf("Game Over!\n");
	_getch();
}


int isHit() {
	TubesNode* node = tubes.head;
	if (node == NULL)
		return 0;

	int left = node->tube->xLeft;
	int right = node->tube->xRight;
	if (left > bird.x || right < bird.x)
		return 0;
	
	int upper = node->tube->gap[0];
	int lower = node->tube->gap[1];
	if (bird.y < upper && bird.y > lower) {
		printf("***************Successful!*************");
		return 0;
	}
	else
		return 1;
}

int isDie() {
	if (isHit() || bird.y >= GRAPH_HEIGHT - base.getheight()) {
		return 1;
	}
	return 0;
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
	else if (bird.y > GRAPH_HEIGHT - base.getheight()) {
		bird.y = GRAPH_HEIGHT - base.getheight();
	}
	bird.v -= gravity * interval;
}

TubesNode* deleteFirstTube() {
	if (tubes.head == NULL) {
		return NULL;
	}
	TubesNode* next = tubes.head->next;
	free(tubes.head->tube);
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

void createConstantTube() {
	Tube* tube = (Tube*) malloc(sizeof(Tube));
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

void moveGround(double interval) {
	int baseHeight = base.getheight();
	int y = GRAPH_HEIGHT - baseHeight;
	currentBase -= baseMoveStep * interval;
	if (currentBase + GRAPH_WIDTH <= 0) {
		currentBase = 0;
	}
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