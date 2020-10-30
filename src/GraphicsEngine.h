#pragma once
#include <d3d11.h>
#include <memory>
#include "SwapChain.h"
#include "DeviceContext.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	static GraphicsEngine& get();

	bool init();
	bool release();

	std::shared_ptr<SwapChain> createSwapChain();
	std::shared_ptr<DeviceContext> getImmediateDeviceContext();

private:
	std::shared_ptr<DeviceContext> mImmediateDeviceContext;

	ID3D11Device* md3dDevice;
	D3D_FEATURE_LEVEL featureLevel;

	IDXGIDevice* mdxgiDevice;
	IDXGIAdapter* mdxgiAdapter;
	IDXGIFactory* mdxgiFactory;

	friend class SwapChain;
};

