#pragma once
#include <d3d11.h>
#include <wrl/client.h>

class GraphicsEngine;
class DeviceContext;

class VertexShader
{
public:
	VertexShader();
	~VertexShader();
private:
	bool init(const void* shaderByteCode, size_t shaderByteCodeSize);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;

	friend class GraphicsEngine;
	friend class DeviceContext;
};

