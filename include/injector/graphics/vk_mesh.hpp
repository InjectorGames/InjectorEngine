#pragma once
#include <injector/graphics/mesh.hpp>
#include <injector/graphics/vk_buffer.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkMesh : public Mesh
	{
	protected:
		vk::IndexType vkIndexType;
		vk::Buffer vkVertexBuffer;
		vk::Buffer vkIndexBuffer;
	public:
		VkMesh(size_t indexCount,
			MeshIndex indexType,
			const VkBufferHandle& vertexBuffer,
			const VkBufferHandle& indexBuffer);
		virtual ~VkMesh();

		vk::IndexType getVkIndexType() const noexcept;
		vk::Buffer getVkVertexBuffer() const noexcept;
		vk::Buffer getVkIndexBuffer() const noexcept;

		void draw(vk::CommandBuffer commandBuffer) noexcept;

		static vk::IndexType toVkIndexType(MeshIndex indexType);
		static MeshIndex toIndexType(vk::IndexType indexType);
	};

	using VkMeshHandle = std::shared_ptr<VkMesh>;
}
