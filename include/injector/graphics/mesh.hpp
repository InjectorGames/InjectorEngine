#pragma once
#include <injector/graphics/buffer.hpp>
#include <injector/graphics/mesh_index.hpp>

namespace INJECTOR_NAMESPACE
{
	class Mesh
	{
	protected:
		size_t indexCount;
		MeshIndex indexType;
		BufferHandle vertexBuffer;
		BufferHandle indexBuffer;
	public:
		Mesh(size_t indexCount,
			MeshIndex indexType,
			const BufferHandle& vertexBuffer,
			const BufferHandle& indexBuffer);
		virtual ~Mesh();

		size_t getIndexCount() const noexcept;
		MeshIndex getIndexType() const noexcept;
		BufferHandle getVertexBuffer() const noexcept;
		BufferHandle getIndexBuffer() const noexcept;
	};

	using MeshHandle = std::shared_ptr<Mesh>;
}
