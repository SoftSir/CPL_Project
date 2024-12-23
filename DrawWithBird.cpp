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

// 鸟的属性
typedef struct BirdStruct {
	int x;						// 水平坐标
	int y;						// 垂直坐标
	double v;					// 垂直方向的速度，大于0向上
} Bird;

/*
	采用链表存储所有管道
*/
typedef struct TubeStruct {		// 单个管道的属性
	int xLeft;					// 左边缘坐标
	int width;					// 管道水平宽度
	int xRight;					// 右边缘坐标
	int gap[2];					// 管道间隙所在的y坐标，gap[0]为上边缘，gap[1]为下边缘
	int gapHeight;				// 管道间隙的高度
	double nothing;
} Tube;

typedef struct TubesNodeStruct {// 单个管道的链表节点
	Tube* tube;
	struct TubesNodeStruct* next;
} TubesNode;

typedef struct TubesStruct {	// 链表（所有管道）
	int num;					// 数量
	TubesNode* head;			// 头结点（不为NULL时是第一个元素）
} Tubes;

// 所有需要加载的图像
IMAGE base;
IMAGE back;
IMAGE TubeUp;
IMAGE TubeDown;
IMAGE BirdImages[3]; //0:down 1:mid 2:up

// 基本变量
int tubeGap = 75;						// 管道间隙高度
int tubeWidth = 50;						// 管道间隙宽度
int tubeMoveStep = 10 * SPEED_FACTOR;	// 每次移动时管道的每秒移动距离
int currentBase = 0;					// 现在的地面图像的坐标（仅用于画图）
int baseMoveStep = 10 * SPEED_FACTOR;	// 地面每秒移动距离
int createInterval = 2;					// 创建新管道的时间间隔
double refreshTime = 0.03;				// 刷新界面的时间（即重新绘制）
double gravity = 30;					// 重力加速度

// 所有管道的链表
Tubes tubes = {
	0, NULL
};

// 鸟实例
Bird bird = {
	BIRD_X, (GRAPH_HEIGHT - 112)/ 2, 0
};

// 部分初始化
void loadTestImages();		// 加载所有图片
void initRandom();			// 生成随机数，使用rand()获得一个随机数
void createConstantTube();	// 创建一个新的管道
void getRandomGap(Tube*);	// 为管道间隙坐标取随机值

/*
	移动游戏中的所有组件，其中interval是这段时间间隔
*/
void move(double interval);			// 移动所有组件
void moveGround(double interval);	// 移动地面
void moveAllTubes(double interval);	// 移动所有管道
TubesNode* deleteFirstTube();		// 删除第一个管道
void moveBird(double interval); // Improve: when up and down

/*
*	绘图函数
*/	
void draw();			// 绘制所有组件
void drawTubes(Tube*);	// 绘制指定管道
void drawBackground();	// 绘制背景
void drawBase();		// 绘制地面
void drawAllTubes();	// 绘制所有管道
void drawBird(int flap);

/*
	游戏时所需函数
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