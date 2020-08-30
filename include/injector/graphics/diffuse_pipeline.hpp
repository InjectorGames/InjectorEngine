#pragma once
#include <injector/graphics/pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	class DiffusePipeline : public Pipeline
	{
	public:
		virtual ~DiffusePipeline();

		virtual const Vector4& getObjectColor() const;
		virtual void setObjectColor(const Vector4& objectColor);

		virtual const Vector4& getAmbientColor() const;
		virtual void setAmbientColor(const Vector4& ambientColor);

		virtual const Vector4& getLightColor() const;
		virtual void setLightColor(const Vector4& lightColor);

		virtual const Vector3& getLightDirection() const;
		virtual void setLightDirection(const Vector3& lightDirection);
	};

	using DiffusePipelineHandle = std::shared_ptr<DiffusePipeline>;
}
