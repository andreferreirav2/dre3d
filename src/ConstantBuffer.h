#pragma once
#include <memory>
#include <d3d11.h>
#include <wrl/client.h>

class DeviceContext;

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	bool load(void* buffer, size_t size);
	void update(std::shared_ptr<DeviceContext> deviceContext, void* buffer);
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;

	friend class DeviceContext;
};

