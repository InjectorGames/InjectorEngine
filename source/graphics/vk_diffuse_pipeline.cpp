#include <injector/graphics/vk_diffuse_pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	vk::Pipeline VkDiffusePipeline::createPipeline(
		vk::Device device,
		vk::PipelineCache pipelineCache,
		vk::PipelineLayout pipelineLayout,
		vk::RenderPass renderPass,
		const vk::Extent2D& surfaceExtent)
	{
		return nullptr;
	}

	VkDiffusePipeline::VkDiffusePipeline(
		vk::Device device,
		vk::RenderPass renderPass,
		const vk::Extent2D& surfaceExtent) :
		VkPipeline(device)
	{

	}
	VkDiffusePipeline::~VkDiffusePipeline()
	{

	}

	void VkDiffusePipeline::recreate(
		uint32_t imageCount,
		vk::RenderPass renderPass,
		vk::Extent2D surfaceExtent)
	{

	}
	void VkDiffusePipeline::bind(
		uint32_t imageIndex,
		vk::CommandBuffer commandBuffer)
	{

	}

	const Matrix4& VkDiffusePipeline::getModel() const
	{
		return model;
	}
	void VkDiffusePipeline::setModel(const Matrix4& _model)
	{
		model = _model;
	}

	const Matrix4& VkDiffusePipeline::getMVP() const
	{
		return mvp;
	}
	void VkDiffusePipeline::setMVP(const Matrix4& _mvp)
	{
		mvp = _mvp;
	}

	const Vector4& VkDiffusePipeline::getObjectColor() const
	{
		return objectColor;
	}
	void VkDiffusePipeline::setObjectColor(const Vector4& _objectColor)
	{
		objectColor = _objectColor;
	}

	const Vector4& VkDiffusePipeline::getAmbientColor() const
	{
		return ambientColor;
	}
	void VkDiffusePipeline::setAmbientColor(const Vector4& _ambientColor)
	{
		ambientColor = _ambientColor;
	}

	const Vector4& VkDiffusePipeline::getLightColor() const
	{
		return lightColor;
	}
	void VkDiffusePipeline::setLightColor(const Vector4& _lightColor)
	{
		lightColor = _lightColor;
	}

	const Vector3& VkDiffusePipeline::getLightDirection() const
	{
		return lightDirection;
	}
	void VkDiffusePipeline::setLightDirection(const Vector3& _lightDirection)
	{
		lightDirection = _lightDirection;
	}
}
