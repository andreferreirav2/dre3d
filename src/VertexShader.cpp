#include "VertexShader.h"
#include "GraphicsEngine.h"
#include "Utils.h"

VertexShader::VertexShader() :
	mVertexShader(nullptr)
{
}

VertexShader::~VertexShader()
{
	RELEASE_COM(mVertexShader);
}

bool VertexShader::init(const void* shaderByteCode, size_t shaderByteCodeSize)
{
	DX::ThrowIfFailed(GraphicsEngine::get().mDevice->CreateVertexShader(shaderByteCode, shaderByteCodeSize, nullptr, &mVertexShader));
	return true;
}
