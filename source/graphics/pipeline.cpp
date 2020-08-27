#include <injector/graphics/pipeline.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Pipeline::~Pipeline()
	{}

	const Matrix4& Pipeline::getModel() const
	{
		throw std::runtime_error("Not implemented pipeline function");
	}
	const Matrix4& Pipeline::getView() const
	{
		throw std::runtime_error("Not implemented pipeline function");
	}
	const Matrix4& Pipeline::getProj() const
	{
		throw std::runtime_error("Not implemented pipeline function");
	}
	const Matrix4& Pipeline::getViewProj() const
	{
		throw std::runtime_error("Not implemented pipeline function");
	}
	const Matrix4& Pipeline::getMVP() const
	{
		throw std::runtime_error("Not implemented pipeline function");
	}

	void Pipeline::setModel(const Matrix4& model)
	{}
	void Pipeline::setView(const Matrix4& view)
	{}
	void Pipeline::setProj(const Matrix4& proj)
	{}
	void Pipeline::setViewProj(const Matrix4& proj)
	{}
	void Pipeline::setMVP(const Matrix4& proj)
	{}
}
