#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_6.h>

#include <wrl/client.h>

#include <iostream>
#include <string>
#include <sstream>
#include <exception>

using namespace Microsoft::WRL;

inline void ThrowIfFailed(HRESULT hResult, const char* errorMessage)
{
    if (FAILED(hResult))
    {
        std::stringstream fullMessage;
        fullMessage << errorMessage << "\nHRESULT: " << "0x" << std::hex << hResult;

        throw std::runtime_error(fullMessage.str());
    }
}
