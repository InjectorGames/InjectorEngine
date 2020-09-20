#include "Injector/Graphics/Pipeline/GpuPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	GpuPipeline::~GpuPipeline()
	{
	}

	void GpuPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		throw NotImplementedException(
			"GpuPipeline",
			"setUniforms");
	}
}
