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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			static_cast<GLsizei>(sizeof(Vector3) + sizeof(Vector4)),
			reinterpret_cast<const GLvoid*>(0));
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
			static_cast<GLsizei>(sizeof(Vector3) + sizeof(Vector4)),
			reinterpret_cast<const GLvoid*>(sizeof(Vector3)));
	}
}
