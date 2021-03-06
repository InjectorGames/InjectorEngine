#include "Injector/Graphics/OpenGL/Pipeline/GlColorColorGpuPipeline.hpp"

namespace Injector
{
	GlColorColorGpuPipeline::GlColorColorGpuPipeline(
		GpuDrawMode drawMode,
		const std::shared_ptr<GlGpuShader>& vertexShader,
		const std::shared_ptr<GlGpuShader>& fragmentShader,
		const FloatVector4& color) :
		GlColorGpuPipeline(
			drawMode,
			vertexShader,
			fragmentShader,
			color)
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
			sizeof(FloatVector3) + sizeof(FloatVector4),
			0);
		setVertexAttributePointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(FloatVector3) + sizeof(FloatVector4),
			sizeof(FloatVector3));
	}
}
