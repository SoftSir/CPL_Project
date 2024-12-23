#include <easyx.h>
#include <conio.h>
// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

void audio()
{
	// 打开音乐
//mciSendString(_T("open 别看我只是一只羊.mp3 alias mymusic"), NULL, 0, NULL);
	mciSendString(_T("open audio\\die.wav alias mymusic"), NULL, 0, NULL);
	// 播放音乐
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
	_getch();
}