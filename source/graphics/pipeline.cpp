#include <injector/graphics/pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	Pipeline::Pipeline(
		const Matrix4& _model,
		const Matrix4& _view,
		const Matrix4& _proj,
		const Matrix4& _mvp) :
		model(_model),
		view(_view),
		proj(_proj),
		mvp(_mvp)
	{}
	Pipeline::~Pipeline()
	{}

	const Matrix4& Pipeline::getModel() const noexcept
	{
		return model;
	}
	const Matrix4& Pipeline::getView() const noexcept
	{
		return view;
	}
	const Matrix4& Pipeline::getProj() const noexcept
	{
		return view;
	}
	const Matrix4& Pipeline::getMVP() const noexcept
	{
		return mvp;
	}

	void Pipeline::setModel(const Matrix4& _model) noexcept
	{
		model = Matrix4(_model);
	}
	void Pipeline::setView(const Matrix4& _view) noexcept
	{
		view = Matrix4(_view);
	}
	void Pipeline::setProj(const Matrix4& _proj) noexcept
	{
		proj = _proj;
	}
	void Pipeline::setMVP(const Matrix4& _mvp) noexcept
	{
		mvp = _mvp;
	}
}
