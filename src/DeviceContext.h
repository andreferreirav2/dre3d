#pragma once
#include <memory>
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class VertexShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* d3dDeviceContext);
	~DeviceContext();

	void clearRenderTargetColor(std::shared_ptr<SwapChain> swapChain, float r, float g, float b, float a);
	void clearRenderTargetColor(std::shared_ptr<SwapChain> swapChain, float const* color);
	void setVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);
	void setVertexShader(std::shared_ptr<VertexShader> vertexShader);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);
	void setViewportSize(UINT width, UINT height);
private:
	ID3D11DeviceContext* mDeviceContext;
};

