#pragma once
#include <injector/graphics/shader.hpp>

#include <string>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>

namespace INJECTOR_NAMESPACE
{
	class VkShader : public Shader
	{
	protected:
		vk::Device device;
		vk::ShaderModule shaderModule;

		static vk::ShaderModule createShaderModule(
			const vk::Device& device, const std::vector<char>& code);
	public:
		VkShader(ShaderStage stage,
			const vk::Device& device,const std::string& path);
		virtual ~VkShader();

		const vk::Device& getDevice() const noexcept;
		const vk::ShaderModule& getShaderModule() const noexcept;
	};
}
