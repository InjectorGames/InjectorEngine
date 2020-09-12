#pragma once
#include "Injector/Graphics/Buffer.hpp"
#include "Injector/Graphics/BufferIndex.hpp"

#include <vector>
#include <cstdlib>

namespace Injector
{
	class Mesh
	{
	protected:
		std::shared_ptr<Buffer> vertexBuffer;
		std::shared_ptr<Buffer> indexBuffer;
	public:
		size_t indexCount;
		BufferIndex indexType;

		Mesh(size_t indexCount,
			BufferIndex indexType,
			const std::shared_ptr<Buffer>& vertexBuffer,
			const std::shared_ptr<Buffer>& indexBuffer);
		virtual ~Mesh();

		const std::shared_ptr<Buffer>& getVertexBuffer() const noexcept;
		const std::shared_ptr<Buffer>& getIndexBuffer() const noexcept;

		virtual void setVertexBuffer(const std::shared_ptr<Buffer>& vertexBuffer);
		virtual void setIndexBuffer(const std::shared_ptr<Buffer>& indexBuffer);
	};
}
