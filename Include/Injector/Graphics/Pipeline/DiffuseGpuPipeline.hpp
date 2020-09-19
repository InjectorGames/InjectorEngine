#pragma once
#include "Injector/Graphics/Pipeline/GpuPipeline.hpp"

namespace Injector
{
	class DiffuseGpuPipeline : public GpuPipeline
	{
	 public:
		virtual ~DiffuseGpuPipeline();

		virtual const Vector4& getObjectColor() const;
		virtual void setObjectColor(const Vector4& color);

		virtual const Vector4& getAmbientColor() const;
		virtual void setAmbientColor(const Vector4& color);

		virtual const Vector4& getLightColor() const;
		virtual void setLightColor(const Vector4& color);

		virtual const Vector3& getLightDirection() const;
		virtual void setLightDirection(const Vector3& direction);
	};
}
