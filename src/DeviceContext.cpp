#include "DeviceContext.h"
#include "SwapChain.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
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

void DeviceContext::setVSConstantBuffer(std::shared_ptr<ConstantBuffer> constantBuffer)
{
	mDeviceContext->VSSetConstantBuffers(0, 1, constantBuffer->mBuffer.GetAddressOf());
}

void DeviceContext::setPSConstantBuffer(std::shared_ptr<ConstantBuffer> constantBuffer)
{
	mDeviceContext->PSSetConstantBuffers(0, 1, constantBuffer->mBuffer.GetAddressOf());
}

void DeviceContext::setVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
{
	UINT stride = vertexBuffer->mVertexSize;
	UINT offset = 0;

	mDeviceContext->IASetVertexBuffers(0, 1, vertexBuffer->mBuffer.GetAddressOf(), &stride, &offset);
	mDeviceContext->IASetInputLayout(vertexBuffer->mLayout.Get());
}

void DeviceContext::setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
{
	mDeviceContext->IASetIndexBuffer(indexBuffer->mBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::setVertexShader(std::shared_ptr<VertexShader> vertexShader)
{
	mDeviceContext->VSSetShader(vertexShader->mVertexShader.Get(), nullptr, 0);
}

void DeviceContext::setPixelShader(std::shared_ptr<PixelShader> pixelShader)
{
	mDeviceContext->PSSetShader(pixelShader->mPixelShader.Get(), nullptr, 0);
}

void DeviceContext::drawTriangleList(UINT vertexCount, UINT startVertexLocation)
{
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mDeviceContext->Draw(vertexCount, startVertexLocation);
}

void DeviceContext::drawIndexedTriangleList(UINT indexCount, UINT startIndexLocation, UINT baseVertexLocation)
{
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mDeviceContext->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
}

void DeviceContext::drawTriangleStrip(UINT vertexCount, UINT startVertexLocation)
{
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	mDeviceContext->Draw(vertexCount, startVertexLocation);
}

void DeviceContext::setViewportSize(UINT width, UINT height, UINT topLeftX, UINT topLeftY)
{
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = static_cast<FLOAT>(topLeftX);
	viewport.TopLeftY = static_cast<FLOAT>(topLeftY);
	viewport.Width = static_cast<FLOAT>(width);
	viewport.Height = static_cast<FLOAT>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	mDeviceContext->RSSetViewports(1, &viewport);
}