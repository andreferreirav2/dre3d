#include "SwapChain.h"
#include "Utils.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain() :
	mSwapChain(nullptr),
	mRenderTargetView(nullptr)
{
}

SwapChain::~SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapChainDesc.SampleDesc.Count = 1;		// Change to use MSAA
	swapChainDesc.SampleDesc.Quality = 0;	// Change to use MSAA

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	DX::ThrowIfFailed(GraphicsEngine::get().mdxgiFactory->CreateSwapChain(GraphicsEngine::get().mDevice.Get(), &swapChainDesc, mSwapChain.ReleaseAndGetAddressOf()));

	Microsoft::WRL::ComPtr<ID3D11Texture2D> buffer = NULL;
	DX::ThrowIfFailed(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(buffer.ReleaseAndGetAddressOf())));

	DX::ThrowIfFailed(GraphicsEngine::get().mDevice->CreateRenderTargetView(buffer.Get(), NULL, mRenderTargetView.ReleaseAndGetAddressOf()));
	buffer.Reset();

	return true;
}

bool SwapChain::present(bool vsync)
{
	mSwapChain->Present(vsync, NULL);
	return true;
}