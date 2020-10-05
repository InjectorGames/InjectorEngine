#pragma once
#include "vulkan/vulkan.hpp"
#include <vector>

namespace Injector
{
	class VkGpuShader
	{
	 protected:
		vk::Device device;
		vk::ShaderModule shaderModule;
	 public:
		VkGpuShader(
			const vk::Device& device,
			const std::vector<uint32_t>& code);
		VkGpuShader(
			const vk::Device& device,
			const std::vector<char>& code);

		// TODO: change to override
		virtual ~VkGpuShader();

		vk::Device getDevice() const noexcept;
		vk::ShaderModule getShaderModule() const noexcept;
	};
}
