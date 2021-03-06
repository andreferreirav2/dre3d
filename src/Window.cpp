#include "Window.h"
#include <stdexcept>
#include <sstream>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE: // When window is 1st created
	{
		auto* const params = reinterpret_cast<LPCREATESTRUCT>(lparam);
		auto* const window = reinterpret_cast<Window* const>(params->lpCreateParams);

		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->setHwnd(hwnd);
		window->onCreate();
		break;
	}

	case WM_DESTROY: // When window is destroyed
	{
		auto* const window = reinterpret_cast<Window* const>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		window->onDestroy();
		PostQuitMessage(0);
		break;
	}


	default: // Any other message
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}

Window::Window() : mWidth(1024), mHeight(768), mIsRunning(false) {}

bool Window::init()
{
	// Create WNDCLASSEX obj
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = L"WindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!RegisterClassEx(&wc))
	{
		throw std::runtime_error("Failed to RegisterClassEx.");
	}

	// Setup draw area
	RECT rect = { 0,0,mWidth,mHeight };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

	const auto width = rect.right - rect.left;
	const auto height = rect.bottom - rect.top;

	//Create window
	mhWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		L"WindowClass",
		L"DirectX Application",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		nullptr,
		this);

	if (!mhWnd)
		throw std::runtime_error("Failed to CreateWindowEx.");

	//Show window
	ShowWindow(mhWnd, SW_SHOW);
	UpdateWindow(mhWnd);

	mIsRunning = true;

	return true;
}


int Window::run()
{
	MSG msg = { 0 };

	mTimer.reset();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			mTimer.tick();
			if (!mTimer.isPaused())
			{
				calculateFrameStats();
				onUpdate();
				onDraw();
			}
			else
			{
				Sleep(100);
			}
		}
	}

	return (int)msg.wParam;
}

bool Window::isRunning()
{
	return mIsRunning;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDraw()
{
}

Window::~Window()
{
	DestroyWindow(mhWnd);
}

void Window::onDestroy()
{
	mIsRunning = false;
}

void Window::calculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.totalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << L"    "
			<< L"FPS: " << fps << L"    "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(mhWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	GetClientRect(mhWnd, &rc);
	return rc;
}

void Window::setHwnd(HWND hwnd)
{
	mhWnd = hwnd;
}

