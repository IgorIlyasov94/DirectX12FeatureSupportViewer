#pragma once

#include "Includes.h"

class DirectX12Device
{
public:
	DirectX12Device();
	~DirectX12Device();

	void CheckHighestShaderModelSupport(int& majorVersion, int& minorVersion);
	void CheckBasicFeaturesSupport(bool& doublePrecisionFloatShaderSupport, int& minShaderDataPrecisionBitsSupport, bool& rasterizerOrderViewSupport,
		int& maxConservativeRasterizationTier);
	void CheckRaytracingSupport(int& majorVersion, int& minorVersion);
	void CheckVariableShadingRate(int& maxVariableShadingRateTier);
	bool CheckMeshAndAmplificationShadersSupport();

	std::wstring GetAdapterDescription();
	SIZE_T GetDedicatedVideoMemory();
	SIZE_T GetDedicatedSystemMemory();
	SIZE_T GetSharedSystemMemory();

private:
	void GetHardwareAdapter(IDXGIFactory4* _factory, IDXGIAdapter1** _adapter);
	
	void CreateDevice(IDXGIAdapter1* _adapter, ID3D12Device** _device);
	void CreateFactory(IDXGIFactory4** _factory);

	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIAdapter1> adapter;
	ComPtr<IDXGIFactory4> factory;

	DXGI_ADAPTER_DESC adapterDesc;
};
