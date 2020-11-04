#pragma once
#include <memory>
#include <d3d11.h>
#include <wrl/client.h>

class SwapChain;
class ConstantBuffer;
class VertexBuffer;
class VertexShader;
class PixelShader;

class DeviceContext
{
public:
	DeviceContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dDeviceContext);
	~DeviceContext();

	void clearRenderTargetColor(std::shared_ptr<SwapChain> swapChain, float r, float g, float b, float a);
	void clearRenderTargetColor(std::shared_ptr<SwapChain> swapChain, float const* color);
	void setVSConstantBuffer(std::shared_ptr<ConstantBuffer> constantBuffer);
	void setPSConstantBuffer(std::shared_ptr<ConstantBuffer> constantBuffer);
	void setVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);
	void setVertexShader(std::shared_ptr<VertexShader> vertexShader);
	void setPixelShader(std::shared_ptr<PixelShader> pixelShader);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);
	void setViewportSize(UINT width, UINT height, UINT topLeftX = 0, UINT topLeftY = 0);
private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext;

	friend class ConstantBuffer;
};

