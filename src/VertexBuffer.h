#pragma once
#include <d3d11.h>

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	bool load(void* vertexList, UINT vertexSize, UINT vertexListSize, void* shaderByteCode, UINT shaderByteSize);
	UINT getVertexListSize();
private:
	UINT mVertexSize;
	UINT mVertexListSize;
	ID3D11Buffer* mBuffer;
	ID3D11InputLayout* mLayout;

	friend class DeviceContext;
};

