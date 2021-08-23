#include "DirectX12Device.h"

DirectX12Device::DirectX12Device()
{
	CreateFactory(&factory);

	GetHardwareAdapter(factory.Get(), &adapter);

	CreateDevice(adapter.Get(), &device);
}

DirectX12Device::~DirectX12Device()
{

}

void DirectX12Device::GetHardwareAdapter(IDXGIFactory4* _factory, IDXGIAdapter1** _adapter)
{
	*_adapter = nullptr;

	ComPtr<IDXGIAdapter1> adapter1;
	ComPtr<IDXGIFactory6> factory6;

	if (SUCCEEDED(_factory->QueryInterface(IID_PPV_ARGS(&factory6))))
	{
		for (auto adapterId = 0;
			factory6->EnumAdapterByGpuPreference(adapterId, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter1)) != DXGI_ERROR_NOT_FOUND;
			adapterId++)
		{
			if (SUCCEEDED(D3D12CreateDevice(adapter1.Get(), D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)))
				break;
		}
	}
	else
	{
		for (auto adapterId = 0; _factory->EnumAdapters1(adapterId, &adapter1) != DXGI_ERROR_NOT_FOUND; adapterId++)
		{
			if (SUCCEEDED(D3D12CreateDevice(adapter1.Get(), D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)))
				break;
		}
	}

	*_adapter = adapter1.Detach();
}

void DirectX12Device::CreateDevice(IDXGIAdapter1* _adapter, ID3D12Device** _device)
{
	ThrowIfFailed(D3D12CreateDevice(_adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(_device)), "CreateCommandQueue: Device creating failed!");
}

void DirectX12Device::CreateFactory(IDXGIFactory4** _factory)
{
	UINT dxgiFactoryFlags = 0;

	ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(_factory)), "DirectX12Device::CreateFactory: Factory creating failed!");
}
