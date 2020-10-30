#include "AppWindow.h"
#include "GraphicsEngine.h"

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get().init();
	mSwapChain = GraphicsEngine::get().createSwapChain();

	RECT rc = getClientWindowRect();
	mSwapChain->init(mhWnd, rc.right - rc.left, rc.bottom - rc.bottom);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	mSwapChain->release();
	GraphicsEngine::get().release();
}
