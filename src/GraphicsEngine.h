#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <memory>

class SwapChain;
class ConstantBuffer;
class VertexBuffer;
class DeviceContext;
class VertexShader;
class PixelShader;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	static GraphicsEngine& get();

	bool init();

	std::shared_ptr<SwapChain> createSwapChain() const;
	std::shared_ptr<DeviceContext> getImmediateDeviceContext() const;

	std::shared_ptr<ConstantBuffer> createConstantBuffer() const;
	std::shared_ptr<VertexBuffer> createVertexBuffer() const;
	std::shared_ptr<VertexShader> createVertexShader(const void* shaderByteCode, size_t shaderByteCodeSize) const;
	bool compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* shaderByteCodeSize);
	std::shared_ptr<PixelShader> createPixelShader(const void* shaderByteCode, size_t shaderByteCodeSize) const;
	bool compilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* shaderByteCodeSize);
	void releaseCompiledShader();

private:
	std::shared_ptr<DeviceContext> mImmediateDeviceContext;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mImmediateContext;

	Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
	D3D_FEATURE_LEVEL featureLevel;

	Microsoft::WRL::ComPtr<IDXGIDevice> mdxgiDevice;
	Microsoft::WRL::ComPtr<IDXGIAdapter> mdxgiAdapter;
	Microsoft::WRL::ComPtr<IDXGIFactory> mdxgiFactory;

	Microsoft::WRL::ComPtr<ID3DBlob> mBlob;

	friend class SwapChain;
	friend class ConstantBuffer;
	friend class VertexBuffer;
	friend class VertexShader;
	friend class PixelShader;
};

