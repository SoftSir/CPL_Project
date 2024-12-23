/*
#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

double gravity;
double updateTime;

typedef struct BirdStruct {
	double yAxis;
	double v;
} Bird;

typedef struct TubeStruct {
	double xLeft;
	double xRight;
	double width;
	double gap[2];
	double gapHeight;
} Tube;

// state;
void MenuState();
void GameState();
void OverState();

// Function for Bird
void wing(Bird*);


// Function for Tube

// Global Function
void update();
void trigger();
int isHit();
void createTube();
void nextState();

// Graphics
void drawRunningInit();
void drawMenuState();
void drawOverState();
void drawUpdate();
void drawTubes();
void drawBird();
void drawHit();
void drawDie();

// Audio
void loadAudio();
void dieAudio();
void hitAudio();
void getPointAudio();
void wingAudio();
void bgmAudio();
void stopAllAudio();
void closeAllAudio();



// Load all the audio needed
void loadAudio() {
	mciSendString(_T("open audio\\bgm.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open audio\\die.wav alias die"), NULL, 0, NULL);
	mciSendString(_T("open audio\\hit.wav alias hit"), NULL, 0, NULL);
	mciSendString(_T("open audio\\point.wav alias point"), NULL, 0, NULL);
	mciSendString(_T("open audio\\wing.wav alias wing"), NULL, 0, NULL);
	mciSendString(_T("open audio\\swoosh.wav alias swoosh"), NULL, 0, NULL);
}

void bgmAudio() {
	// 播放音乐
	mciSendString(_T("play bgm from 0 repeat"), NULL, 0, NULL);
}

void dieAudio() {
	mciSendString(_T("play die from 0"), NULL, 0, NULL);
}

void hitAudio() {
	mciSendString(_T("play hit from 0"), NULL, 0, NULL);
}

void wingAudio() {
	mciSendString(_T("play wing from 0"), NULL, 0, NULL);
}

void swooshAudio() {
	mciSendString(_T("play swoosh from 0"), NULL, 0, NULL);
}

void getPointAudio() {
	mciSendString(_T("play point from 0"), NULL, 0, NULL);
}

void stopAllAudio() {
	mciSendString(_T("stop all"), NULL, 0, NULL);
}

void closeAllAudio() {
	mciSendString(_T("close all"), NULL, 0, NULL);
}

*/