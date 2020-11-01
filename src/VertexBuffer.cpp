#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "Utils.h"

VertexBuffer::VertexBuffer() :
	mVertexSize(0),
	mVertexListSize(0),
	mBuffer(nullptr),
	mLayout(nullptr)
{
}

VertexBuffer::~VertexBuffer()
{
	RELEASE_COM(mBuffer);
	RELEASE_COM(mLayout);
}

bool VertexBuffer::load(void* vertexList, size_t vertexSize, size_t vertexListSize, const void* shaderByteCode, size_t shaderByteCodeSize)
{
	RELEASE_COM(mBuffer);
	RELEASE_COM(mLayout);

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = vertexSize * vertexListSize;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertexList;

	mVertexSize = vertexSize;
	mVertexListSize = vertexListSize;

	DX::ThrowIfFailed(GraphicsEngine::get().mDevice->CreateBuffer(&bufferDesc, &initData, &mBuffer));

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{
			"POSITION",						// LPCSTR SemanticName
			0,								// UINT SemanticIndex
			DXGI_FORMAT_R32G32B32_FLOAT,	// DXGI_FORMAT Format
			0,								// UINT InputSlot
			0,								// UINT AlignedByteOffset
			D3D11_INPUT_PER_VERTEX_DATA,	// D3D11_INPUT_CLASSIFICATION InputSlotClass
			0								// UINT InstanceDataStepRate
		}
	};
	size_t layoutSize = ARRAYSIZE(layout);
	DX::ThrowIfFailed(GraphicsEngine::get().mDevice->CreateInputLayout(layout, layoutSize, shaderByteCode, shaderByteCodeSize, &mLayout));

	return true;
}

UINT VertexBuffer::getVertexListSize()
{
	return mVertexListSize;
}
