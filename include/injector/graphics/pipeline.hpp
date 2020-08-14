#pragma once
#include <injector/mathematics/matrix4.hpp>
#include <memory>

namespace INJECTOR_NAMESPACE
{
	class Pipeline
	{
	protected:
		Matrix4 model;
		Matrix4 view;
		Matrix4 proj;
		Matrix4 mvp;
	public:
		Pipeline(
			const Matrix4& model = Matrix4::identity,
			const Matrix4& view = Matrix4::identity,
			const Matrix4& proj = Matrix4::identity,
			const Matrix4& mvp = Matrix4::identity);
		virtual ~Pipeline();

		const Matrix4& getModel() const noexcept;
		const Matrix4& getView() const noexcept;
		const Matrix4& getProj() const noexcept;
		const Matrix4& getMVP() const noexcept;

		void setModel(const Matrix4& model) noexcept;
		void setView(const Matrix4& view) noexcept;
		void setProj(const Matrix4& proj) noexcept;
		void setMVP(const Matrix4& mvp) noexcept;
	};

	using PipelineHandle = std::shared_ptr<Pipeline>;
}
