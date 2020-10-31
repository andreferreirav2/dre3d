#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "Utils.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* d3dDeviceContext) :
	mDeviceContext(d3dDeviceContext)
{
}

DeviceContext::~DeviceContext()
{
}

void DeviceContext::clearRenderTargetColor(std::shared_ptr<SwapChain> swapChain, float r, float g, float b, float a)
{
	FLOAT clearColor[] = { r,g,b,a };
	mDeviceContext->ClearRenderTargetView(swapChain->mRenderTargetView, clearColor);
	mDeviceContext->OMSetRenderTargets(1, &swapChain->mRenderTargetView, NULL);
}

void DeviceContext::setVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
{
	UINT stride = vertexBuffer->mVertexSize;
	UINT offset = 0;

	mDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->mBuffer, &stride, &offset);
	mDeviceContext->IASetInputLayout(vertexBuffer->mLayout);
}

void DeviceContext::drawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mDeviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<FLOAT>(width);
	viewport.Height = static_cast<FLOAT>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	mDeviceContext->RSSetViewports(1, &viewport);
}

bool DeviceContext::release()
{
	RELEASE_COM(mDeviceContext);
	return true;
}
