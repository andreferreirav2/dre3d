#pragma once
#include <memory>
#include <d3d11.h>
#include "SwapChain.h"


class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* d3dDeviceContext);
	~DeviceContext();

	bool clearRenderTargetColor(std::shared_ptr<SwapChain> swapChain, float r, float g, float b, float a);
	bool release();
private:
	ID3D11DeviceContext* md3dDeviceContext;
};

