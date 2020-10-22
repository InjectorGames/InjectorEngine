#pragma once
#include "Injector/Mathematics/Matrix/Matrix4.hpp"
#include "Injector/Graphics/PrimitiveTopology.hpp"

namespace Injector
{
	class GpuPipeline
	{
	 protected:
		PrimitiveTopology primitiveTopology;
	 public:
		// TODO: add other pipeline parameters from vulakn pipeline
		// Ex: glPolygonMode
		explicit GpuPipeline(
			PrimitiveTopology primitiveTopology);
		GpuPipeline(const GpuPipeline& pipeline) = delete;
		GpuPipeline(GpuPipeline&& pipeline) = delete;
		virtual ~GpuPipeline() = default;

		PrimitiveTopology getPrimitiveTopology() const noexcept;

		virtual void setUniforms(
			const Matrix4& model,
			const Matrix4& view,
			const Matrix4& proj,
			const Matrix4& viewProj,
			const Matrix4& mvp) = 0;
	};
}
