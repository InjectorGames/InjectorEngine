#pragma once
#include "Injector/Graphics/Pipeline/GpuPipeline.hpp"

namespace Injector
{
	class DiffuseGpuPipeline : public GpuPipeline
	{
	 public:
		virtual const Vector4& getObjectColor() const = 0;
		virtual void setObjectColor(const Vector4& color) = 0;

		virtual const Vector4& getAmbientColor() const = 0;
		virtual void setAmbientColor(const Vector4& color) = 0;

		virtual const Vector4& getLightColor() const = 0;
		virtual void setLightColor(const Vector4& color) = 0;

		virtual const Vector3& getLightDirection() const = 0;
		virtual void setLightDirection(const Vector3& direction) = 0;
	};
}
