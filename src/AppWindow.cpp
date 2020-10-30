#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

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
	GraphicsEngine::get().getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, 0, 0, 1, 1);
	mSwapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	mSwapChain->release();
	GraphicsEngine::get().release();
}
