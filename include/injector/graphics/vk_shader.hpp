#pragma once
#include <injector/graphics/shader.hpp>
#include <vulkan/vulkan.hpp>

#include <string>
#include <vector>

namespace INJECTOR_NAMESPACE
{
	class VkShader : public Shader
	{
	protected:
		vk::Device device;
		vk::ShaderModule shaderModule;
	public:
		VkShader(const vk::Device& device,
			const std::string& path,
			ShaderStage stage);
		virtual ~VkShader();

		vk::Device getDevice() const noexcept;
		vk::ShaderModule getShaderModule() const noexcept;

		static vk::ShaderStageFlagBits toVkStage(ShaderStage stage);
		static ShaderStage toStage(vk::ShaderStageFlagBits stage);
	};

	using VkShaderHandle = std::shared_ptr<VkShader>;
}
