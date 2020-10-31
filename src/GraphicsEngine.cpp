#include "Utils.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

#include <d3dcompiler.h>

GraphicsEngine::GraphicsEngine() :
	mImmediateDeviceContext(nullptr),
	mImmediateContext(nullptr),
	mDevice(nullptr),
	featureLevel(D3D_FEATURE_LEVEL_11_0),
	mdxgiDevice(nullptr),
	mdxgiAdapter(nullptr),
	mdxgiFactory(nullptr),
	mVsBlob(nullptr),
	mPsBlob(nullptr),
	mVs(nullptr),
	mPs(nullptr)
{
}

GraphicsEngine::~GraphicsEngine()
{
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
			NULL,					// default adapter
			driverType,
			NULL,					// no software device
			createDeviceFlags,
			featureLevels,			// versions of DX to try, first matching will be chosen
			numFeatureLevels,		// num of versions of DX in above array
			D3D11_SDK_VERSION,
			// output variables
			&mDevice,			// resulting d3 device
			&featureLevel,			// chosen version of DX
			&mImmediateContext
		);

		if (SUCCEEDED(hr))
		{
			break;
		}
	}

	// what is the impact of throwing rather than returning false?
	//throw std::runtime_error("Failed to D3D11CreateDevice.");
	CHECK_HR(hr);

	mImmediateDeviceContext = std::make_shared<DeviceContext>(mImmediateContext);

	CHECK_HR(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&mdxgiDevice));
	CHECK_HR(mdxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&mdxgiAdapter));
	CHECK_HR(mdxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&mdxgiFactory));

	return true;
}

bool GraphicsEngine::release()
{
	RELEASE_COM(mVs);
	RELEASE_COM(mPs);
	RELEASE_COM(mVsBlob);
	RELEASE_COM(mPsBlob);

	RELEASE_COM(mdxgiFactory);
	RELEASE_COM(mdxgiAdapter);
	RELEASE_COM(mdxgiDevice);

	mImmediateDeviceContext->release();

	RELEASE_COM(mDevice);
	return true;
}

std::shared_ptr<SwapChain> GraphicsEngine::createSwapChain()
{
	return std::make_shared<SwapChain>();
}

std::shared_ptr<DeviceContext> GraphicsEngine::getImmediateDeviceContext()
{
	return mImmediateDeviceContext;
}

std::shared_ptr<VertexBuffer> GraphicsEngine::createVertexBuffer()
{
	return std::make_shared<VertexBuffer>();
}

bool GraphicsEngine::createShaders()
{
	ID3DBlob* errblob = nullptr;
	CHECK_HR(D3DCompileFromFile(L"src/shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &mVsBlob, &errblob));
	CHECK_HR(D3DCompileFromFile(L"src/shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &mPsBlob, &errblob));
	CHECK_HR(mDevice->CreateVertexShader(mVsBlob->GetBufferPointer(), mVsBlob->GetBufferSize(), nullptr, &mVs));
	CHECK_HR(mDevice->CreatePixelShader(mPsBlob->GetBufferPointer(), mPsBlob->GetBufferSize(), nullptr, &mPs));
	return true;
}

bool GraphicsEngine::setShaders()
{
	mImmediateContext->VSSetShader(mVs, nullptr, 0);
	mImmediateContext->PSSetShader(mPs, nullptr, 0);
	return true;
}

void GraphicsEngine::getShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = mVsBlob->GetBufferPointer();
	*size = (UINT)mVsBlob->GetBufferSize();
}