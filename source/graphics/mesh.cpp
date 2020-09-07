#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector
{
	Mesh::Mesh(
		size_t _indexCount,
		BufferIndex _indexType) :
		indexCount(_indexCount),
		indexType(_indexType)
	{}
	Mesh::~Mesh()
	{}

	void Mesh::setVertexData(void* data, size_t size)
	{
		throw GraphicsException("Not implemented mesh function");
	}
	void Mesh::setVertexData(void* data, size_t size, size_t offset)
	{
		throw GraphicsException("Not implemented mesh function");
	}

	void Mesh::setIndexData(void* data, size_t size)
	{
		throw GraphicsException("Not implemented mesh function");
	}
	void Mesh::setIndexData(void* data, size_t size, size_t offset)
	{
		throw GraphicsException("Not implemented mesh function");
	}
}
