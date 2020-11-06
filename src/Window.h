#pragma once
#include <Windows.h>
#include "Timer.h"

class Window
{
public:
	Window();
	~Window();
	bool init();
	int run();
	bool isRunning();

	void virtual onCreate();
	void virtual onUpdate();
	void virtual onDraw();
	void virtual onDestroy();

	void calculateFrameStats();

	RECT getClientWindowRect();
	void setHwnd(HWND hwnd);

protected:
	HWND mhWnd = nullptr;
	bool mIsRunning = false;
	int mWidth;
	int mHeight;

	Timer mTimer;
};

