#include "Injector/Graphics/VkGpuMesh.hpp"
#include "Injector/Exception/CastException.hpp"

namespace Injector
{
	VkGpuMesh::VkGpuMesh(
		size_t indexCount,
		GpuBufferIndex indexType,
		const std::shared_ptr<GpuBuffer>& vertexBuffer,
		const std::shared_ptr<GpuBuffer>& indexBuffer) :
		GpuMesh(indexCount, indexType, vertexBuffer, indexBuffer)
	{
	}
	VkGpuMesh::~VkGpuMesh()
	{
	}

	void VkGpuMesh::draw(vk::CommandBuffer commandBuffer)
	{
		const VkDeviceSize offset = 0;

		auto vkVertexBuffer = std::dynamic_pointer_cast<VkGpuBuffer>(vertexBuffer);
		auto vkIndexBuffer = std::dynamic_pointer_cast<VkGpuBuffer>(vertexBuffer);

		if (!vkVertexBuffer || !vkIndexBuffer)
		{
			throw CastException(
				"VkGpuMesh",
				"VkGpuMesh",
				"buffer");
		}

		auto buffer = vkVertexBuffer->getBuffer();

		commandBuffer.bindVertexBuffers(
			0,
			1,
			&buffer,
			&offset);

		auto index = (indexType == GpuBufferIndex::UnsignedShort) ?
			vk::IndexType::eUint16 : vk::IndexType::eUint32;

		commandBuffer.bindIndexBuffer(
			vkIndexBuffer->getBuffer(),
			0,
			index);

		commandBuffer.drawIndexed(
			static_cast<uint32_t>(indexCount),
			1,
			0,
			0,
			0);
	}
}
