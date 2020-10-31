#pragma once
#include <d3d11.h>
#include <memory>

class SwapChain;
class VertexBuffer;
class DeviceContext;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	static GraphicsEngine& get();

	bool init();

	std::shared_ptr<SwapChain> createSwapChain() const;
	std::shared_ptr<DeviceContext> getImmediateDeviceContext() const;
	std::shared_ptr<VertexBuffer> createVertexBuffer() const;

	bool createShaders();
	bool setShaders();
	void getShaderBufferAndSize(void** bytecode, UINT* size) const;

private:
	std::shared_ptr<DeviceContext> mImmediateDeviceContext;
	ID3D11DeviceContext* mImmediateContext;

	ID3D11Device* mDevice;
	D3D_FEATURE_LEVEL featureLevel;

	IDXGIDevice* mdxgiDevice;
	IDXGIAdapter* mdxgiAdapter;
	IDXGIFactory* mdxgiFactory;

	ID3DBlob* mVsBlob;
	ID3DBlob* mPsBlob;
	ID3D11VertexShader* mVs;
	ID3D11PixelShader* mPs;

	friend class SwapChain;
	friend class VertexBuffer;
};

