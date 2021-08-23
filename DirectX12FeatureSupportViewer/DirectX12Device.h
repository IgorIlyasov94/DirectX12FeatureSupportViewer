#pragma once

#include "Includes.h"

class DirectX12Device
{
public:
	DirectX12Device();
	~DirectX12Device();



private:
	void GetHardwareAdapter(IDXGIFactory4* _factory, IDXGIAdapter1** _adapter);
	
	void CreateDevice(IDXGIAdapter1* _adapter, ID3D12Device** _device);
	void CreateFactory(IDXGIFactory4** _factory);

	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIAdapter1> adapter;
	ComPtr<IDXGIFactory4> factory;
};
