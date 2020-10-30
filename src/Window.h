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

protected:
	HWND mhWnd = nullptr;
	bool mIsRunning = false;
	int mWidth;
	int mHeight;
};

