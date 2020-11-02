#include "AppWindow.h"
#include "Utils.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <DirectXMath.h>

struct Vertex					// 24 bytes
{
	DirectX::XMFLOAT3 position; // 12 bytes
	DirectX::XMFLOAT3 color;	// 12 bytes
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
		{ DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f),	DirectX::XMFLOAT3(1, 0, 0)},
		{ DirectX::XMFLOAT3(-0.5f, 0.5f, 0.0f),		DirectX::XMFLOAT3(0, 1, 0)},
		{ DirectX::XMFLOAT3(0.5f,-0.5f, 0.0f),		DirectX::XMFLOAT3(0, 0, 1)},
		{ DirectX::XMFLOAT3(0.5f, 0.5f, 0.0f),		DirectX::XMFLOAT3(1, 1, 1)},
	};

	mVertexBuffer = GraphicsEngine::get().createVertexBuffer();
	size_t vertexListSize = ARRAYSIZE(vertexList);

	void* shaderByteCode = nullptr;
	size_t shaderByteCodeSize = 0;

	GraphicsEngine::get().compileVertexShader(L"shaders/VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderByteCodeSize);
	mVertexShader = GraphicsEngine::get().createVertexShader(shaderByteCode, shaderByteCodeSize);
	mVertexBuffer->load(vertexList, sizeof(Vertex), vertexListSize, shaderByteCode, shaderByteCodeSize);
	GraphicsEngine::get().releaseCompiledShader();

	GraphicsEngine::get().compilePixelShader(L"shaders/PixelShader.hlsl", "psmain", &shaderByteCode, &shaderByteCodeSize);
	mPixelShader = GraphicsEngine::get().createPixelShader(shaderByteCode, shaderByteCodeSize);
	GraphicsEngine::get().releaseCompiledShader();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get().getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, reinterpret_cast<const float*>(&Colors::Cyan));

	RECT rc = getClientWindowRect();
	GraphicsEngine::get().getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get().getImmediateDeviceContext()->setVertexShader(mVertexShader);
	GraphicsEngine::get().getImmediateDeviceContext()->setPixelShader(mPixelShader);
	GraphicsEngine::get().getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);

	GraphicsEngine::get().getImmediateDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexListSize(), 0);

	mSwapChain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}
