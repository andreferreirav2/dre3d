#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "Utils.h"

IndexBuffer::IndexBuffer() :
	mIndexListSize(0),
	mBuffer(nullptr)
{
}

IndexBuffer::~IndexBuffer()
{
}

bool IndexBuffer::load(void* indexList, size_t indexListSize)
{
	mBuffer.Reset();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(int) * indexListSize;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = indexList;
	mIndexListSize = indexListSize;

	DX::ThrowIfFailed(GraphicsEngine::get().mDevice->CreateBuffer(&bufferDesc, &initData, mBuffer.ReleaseAndGetAddressOf()));
	return true;
}

UINT IndexBuffer::getIndexListSize()
{
	return mIndexListSize;
}
