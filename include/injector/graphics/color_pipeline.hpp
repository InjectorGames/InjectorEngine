#pragma once
#include <injector/graphics/pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	class ColorPipeline : public Pipeline
	{
	public:
		virtual ~ColorPipeline();

		virtual const Vector4& getColor() const;
		virtual void setColor(const Vector4& color);
	};

	using ColorPipelineHandle = std::shared_ptr<ColorPipeline>;
}
