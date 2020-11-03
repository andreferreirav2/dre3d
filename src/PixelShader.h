#pragma once
#include <d3d11.h>
#include <wrl/client.h>

class GraphicsEngine;
class DeviceContext;

class PixelShader
{
public:
	PixelShader();
	~PixelShader();
private:
	bool init(const void* shaderByteCode, size_t shaderByteCodeSize);

	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;

	friend class GraphicsEngine;
	friend class DeviceContext;
};

