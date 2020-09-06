#pragma once
#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/VkBuffer.hpp"

#include <memory>

namespace Injector::Graphics
{
	using namespace std;

	class VkMesh : public Mesh
	{
	protected:
		shared_ptr<VkBuffer> vertexBuffer;
		shared_ptr<VkBuffer> indexBuffer;
	public:
		VkMesh(
			size_t indexCount,
			BufferIndex indexType,
			const shared_ptr<VkBuffer>& vertexBuffer,
			const shared_ptr<VkBuffer>& indexBuffer);
		virtual ~VkMesh();

		const shared_ptr<VkBuffer>& getVertexBuffer() const noexcept;
		const shared_ptr<VkBuffer>& getIndexBuffer() const noexcept;

		void draw(vk::CommandBuffer commandBuffer) noexcept;

		void setVertexData(void* data, size_t size) override;
		void setVertexData(void* data, size_t size, size_t offset) override;

		void setIndexData(void* data, size_t size) override;
		void setIndexData(void* data, size_t size, size_t offset) override;
	};
}
