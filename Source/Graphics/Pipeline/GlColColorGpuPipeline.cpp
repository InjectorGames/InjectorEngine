#include "Injector/Graphics/Pipeline/GlColColorGpuPipeline.hpp"

namespace Injector
{
	GlColColorGpuPipeline::GlColColorGpuPipeline(
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		const Vector4& color) :
		GlColorGpuPipeline(vertexShader, fragmentShader, color)
	{
	}
	GlColColorGpuPipeline::~GlColColorGpuPipeline()
	{
	}

	void GlColColorGpuPipeline::setAttributes()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		setVertexAttributePointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vector3) + sizeof(Vector4),
			0);
		setVertexAttributePointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vector3) + sizeof(Vector4),
			sizeof(Vector3));
	}
}
