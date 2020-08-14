#pragma once
#include <injector/mathematics/matrix4.hpp>

namespace INJECTOR_NAMESPACE
{
	class ColorPipeline
	{
	protected:
		Vector4 color;
	public:
		ColorPipeline(const Vector4& color = Vector4::one);
		virtual ~ColorPipeline();

		const Vector4& getColor() const noexcept;
		void setColor(const Vector4& color) noexcept;
	};
}
