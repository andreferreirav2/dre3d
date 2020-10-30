#pragma once
#include <stdexcept>

#define RELEASE_COM(x) { if(x){ x->Release(); x = nullptr; } }
#define CHECK_HR(hr) { if(FAILED(hr)){ throw std::runtime_error("Failed!!"); } }
