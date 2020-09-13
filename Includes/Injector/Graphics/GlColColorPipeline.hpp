#pragma once
#include "Injector/Graphics/GlColorPipeline.hpp"

namespace Injector
{
	class GlColColorPipeline : public GlColorPipeline
	{
	public:
		GlColColorPipeline(bool gles,
			const Vector4& color = Vector4::one);
		virtual ~GlColColorPipeline();

		void setAttributes() override;
	};
}
