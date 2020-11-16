#pragma once
#include "Injector/Graphics/Vulkan/VkGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/ColorGpuPipeline.hpp"
#include "Injector/Graphics/Vulkan/VkGpuShader.hpp"

namespace Injector
{
	class VkColorGpuPipeline :
		public VkGpuPipeline,
		public ColorGpuPipeline
	{
	 protected:
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;

		std::shared_ptr<VkGpuShader> vertexShader;
		std::shared_ptr<VkGpuShader> fragmentShader;

		FloatVector4 color;

		static vk::PipelineLayout createPipelineLayout(
			vk::Device device);
		static vk::Pipeline createPipeline(
			vk::Device device,
			vk::PipelineCache pipelineCache,
			vk::PipelineLayout pipelineLayout,
			vk::RenderPass renderPass,
			const vk::Extent2D& surfaceExtent,
			vk::PrimitiveTopology primitiveTopology,
			const std::shared_ptr<VkGpuShader>& vertexShader,
			const std::shared_ptr<VkGpuShader>& fragmentShader);
	 public:
		VkColorGpuPipeline(
			vk::Device device,
			vk::RenderPass renderPass,
			const vk::Extent2D& surfaceExtent,
			GpuDrawMode drawMode,
			const std::shared_ptr<VkGpuShader>& vertexShader,
			const std::shared_ptr<VkGpuShader>& fragmentShader,
			const FloatVector4& color);
		~VkColorGpuPipeline() override;

		const FloatVector4& getColor() const override;
		void setColor(const FloatVector4& color) override;

		void recreate(
			VmaAllocator allocator,
			vk::RenderPass renderPass,
			uint32_t imageCount,
			const vk::Extent2D& surfaceExtent) override;
		void flush(
			size_t imageIndex) override;
		void bind(
			vk::CommandBuffer commandBuffer,
			size_t imageIndex) override;
		void setUniforms(
			const FloatMatrix4& model,
			const FloatMatrix4& view,
			const FloatMatrix4& proj,
			const FloatMatrix4& viewProj,
			const FloatMatrix4& mvp) override;
	};
}
