#pragma once
#include "Injector/Mathematics/Matrix4.hpp"

namespace Injector
{
	class GpuPipeline
	{
	 public:
		virtual ~GpuPipeline();

		virtual void setUniforms(
			const Matrix4& model,
			const Matrix4& view,
			const Matrix4& proj,
			const Matrix4& viewProj,
			const Matrix4& mvp);
	};
}
