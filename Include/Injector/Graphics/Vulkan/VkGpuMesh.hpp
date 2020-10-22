#pragma once
#include "Injector/Graphics/GpuMesh.hpp"
#include "Injector/Graphics/Vulkan/VkGpuBuffer.hpp"

#include <memory>

namespace Injector
{
	class VkGpuMesh : public GpuMesh
	{
	 protected:
		std::shared_ptr<VkGpuBuffer> vertexBuffer;
		std::shared_ptr<VkGpuBuffer> indexBuffer;
	 public:
		VkGpuMesh(
			size_t indexCount,
			const std::shared_ptr<VkGpuBuffer>& vertexBuffer,
			const std::shared_ptr<VkGpuBuffer>& indexBuffer);

		std::shared_ptr<GpuBuffer> getVertexBuffer() const override;
		void setVertexBuffer(const std::shared_ptr<GpuBuffer>& buffer) override;

		std::shared_ptr<GpuBuffer> getIndexBuffer() const override;
		void setIndexBuffer(const std::shared_ptr<GpuBuffer>& buffer) override;

		void draw(vk::CommandBuffer commandBuffer);
	};
}
