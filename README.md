# dre3d
C++ &amp; Dx11 Game Engine

Heavily inspired by examples and structure of [Introduction to 3D Game Programming with DirectX 11.0 by Frank Luna](http://www.merclearning.com/titles/Introduction_to_3D_Game_Programming_with_DirectX11.html) and [C++ 3D Game Tutorial Series by PardCode](https://www.pardcode.com/cpp-3d-game-tutorial-series).

## Notes
* DX11 resources are created through the usage of [Microsoft::WRL::ComPtr](https://github.com/Microsoft/DirectXTK/wiki/ComPtr) to allow proper ref counting and avoid manual release
* Pointers to internal objects make use of smart pointers, mostly std::shared_ptr<>
