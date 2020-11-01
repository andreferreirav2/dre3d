#pragma once
#include <memory>
#include "Window.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"


class AppWindow : public Window
{
public:
	AppWindow() = default;

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	std::shared_ptr<SwapChain> mSwapChain;
	std::shared_ptr<VertexBuffer> mVertexBuffer;
	std::shared_ptr<VertexShader> mVertexShader;
};
