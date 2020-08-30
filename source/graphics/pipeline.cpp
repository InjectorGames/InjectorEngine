#include <injector/graphics/pipeline.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
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
		throw std::runtime_error("Not implemented pipeline function");
	}
}
