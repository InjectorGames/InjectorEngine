#pragma once
#include <injector/mathematics/matrix4.hpp>
#include <memory>

namespace INJECTOR_NAMESPACE
{
	class Pipeline
	{
	public:
		virtual ~Pipeline();

		virtual void setUniforms(
			const Matrix4& model,
			const Matrix4& view,
			const Matrix4& proj,
			const Matrix4& viewProj,
			const Matrix4& mvp);
	};

	using PipelineHandle = std::shared_ptr<Pipeline>;
}
