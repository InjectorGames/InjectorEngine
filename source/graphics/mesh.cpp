#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

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

	const std::shared_ptr<Buffer>& Mesh::getVertexBuffer() const noexcept
	{
		return vertexBuffer;
	}
	const std::shared_ptr<Buffer>& Mesh::getIndexBuffer() const noexcept
	{
		return indexBuffer;
	}

	void Mesh::setVertexBuffer(const std::shared_ptr<Buffer>& vertexBuffers)
	{
		throw GraphicsException("Not implemented mesh function");
	}
	void Mesh::setIndexBuffer(const std::shared_ptr<Buffer>& indexBuffer)
	{
		throw GraphicsException("Not implemented mesh function");
	}
}
