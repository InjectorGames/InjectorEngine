#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	Mesh::Mesh(
		size_t _indexCount,
		BufferIndex _indexType,
		const std::shared_ptr<Buffer>& _vertexBuffer,
		const std::shared_ptr<Buffer>& _indexBuffer) :
		indexCount(_indexCount),
		indexType(_indexType),
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer)
	{}
	Mesh::~Mesh()
	{}

	std::shared_ptr<Buffer> Mesh::getVertexBuffer() const noexcept
	{
		return vertexBuffer;
	}
	std::shared_ptr<Buffer> Mesh::getIndexBuffer() const noexcept
	{
		return indexBuffer;
	}

	void Mesh::setVertexBuffer(const std::shared_ptr<Buffer>& vertexBuffers)
	{
		throw NotImplementedException("Mesh", "setVertexBuffer");
	}
	void Mesh::setIndexBuffer(const std::shared_ptr<Buffer>& indexBuffer)
	{
		throw NotImplementedException("Mesh", "setIndexBuffer");
	}
}
