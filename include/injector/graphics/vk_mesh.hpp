#pragma once
#include <injector/graphics/mesh.hpp>
#include <injector/graphics/vk_buffer.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkMesh : public Mesh
	{
	protected:
		vk::IndexType index;
		VkBufferHandle vertexBuffer;
		VkBufferHandle indexBuffer;
	public:
		VkMesh(vk::IndexType index,
			size_t indexCount,
			const VkBufferHandle& vertexBuffer,
			const VkBufferHandle& indexBuffer);
		virtual ~VkMesh();

		MeshIndex getIndex() const override;
		void setIndex(MeshIndex index) override;

		const BufferHandle& getVertexBuffer() const override;
		const BufferHandle& getIndexBuffer() const override;

		void draw(vk::CommandBuffer commandBuffer);

		static vk::IndexType toVkIndex(MeshIndex index);
		static MeshIndex toIndex(vk::IndexType index);
	};

	using VkMeshHandle = std::shared_ptr<VkMesh>;
}
