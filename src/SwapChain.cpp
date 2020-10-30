#include "SwapChain.h"
#include "Utils.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain() :
	midxgiSwapChain(nullptr)
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

	ID3D11Device* d3dDevice = GraphicsEngine::get().md3dDevice;
	CHECK_HR(GraphicsEngine::get().mdxgiFactory->CreateSwapChain(d3dDevice, &swapChainDesc, &midxgiSwapChain));
	return true;
}

bool SwapChain::release()
{
	RELEASE_COM(midxgiSwapChain);
	return true;
}
