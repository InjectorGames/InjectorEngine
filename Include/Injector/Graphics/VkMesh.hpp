#pragma once
#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/VkBuffer.hpp"

#include <memory>

namespace Injector
{
	class VkMesh : public Mesh
	{
	public:
		VkMesh(size_t indexCount,
			BufferIndex indexType,
			const std::shared_ptr<Buffer>& vertexBuffer,
			const std::shared_ptr<Buffer>& indexBuffer);
		virtual ~VkMesh();

		void draw(vk::CommandBuffer commandBuffer) noexcept;

		void setVertexBuffer(const std::shared_ptr<Buffer>& vertexBuffer) override;
		void setIndexBuffer(const std::shared_ptr<Buffer>& indexBuffer) override;
	};
}
