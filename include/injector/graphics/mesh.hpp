#pragma once
#include <injector/graphics/buffer.hpp>
#include <injector/graphics/mesh_index.hpp>

namespace INJECTOR_NAMESPACE
{
	class Mesh
	{
	public:
		virtual ~Mesh();

		virtual MeshIndex getIndex() const;
		virtual void setIndex(MeshIndex index);

		virtual const BufferHandle& getVertexBuffer() const;
		virtual const BufferHandle& getIndexBuffer() const;
	};

	using MeshHandle = std::shared_ptr<Mesh>;
}
