#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	~Window();
	bool init();
	void broadcast();
	bool isRunning();

	void virtual onCreate();
	void virtual onUpdate();
	void virtual onDestroy();

	RECT getClientWindowRect();
	void setHwnd(HWND hwnd);

protected:
	HWND mhWnd = nullptr;
	bool mIsRunning = false;
	int mWidth;
	int mHeight;
};

