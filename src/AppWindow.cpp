#include "AppWindow.h"
#include "Utils.h"
#include "MathHelper.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <DirectXMath.h>
#include <windows.h>
#include <iostream>

struct Vertex						// 48 bytes
{
	DirectX::XMFLOAT3 position;		// 12 bytes
	DirectX::XMFLOAT3 position1;	// 12 bytes
	DirectX::XMFLOAT3 color;		// 12 bytes
	DirectX::XMFLOAT3 color1;		// 12 bytes
};

// Always handled in chunks of 16 bytes
__declspec(align(16))
struct Constant
{
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 proj;
	unsigned int time;
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
		{ DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f),	DirectX::XMFLOAT3(-0.5f, 0.5f, 0.0f),	DirectX::XMFLOAT3(1, 0, 0),	DirectX::XMFLOAT3(0, 1, 1)},
		{ DirectX::XMFLOAT3(-0.5f, 0.5f, 0.0f),		DirectX::XMFLOAT3(0.5f, 0.5f, 0.0f),	DirectX::XMFLOAT3(0, 1, 0),	DirectX::XMFLOAT3(1, 0, 1)},
		{ DirectX::XMFLOAT3(0.5f,-0.5f, 0.0f),		DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f),	DirectX::XMFLOAT3(0, 0, 1),	DirectX::XMFLOAT3(1, 1, 0)},
		{ DirectX::XMFLOAT3(0.5f, 0.5f, 0.0f),		DirectX::XMFLOAT3(0.5f,-0.5f, 0.0f),	DirectX::XMFLOAT3(1, 1, 1),	DirectX::XMFLOAT3(0, 0, 0)},
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

	Constant constants = { };
	mConstantBuffer = GraphicsEngine::get().createConstantBuffer();
	mConstantBuffer->load(&constants, sizeof(Constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get().getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, reinterpret_cast<const float*>(&Colors::LightSteelBlue));

	RECT rc = getClientWindowRect();
	// Full screen render
	GraphicsEngine::get().getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	// Mini map render with 1/5th of the size, bottom right corner
	//GraphicsEngine::get().getImmediateDeviceContext()->setViewportSize((rc.right - rc.left) / 5, (rc.bottom - rc.top) / 5, (rc.right - rc.left) * 4 / 5, (rc.bottom - rc.top) * 4 / 5);

	mDeltaCycle += 0.1f * mDeltaTime;
	mDeltaCycle = fmod(mDeltaCycle, 1.0f);
	DirectX::XMMATRIX worldRotate = DirectX::XMMatrixRotationZ(sin(mDeltaCycle * 3.1415) * 50);
	DirectX::XMMATRIX worldScale = DirectX::XMMatrixScaling(sin(mDeltaCycle * 20), sin(mDeltaCycle * 20), 1);
	DirectX::XMMATRIX worldTranslate = MathHelper::Lerp(DirectX::XMMatrixTranslation(-2, -2, 0), DirectX::XMMatrixTranslation(2, 2, 0), mDeltaCycle);

	Constant constants = {};
	DirectX::XMStoreFloat4x4(&constants.world, worldRotate * worldScale * worldTranslate);
	DirectX::XMStoreFloat4x4(&constants.view, DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&constants.proj, DirectX::XMMatrixOrthographicLH((rc.right - rc.left) / 400.0f, (rc.bottom - rc.top) / 400.0f, -4.0f, 4.0f));
	constants.time = GetTickCount64();

	mConstantBuffer->update(GraphicsEngine::get().getImmediateDeviceContext(), &constants);
	GraphicsEngine::get().getImmediateDeviceContext()->setVSConstantBuffer(mConstantBuffer);
	GraphicsEngine::get().getImmediateDeviceContext()->setPSConstantBuffer(mConstantBuffer);

	GraphicsEngine::get().getImmediateDeviceContext()->setVertexShader(mVertexShader);
	GraphicsEngine::get().getImmediateDeviceContext()->setPixelShader(mPixelShader);
	GraphicsEngine::get().getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);

	GraphicsEngine::get().getImmediateDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexListSize(), 0);

	mSwapChain->present(true);


	mOldTime = mNewTime;
	mNewTime = GetTickCount64();
	mDeltaTime = mOldTime ? max((mNewTime - mOldTime) / 1000.0f, 0.0f) : 0.0f;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}
