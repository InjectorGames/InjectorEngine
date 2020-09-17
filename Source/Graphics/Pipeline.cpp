#include "Injector/Graphics/Pipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	Pipeline::~Pipeline()
	{}

	void Pipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		throw NotImplementedException("Pipeline", "setUniforms");
	}
}
