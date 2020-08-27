#pragma once
#include <injector/mathematics/matrix4.hpp>
#include <memory>

namespace INJECTOR_NAMESPACE
{
	class Pipeline
	{
	public:
		virtual ~Pipeline();

		virtual const Matrix4& getModel() const;
		virtual const Matrix4& getView() const;
		virtual const Matrix4& getProj() const;
		virtual const Matrix4& getViewProj() const;
		virtual const Matrix4& getMVP() const;

		virtual void setModel(const Matrix4& model);
		virtual void setView(const Matrix4& view);
		virtual void setProj(const Matrix4& proj);
		virtual void setViewProj(const Matrix4& proj);
		virtual void setMVP(const Matrix4& color);
	};

	using PipelineHandle = std::shared_ptr<Pipeline>;
}
