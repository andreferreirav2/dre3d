#pragma once
#include <d3d11.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	static GraphicsEngine& get();

	bool init();
	bool release();

private:
	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dImmediateContext;
	D3D_FEATURE_LEVEL featureLevel;
};

