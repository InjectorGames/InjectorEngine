#pragma once
#include <injector/defines.hpp>
#include <vulkan/vulkan.hpp>

#include <string>
#include <vector>

namespace INJECTOR_NAMESPACE
{
	class VkShader
	{
	protected:
		vk::Device device;
		vk::ShaderModule shaderModule;
	public:
		VkShader(const vk::Device& device,
			const std::vector<uint32_t>& code);
		VkShader(const vk::Device& device,
			const std::vector<char>& code);
		virtual ~VkShader();

		vk::Device getDevice() const noexcept;
		vk::ShaderModule getShaderModule() const noexcept;
	};

	using VkShaderHandle = std::shared_ptr<VkShader>;
}
