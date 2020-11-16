#pragma once
#include "Injector/Mathematics/Vector4.hpp"

namespace Injector
{
	class DiffuseGpuPipeline
	{
	 public:
		virtual const FloatVector4& getObjectColor() const = 0;
		virtual void setObjectColor(const FloatVector4& color) = 0;

		virtual const FloatVector4& getAmbientColor() const = 0;
		virtual void setAmbientColor(const FloatVector4& color) = 0;

		virtual const FloatVector4& getLightColor() const = 0;
		virtual void setLightColor(const FloatVector4& color) = 0;

		virtual const FloatVector3& getLightDirection() const = 0;
		virtual void setLightDirection(const FloatVector3& direction) = 0;
	};
}
