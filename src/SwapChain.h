#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool init(HWND hwnd, UINT width, UINT height);
	bool present(bool vsync);
	bool release();
private:
	IDXGISwapChain* mSwapChain;
	ID3D11RenderTargetView* mRenderTargetView;

	friend class DeviceContext;
};

