#include "AppWindow.h"
#include "Utils.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include <DirectXMath.h>

struct Vertex
{
	DirectX::XMFLOAT3 position;
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
		{ DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f)},
		{ DirectX::XMFLOAT3(-0.5f, 0.5f, 0.0f)},
		{ DirectX::XMFLOAT3(0.5f,-0.5f, 0.0f)},
		{ DirectX::XMFLOAT3(0.5f, 0.5f, 0.0f)},
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
	GraphicsEngine::get().getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, reinterpret_cast<const float*>(&Colors::Cyan));

	RECT rc = getClientWindowRect();
	GraphicsEngine::get().getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get().setShaders();
	GraphicsEngine::get().getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);

	GraphicsEngine::get().getImmediateDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexListSize(), 0);

	mSwapChain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}
