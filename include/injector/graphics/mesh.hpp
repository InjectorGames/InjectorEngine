#pragma once
#include "Injector/Graphics/BufferIndex.hpp"
#include <cstdlib>

namespace Injector::Graphics
{
	class Mesh
	{
	public:
		size_t indexCount;
		BufferIndex indexType;

		Mesh(size_t indexCount, BufferIndex indexType);
		virtual ~Mesh();

		virtual void setVertexData(void* data, size_t size);
		virtual void setVertexData(void* data, size_t size, size_t offset);

		virtual void setIndexData(void* data, size_t size);
		virtual void setIndexData(void* data, size_t size, size_t offset);
	};
}
