#include <injector/graphics/mesh.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Mesh::~Mesh()
	{}

	MeshIndex Mesh::getIndex() const
	{
		throw std::runtime_error("Not implemented mesh function");
	}
	void Mesh::setIndex(MeshIndex index)
	{
		throw std::runtime_error("Not implemented mesh function");
	}

	const BufferHandle& Mesh::getVertexBuffer() const
	{
		throw std::runtime_error("Not implemented mesh function");
	}
	const BufferHandle& Mesh::getIndexBuffer() const
	{
		throw std::runtime_error("Not implemented mesh function");
	}
}
