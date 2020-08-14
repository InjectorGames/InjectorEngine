#pragma once
#include <injector/mathematics/matrix4.hpp>

namespace INJECTOR_NAMESPACE
{
	class ColorPipeline
	{
	protected:
		Matrix4 mvp;
		Vector4 color;
	public:
		ColorPipeline(
			const Matrix4& mvp = Matrix4::identity,
			const Vector4& color = Vector4::one);
		virtual ~ColorPipeline();

		const Matrix4& getMVP() const noexcept;
		const Vector4& getColor() const noexcept;

		void setMVP(const Matrix4& mvp) noexcept;
		void setColor(const Vector4& color) noexcept;
	};
}
