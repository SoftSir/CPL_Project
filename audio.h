#include <easyx.h>
#include <conio.h>
// “˝”√ Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

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
	// ≤•∑≈“Ù¿÷
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
