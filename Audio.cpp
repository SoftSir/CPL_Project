#include <easyx.h>
#include <conio.h>
// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

void audio()
{
	// ������
//mciSendString(_T("open ����ֻ��һֻ��.mp3 alias mymusic"), NULL, 0, NULL);
	mciSendString(_T("open audio\\die.wav alias mymusic"), NULL, 0, NULL);
	// ��������
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
	_getch();
}