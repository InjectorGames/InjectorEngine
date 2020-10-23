#pragma once
#include "Injector/Graphics/GpuShader.hpp"
#include "Injector/Graphics/ShaderData.hpp"

#include "vulkan/vulkan.hpp"
#include <vector>

namespace Injector
{
	class VkGpuShader : public GpuShader
	{
	 protected:
		vk::Device device;
		vk::ShaderModule shaderModule;
	 public:
		VkGpuShader(
			vk::Device device,
			GpuShaderStage stage,
			const std::shared_ptr<ShaderData>& data);
		~VkGpuShader() override;

		vk::Device getDevice() const noexcept;
		vk::ShaderModule getShaderModule() const noexcept;
	};
}
