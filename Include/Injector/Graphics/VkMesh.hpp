#pragma once
#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/VkBuffer.hpp"

#include <memory>

namespace Injector
{
	class VkMesh : public Mesh
	{
	protected:
		std::shared_ptr<VkBuffer> vertexBuffer;
		std::shared_ptr<VkBuffer> indexBuffer;
	public:
		VkMesh(
			size_t indexCount,
			BufferIndex indexType,
			const std::shared_ptr<VkBuffer>& vertexBuffer,
			const std::shared_ptr<VkBuffer>& indexBuffer);
		virtual ~VkMesh();

		const std::shared_ptr<VkBuffer>& getVertexBuffer() const noexcept;
		const std::shared_ptr<VkBuffer>& getIndexBuffer() const noexcept;

		void draw(vk::CommandBuffer commandBuffer) noexcept;

		void setVertexData(void* data, size_t size) override;
		void setVertexData(void* data, size_t size, size_t offset) override;

		void setIndexData(void* data, size_t size) override;
		void setIndexData(void* data, size_t size, size_t offset) override;
	};
}
