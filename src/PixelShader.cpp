#include "PixelShader.h"
#include "GraphicsEngine.h"
#include "Utils.h"

PixelShader::PixelShader() :
	mPixelShader(nullptr)
{
}

PixelShader::~PixelShader()
{
}

bool PixelShader::init(const void* shaderByteCode, size_t shaderByteCodeSize)
{
	DX::ThrowIfFailed(GraphicsEngine::get().mDevice->CreatePixelShader(shaderByteCode, shaderByteCodeSize, nullptr, mPixelShader.ReleaseAndGetAddressOf()));
	return true;
}
