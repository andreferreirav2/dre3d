#include "DeviceContext.h"
#include "Utils.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* d3dDeviceContext) :
	md3dDeviceContext(d3dDeviceContext)
{
}

DeviceContext::~DeviceContext()
{
}

bool DeviceContext::clearRenderTargetColor(std::shared_ptr<SwapChain> swapChain, float r, float g, float b, float a)
{
	FLOAT clearColor[] = { r,g,b,a };
	md3dDeviceContext->ClearRenderTargetView(swapChain->mRenderTargetView, clearColor);

	return true;
}

bool DeviceContext::release()
{
	RELEASE_COM(md3dDeviceContext);
	return true;
}
