#include <stdexcept>
#include "GraphicsEngine.h"

#define SafeRelease(x) { if(x){ x->Release(); x = nullptr; } }

GraphicsEngine::GraphicsEngine() : md3dDevice(nullptr), md3dImmediateContext(nullptr), featureLevel(D3D_FEATURE_LEVEL_11_0)
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
		D3D_FEATURE_LEVEL_12_1
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
			&md3dDevice,			// resulting d3 device
			&featureLevel,			// chosen version of DX
			&md3dImmediateContext
		);

		if (SUCCEEDED(hr))
		{
			break;
		}
	}

	if (FAILED(hr))
	{
		// what is the impact of throwing rather than returning false?
		//throw std::runtime_error("Failed to D3D11CreateDevice.");
		return false;
	}

	return true;
}

bool GraphicsEngine::release()
{
	SafeRelease(md3dImmediateContext);
	SafeRelease(md3dDevice);
	return true;
}
