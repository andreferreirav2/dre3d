#pragma once
#include <d3d11.h>
#include <memory>

class SwapChain;
class VertexBuffer;
class DeviceContext;
class VertexShader;

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
	std::shared_ptr<VertexShader> createVertexShader(const void* shaderByteCode, size_t shaderByteCodeSize) const;
	bool compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* shaderByteCodeSize);
	void releaseCompiledShader();

	bool createShaders();
	bool setShaders();

private:
	std::shared_ptr<DeviceContext> mImmediateDeviceContext;
	ID3D11DeviceContext* mImmediateContext;

	ID3D11Device* mDevice;
	D3D_FEATURE_LEVEL featureLevel;

	IDXGIDevice* mdxgiDevice;
	IDXGIAdapter* mdxgiAdapter;
	IDXGIFactory* mdxgiFactory;

	ID3DBlob* mBlob;
	ID3DBlob* mVsBlob;
	ID3DBlob* mPsBlob;
	ID3D11VertexShader* mVs;
	ID3D11PixelShader* mPs;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class VertexShader;
};

