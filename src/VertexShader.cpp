#include "VertexShader.h"
#include "GraphicsEngine.h"
#include "Utils.h"

VertexShader::VertexShader() :
	mVertexShader(nullptr)
{
}

VertexShader::~VertexShader()
{
}

bool VertexShader::init(const void* shaderByteCode, size_t shaderByteCodeSize)
{
	DX::ThrowIfFailed(GraphicsEngine::get().mDevice->CreateVertexShader(shaderByteCode, shaderByteCodeSize, nullptr, mVertexShader.ReleaseAndGetAddressOf()));
	return true;
}
