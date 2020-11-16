#pragma once
#include "Injector/Mathematics/Matrix4.hpp"
#include "Injector/Graphics/GpuDrawMode.hpp"

namespace Injector
{
	class GpuPipeline
	{
	 protected:
		GpuDrawMode drawMode;
	 public:
		// TODO: add other pipeline parameters from vulakn pipeline
		// Ex: glPolygonMode
		explicit GpuPipeline(
			GpuDrawMode drawMode);
		GpuPipeline(const GpuPipeline& pipeline) = delete;
		GpuPipeline(GpuPipeline&& pipeline) = delete;
		virtual ~GpuPipeline() = default;

		GpuDrawMode getDrawMode() const noexcept;

		virtual void setUniforms(
			const FloatMatrix4& model,
			const FloatMatrix4& view,
			const FloatMatrix4& proj,
			const FloatMatrix4& viewProj,
			const FloatMatrix4& mvp) = 0;
	};
}
