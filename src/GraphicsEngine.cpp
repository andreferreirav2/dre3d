#include "Utils.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

GraphicsEngine::GraphicsEngine() :
	mImmediateDeviceContext(nullptr),
	md3dDevice(nullptr),
	featureLevel(D3D_FEATURE_LEVEL_11_0),
	mdxgiDevice(nullptr),
	mdxgiAdapter(nullptr),
	mdxgiFactory(nullptr)
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
	ID3D11DeviceContext* d3dImmediateContext = NULL;
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
			&md3dDevice,			// resulting d3 device
			&featureLevel,			// chosen version of DX
			&d3dImmediateContext
		);

		if (SUCCEEDED(hr))
		{
			break;
		}
	}

	// what is the impact of throwing rather than returning false?
	//throw std::runtime_error("Failed to D3D11CreateDevice.");
	CHECK_HR(hr);

	mImmediateDeviceContext = std::make_shared<DeviceContext>(d3dImmediateContext);

	CHECK_HR(md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&mdxgiDevice));
	CHECK_HR(mdxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&mdxgiAdapter));
	CHECK_HR(mdxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&mdxgiFactory));

	return true;
}

bool GraphicsEngine::release()
{
	mImmediateDeviceContext->release();

	RELEASE_COM(mdxgiFactory);
	RELEASE_COM(mdxgiAdapter);
	RELEASE_COM(mdxgiDevice);

	RELEASE_COM(md3dDevice);
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
