#include "Utils.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include <d3dcompiler.h>

GraphicsEngine::GraphicsEngine() :
	mImmediateDeviceContext(nullptr),
	mImmediateContext(nullptr),
	mDevice(nullptr),
	featureLevel(D3D_FEATURE_LEVEL_11_0),
	mdxgiDevice(nullptr),
	mdxgiAdapter(nullptr),
	mdxgiFactory(nullptr),
	mBlob(nullptr)
{
}

GraphicsEngine::~GraphicsEngine()
{
	Microsoft::WRL::ComPtr<ID3D11Debug> pDebug;
	DX::ThrowIfFailed(mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(pDebug.ReleaseAndGetAddressOf())));
	if (pDebug != nullptr)
	{
		pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	}
}

GraphicsEngine& GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return engine;
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,	// Fastest and on the GPU
		D3D_DRIVER_TYPE_WARP,		// High-perf instructions on the CPU
		D3D_DRIVER_TYPE_REFERENCE,	// Low-perf instructions on the CPU
	};

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0
	};
	int numFeatureLevels = ARRAYSIZE(featureLevels);

	HRESULT hr = 0;
	// Iterate over all driver types to find the best/first that works
	for (D3D_DRIVER_TYPE const& driverType : driverTypes)
	{
		hr = D3D11CreateDevice(
			// input variables
			NULL, // default adapter
			driverType,
			NULL, // no software device
			createDeviceFlags,
			featureLevels, // versions of DX to try, first matching will be chosen
			numFeatureLevels, // num of versions of DX in above array
			D3D11_SDK_VERSION,
			// output variables
			mDevice.ReleaseAndGetAddressOf(), // resulting d3 device
			&featureLevel, // chosen version of DX
			mImmediateContext.ReleaseAndGetAddressOf()
		);

		if (SUCCEEDED(hr))
		{
			break;
		}
	}

	// what is the impact of throwing rather than returning false?
	//throw std::runtime_error("Failed to D3D11CreateDevice.");
	DX::ThrowIfFailed(hr);

	mImmediateDeviceContext = std::make_shared<DeviceContext>(mImmediateContext);

	DX::ThrowIfFailed(mDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(mdxgiDevice.GetAddressOf())));
	DX::ThrowIfFailed(mdxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(mdxgiAdapter.GetAddressOf())));
	DX::ThrowIfFailed(mdxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(mdxgiFactory.GetAddressOf())));

	return true;
}

std::shared_ptr<SwapChain> GraphicsEngine::createSwapChain() const
{
	return std::make_shared<SwapChain>();
}

std::shared_ptr<DeviceContext> GraphicsEngine::getImmediateDeviceContext() const
{
	return mImmediateDeviceContext;
}

std::shared_ptr<ConstantBuffer> GraphicsEngine::createConstantBuffer() const
{
	return std::make_shared<ConstantBuffer>();
}

std::shared_ptr<VertexBuffer> GraphicsEngine::createVertexBuffer() const
{
	return std::make_shared<VertexBuffer>();
}

std::shared_ptr<IndexBuffer> GraphicsEngine::createIndexBuffer() const
{
	return std::make_shared<IndexBuffer>();
}

std::shared_ptr<VertexShader> GraphicsEngine::createVertexShader(const void* shaderByteCode, size_t shaderByteCodeSize) const
{
	std::shared_ptr<VertexShader> vertexShader = std::make_shared<VertexShader>();
	vertexShader->init(shaderByteCode, shaderByteCodeSize);
	return vertexShader;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* shaderByteCodeSize)
{
	Microsoft::WRL::ComPtr<ID3DBlob> errblob = nullptr;
	DX::ThrowIfFailed(D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "vs_5_0", NULL, NULL, mBlob.GetAddressOf(), errblob.ReleaseAndGetAddressOf()));

	*shaderByteCode = mBlob->GetBufferPointer();
	*shaderByteCodeSize = mBlob->GetBufferSize();

	return true;
}

std::shared_ptr<PixelShader> GraphicsEngine::createPixelShader(const void* shaderByteCode, size_t shaderByteCodeSize) const
{
	std::shared_ptr<PixelShader> pixelShader = std::make_shared<PixelShader>();
	pixelShader->init(shaderByteCode, shaderByteCodeSize);
	return pixelShader;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* shaderByteCodeSize)
{
	Microsoft::WRL::ComPtr<ID3DBlob> errblob = nullptr;
	DX::ThrowIfFailed(D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "ps_5_0", NULL, NULL, mBlob.GetAddressOf(), errblob.ReleaseAndGetAddressOf()));

	*shaderByteCode = mBlob->GetBufferPointer();
	*shaderByteCodeSize = mBlob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader()
{
	mBlob.Reset();
}
