#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"


struct Vector3
{
	float x;
	float y;
	float z;
};

struct Vertex
{
	Vector3 position;
};

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get().init();
	mSwapChain = GraphicsEngine::get().createSwapChain();

	RECT rc = getClientWindowRect();
	mSwapChain->init(mhWnd, rc.right - rc.left, rc.bottom - rc.bottom);

	Vertex vertexList[] =
	{
		{ -0.5f, -0.5f, 0.0f},
		{ -0.5f, 0.4f, 0.0f},
		{ 0.5f,-0.5f, 0.0f},

		{ -0.5f, 0.5f, 0.0f},
		{ 0.5f, 0.5f, 0.0f},
		{ 0.5f, -0.4f, 0.0f}
	};

	mVertexBuffer = GraphicsEngine::get().createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertexList);

	GraphicsEngine::get().createShaders();

	void* shaderByteCode = nullptr;
	UINT shaderByteSize = 0;
	GraphicsEngine::get().getShaderBufferAndSize(&shaderByteCode, &shaderByteSize);

	mVertexBuffer->load(vertexList, sizeof(Vertex), size_list, shaderByteCode, shaderByteSize);

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get().getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, 154.0f / 255, 211.0f / 255, 188.0f / 255, 1);

	RECT rc = getClientWindowRect();
	GraphicsEngine::get().getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get().setShaders();
	GraphicsEngine::get().getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);

	GraphicsEngine::get().getImmediateDeviceContext()->drawTriangleList(mVertexBuffer->getVertexListSize(), 0);

	mSwapChain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}
