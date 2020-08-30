#pragma once
#include <injector/graphics/mesh.hpp>
#include <injector/graphics/vk_buffer.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkMesh : public Mesh
	{
	protected:
		VkBufferHandle vertexBuffer;
		VkBufferHandle indexBuffer;
	public:
		VkMesh(
			size_t indexCount,
			BufferIndex indexType,
			const VkBufferHandle& vertexBuffer,
			const VkBufferHandle& indexBuffer);
		virtual ~VkMesh();

		const VkBufferHandle& getVertexBuffer() const noexcept;
		const VkBufferHandle& getIndexBuffer() const noexcept;

		void draw(vk::CommandBuffer commandBuffer) noexcept;

		void setVertexData(void* data, size_t size) override;
		void setVertexData(void* data, size_t size, size_t offset) override;

		void setIndexData(void* data, size_t size) override;
		void setIndexData(void* data, size_t size, size_t offset) override;
	};

	using VkMeshHandle = std::shared_ptr<VkMesh>;
}
