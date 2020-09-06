#pragma once
#include "Injector/Graphics/Pipeline.hpp"

namespace Injector::Graphics
{
	class ColorPipeline : public Pipeline
	{
	public:
		virtual ~ColorPipeline();

		virtual const Vector4& getColor() const;
		virtual void setColor(const Vector4& color);
	};
}
