#pragma once
#include "Injector/Graphics/GpuMesh.hpp"
#include "Injector/Graphics/GpuDrawMode.hpp"
#include "Injector/Mathematics/Matrix4.hpp"

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

		virtual void onRender() = 0;

		virtual bool addMesh(
			const std::shared_ptr<GpuMesh>& mesh) = 0;
		virtual bool removeMesh(
			const std::shared_ptr<GpuMesh>& mesh) = 0;
	};
}
