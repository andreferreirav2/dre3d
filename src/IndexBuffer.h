#pragma once
#include <d3d11.h>
#include <wrl/client.h>

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	bool load(void* indexList, size_t indexListSize);
	UINT getIndexListSize();
private:
	size_t mIndexListSize;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;

	friend class DeviceContext;
};

