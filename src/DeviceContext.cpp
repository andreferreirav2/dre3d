#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Utils.h"

DeviceContext::DeviceContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dDeviceContext) :
	mDeviceContext(d3dDeviceContext)
{
}

DeviceContext::~DeviceContext()
{
	if (mDeviceContext)
		mDeviceContext->ClearState();
}

void DeviceContext::clearRenderTargetColor(std::shared_ptr<SwapChain> swapChain, float r, float g, float b, float a)
{
	FLOAT clearColor[] = { r,g,b,a };
	clearRenderTargetColor(swapChain, clearColor);
}

void DeviceContext::clearRenderTargetColor(std::shared_ptr<SwapChain> swapChain, float const* color)
{
	mDeviceContext->ClearRenderTargetView(swapChain->mRenderTargetView.Get(), color);
	mDeviceContext->OMSetRenderTargets(1, swapChain->mRenderTargetView.GetAddressOf(), NULL);
}

void DeviceContext::setVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
{
	UINT stride = vertexBuffer->mVertexSize;
	UINT offset = 0;

	mDeviceContext->IASetVertexBuffers(0, 1, vertexBuffer->mBuffer.GetAddressOf(), &stride, &offset);
	mDeviceContext->IASetInputLayout(vertexBuffer->mLayout.Get());
}

void DeviceContext::setVertexShader(std::shared_ptr<VertexShader> vertexShader)
{
	mDeviceContext->VSSetShader(vertexShader->mVertexShader.Get(), nullptr, 0);
}

void DeviceContext::setPixelShader(std::shared_ptr<PixelShader> pixelShader)
{
	mDeviceContext->PSSetShader(pixelShader->mPixelShader.Get(), nullptr, 0);
}

void DeviceContext::drawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mDeviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::drawTriangleStrip(UINT vertexCount, UINT startVertexIndex)
{
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	mDeviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<FLOAT>(width);
	viewport.Height = static_cast<FLOAT>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	mDeviceContext->RSSetViewports(1, &viewport);
}