#pragma once
#include <memory>
#include "Window.h"

class SwapChain;
class ConstantBuffer;
class VertexBuffer;
class VertexShader;
class PixelShader;


class AppWindow : public Window
{
public:
	AppWindow() = default;

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	std::shared_ptr<SwapChain> mSwapChain;
	std::shared_ptr<ConstantBuffer> mConstantBuffer;
	std::shared_ptr<VertexBuffer> mVertexBuffer;
	std::shared_ptr<VertexShader> mVertexShader;
	std::shared_ptr<PixelShader> mPixelShader;
};
