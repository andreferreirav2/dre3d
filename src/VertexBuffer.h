#pragma once
#include <d3d11.h>

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	bool load(void* vertexList, size_t vertexSize, size_t vertexListSize, const void* shaderByteCode, size_t shaderByteCodeSize);
	UINT getVertexListSize();
private:
	size_t mVertexSize;
	size_t mVertexListSize;
	ID3D11Buffer* mBuffer;
	ID3D11InputLayout* mLayout;

	friend class DeviceContext;
};

