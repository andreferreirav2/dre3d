#include "ConstantBuffer.h"
#include "Utils.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

ConstantBuffer::ConstantBuffer() :
	mBuffer(nullptr)
{
}

ConstantBuffer::~ConstantBuffer()
{
}

bool ConstantBuffer::load(void* buffer, size_t size)
{
	mBuffer.Reset();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = buffer;

	DX::ThrowIfFailed(GraphicsEngine::get().mDevice->CreateBuffer(&bufferDesc, &initData, mBuffer.ReleaseAndGetAddressOf()));
	return true;
}

void ConstantBuffer::update(std::shared_ptr<DeviceContext> deviceContext, void* buffer)
{
	deviceContext->mDeviceContext->UpdateSubresource(mBuffer.Get(), NULL, NULL, buffer, NULL, NULL);
}
