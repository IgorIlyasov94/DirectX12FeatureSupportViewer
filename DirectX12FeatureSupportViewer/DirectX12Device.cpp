#include "DirectX12Device.h"

DirectX12Device::DirectX12Device()
{
	CreateFactory(&factory);

	GetHardwareAdapter(factory.Get(), &adapter);

	CreateDevice(adapter.Get(), &device);

	adapter->GetDesc(&adapterDesc);
}

DirectX12Device::~DirectX12Device()
{

}

void DirectX12Device::CheckHighestShaderModelSupport(int& majorVersion, int& minorVersion)
{
	D3D12_FEATURE_DATA_SHADER_MODEL dataShaderModel{ D3D_SHADER_MODEL_6_6 };

	device->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &dataShaderModel, sizeof(dataShaderModel));

	majorVersion = static_cast<int>(dataShaderModel.HighestShaderModel) / 16;
	minorVersion = static_cast<int>(dataShaderModel.HighestShaderModel) % 16;
}

void DirectX12Device::CheckBasicFeaturesSupport(bool& doublePrecisionFloatShaderSupport, int& minShaderDataPrecisionBitsSupport, bool& rasterizerOrderViewSupport,
	int& maxConservativeRasterizationTier)
{
	D3D12_FEATURE_DATA_D3D12_OPTIONS dataOptions{};

	device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS, &dataOptions, sizeof(dataOptions));

	doublePrecisionFloatShaderSupport = dataOptions.DoublePrecisionFloatShaderOps;
	minShaderDataPrecisionBitsSupport = (dataOptions.MinPrecisionSupport == D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT) ? 10 :
		(dataOptions.MinPrecisionSupport == D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT) ? 16 : 32;
	rasterizerOrderViewSupport = dataOptions.ROVsSupported;
	maxConservativeRasterizationTier = static_cast<int>(dataOptions.ConservativeRasterizationTier);
}

void DirectX12Device::CheckRaytracingSupport(int& majorVersion, int& minorVersion)
{
	D3D12_FEATURE_DATA_D3D12_OPTIONS5 dataOptions{};

	device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &dataOptions, sizeof(dataOptions));

	majorVersion = dataOptions.RaytracingTier / 10;
	minorVersion = dataOptions.RaytracingTier % 10;
}

void DirectX12Device::CheckVariableShadingRate(int& maxVariableShadingRateTier)
{
	D3D12_FEATURE_DATA_D3D12_OPTIONS6 dataOptions{};

	device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS6, &dataOptions, sizeof(dataOptions));

	maxVariableShadingRateTier = dataOptions.VariableShadingRateTier;
}

bool DirectX12Device::CheckMeshAndAmplificationShadersSupport()
{
	D3D12_FEATURE_DATA_D3D12_OPTIONS7 dataOptions{};

	device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS7, &dataOptions, sizeof(dataOptions));

	return dataOptions.MeshShaderTier == D3D12_MESH_SHADER_TIER_1;
}

std::wstring DirectX12Device::GetAdapterDescription()
{
	return adapterDesc.Description;
}

SIZE_T DirectX12Device::GetDedicatedVideoMemory()
{
	return adapterDesc.DedicatedVideoMemory;
}

SIZE_T DirectX12Device::GetDedicatedSystemMemory()
{
	return adapterDesc.DedicatedSystemMemory;
}

SIZE_T DirectX12Device::GetSharedSystemMemory()
{
	return adapterDesc.SharedSystemMemory;
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
