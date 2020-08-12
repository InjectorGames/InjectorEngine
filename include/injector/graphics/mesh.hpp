#pragma once
#include <injector/graphics/buffer.hpp>
#include <injector/graphics/mesh_index.hpp>

namespace INJECTOR_NAMESPACE
{
	class Mesh
	{
	protected:
		size_t indexCount;
	public:
		Mesh(size_t indexCount);
		virtual ~Mesh();

		size_t getIndexCount() const noexcept;

		virtual MeshIndex getIndex() const;
		virtual void setIndex(MeshIndex index);

		virtual const BufferHandle& getVertexBuffer() const;
		virtual const BufferHandle& getIndexBuffer() const;
	};

	using MeshHandle = std::shared_ptr<Mesh>;
}
