#pragma once
#include "vulkan/vulkan.hpp"
#include <vector>

namespace Injector::Graphics
{
	using namespace std;

	class VkShader
	{
	protected:
		vk::Device device;
		vk::ShaderModule shaderModule;
	public:
		VkShader(const vk::Device& device,
			const vector<uint32_t>& code);
		VkShader(const vk::Device& device,
			const vector<char>& code);
		virtual ~VkShader();

		vk::Device getDevice() const noexcept;
		vk::ShaderModule getShaderModule() const noexcept;
	};
}
