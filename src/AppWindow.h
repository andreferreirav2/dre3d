#pragma once
#include <memory>
#include <DirectXMath.h>
#include "Window.h"

class SwapChain;
class ConstantBuffer;
class VertexBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;


class AppWindow : public Window
{
public:
	AppWindow() = default;

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDraw() override;

private:
	std::shared_ptr<SwapChain> mSwapChain;
	std::shared_ptr<ConstantBuffer> mConstantBuffer;
	std::shared_ptr<VertexBuffer> mVertexBuffer;
	std::shared_ptr<IndexBuffer> mIndexBuffer;
	std::shared_ptr<VertexShader> mVertexShader;
	std::shared_ptr<PixelShader> mPixelShader;

	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;

	UINT mOldTime;
	UINT mNewTime;
	float mDeltaTime;
	float mDeltaCycle;
};
