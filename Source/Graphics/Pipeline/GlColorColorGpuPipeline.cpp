#include "Injector/Graphics/Pipeline/GlColorColorGpuPipeline.hpp"

namespace Injector
{
	GlColorColorGpuPipeline::GlColorColorGpuPipeline(
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		const Vector4& color) :
		GlColorGpuPipeline(vertexShader, fragmentShader, color)
	{
	}
	GlColorColorGpuPipeline::~GlColorColorGpuPipeline()
	{
	}

	void GlColorColorGpuPipeline::setAttributes()
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
