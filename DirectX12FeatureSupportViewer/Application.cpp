#include "Application.h"
#include "DirectX12Device.h"

Application::Application()
{

}

Application::~Application()
{

}

int Application::Run()
{
	try
	{
		DirectX12Device device;

		bool shaderDoubleTypeSupport{};
		int minShaderTypePrecisionBits{};
		bool rasterizerOrderViewSupport{};
		int maxConservativeRasterizationTier{};
		int highestMajorShaderVersion{};
		int highestMinorShaderVersion{};
		int highestRaytracingMajorVersion{};
		int highestRaytracingMinorVersion{};
		int maxVariableShadingRateTier{};
		bool meshAndAmplificationShadersSupport{};
		std::wstring adapterDescription;
		SIZE_T dedicatedVideoMemory{};
		SIZE_T dedicatedSystemMemory{};
		SIZE_T sharedSystemMemory{};

		device.CheckBasicFeaturesSupport(shaderDoubleTypeSupport, minShaderTypePrecisionBits, rasterizerOrderViewSupport, maxConservativeRasterizationTier);
		device.CheckHighestShaderModelSupport(highestMajorShaderVersion, highestMinorShaderVersion);
		device.CheckRaytracingSupport(highestRaytracingMajorVersion, highestRaytracingMinorVersion);
		device.CheckVariableShadingRate(maxVariableShadingRateTier);

		meshAndAmplificationShadersSupport = device.CheckMeshAndAmplificationShadersSupport();
		adapterDescription = device.GetAdapterDescription();
		dedicatedVideoMemory = device.GetDedicatedVideoMemory();
		dedicatedSystemMemory = device.GetDedicatedSystemMemory();
		sharedSystemMemory = device.GetSharedSystemMemory();

		std::wcout << adapterDescription << std::endl << std::endl;
		std::cout << "Dedicated Video Memory: " << dedicatedVideoMemory / (1024 * 1024) << " MB" << std::endl;
		std::cout << "Dedicated System Memory: " << dedicatedSystemMemory / (1024 * 1024) << " MB" << std::endl;
		std::cout << "Shared System Memory: " << sharedSystemMemory / (1024 * 1024) << " MB" << std::endl << std::endl;

		std::cout << "Support Shader Model " << highestMajorShaderVersion << '.' << highestMinorShaderVersion << std::endl;
		std::cout << "Shader double precision float ";

		if (shaderDoubleTypeSupport)
			std::cout << "supported" << std::endl;
		else
			std::cout << "is not supported" << std::endl;

		std::cout << "Minimum precision of the shader data types: " << minShaderTypePrecisionBits << "-bit" << std::endl << std::endl;

		std::cout << "Rasterizer Order View ";

		if (rasterizerOrderViewSupport)
			std::cout << "supported" << std::endl;
		else
			std::cout << "is not supported" << std::endl;

		std::cout << "Conservative Rasterization ";

		if (maxConservativeRasterizationTier > 0)
			std::cout << "Tier " << maxConservativeRasterizationTier << " supported" << std::endl << std::endl;
		else
			std::cout << "is not supported" << std::endl << std::endl;

		std::cout << "DirectX Raytracing ";

		if ((highestRaytracingMajorVersion + highestRaytracingMinorVersion) > 0)
			std::cout << "Tier " << highestRaytracingMajorVersion << '.' << highestRaytracingMinorVersion << " supported" << std::endl << std::endl;
		else
			std::cout << "is not supported" << std::endl << std::endl;

		std::cout << "Variable Shading Rate ";

		if (maxVariableShadingRateTier > 0)
			std::cout << "Tier " << maxVariableShadingRateTier << " supported" << std::endl << std::endl;
		else
			std::cout << "is not supported" << std::endl << std::endl;

		std::cout << "Mesh & Amplification Shaders ";

		if (meshAndAmplificationShadersSupport)
			std::cout << "supported" << std::endl;
		else
			std::cout << "is not supported" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << std::endl << e.what() << std::endl;
	}

	return 0;
}
