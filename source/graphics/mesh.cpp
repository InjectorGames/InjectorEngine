#include <injector/graphics/mesh.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Mesh::Mesh(
		size_t _indexCount,
		MeshIndex _indexType,
		const BufferHandle& _vertexBuffer,
		const BufferHandle& _indexBuffer) :
		indexCount(_indexCount),
		indexType(_indexType),
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer)
	{}
	Mesh::~Mesh()
	{}

	size_t Mesh::getIndexCount() const noexcept
	{
		return indexCount;
	}
	MeshIndex Mesh::getIndexType() const noexcept
	{
		return indexType;
	}
	BufferHandle Mesh::getVertexBuffer() const noexcept
	{
		return vertexBuffer;
	}
	BufferHandle Mesh::getIndexBuffer() const noexcept
	{
		throw std::runtime_error("Not implemented mesh function");
	}
}
