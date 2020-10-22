#include "Injector/Graphics/Vulkan/VkGpuMesh.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	VkGpuMesh::VkGpuMesh(
		size_t indexCount,
		const std::shared_ptr<VkGpuBuffer>& _vertexBuffer,
		const std::shared_ptr<VkGpuBuffer>& _indexBuffer) :
		GpuMesh(indexCount),
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer)
	{
		if(_vertexBuffer && _vertexBuffer->getType() != GpuBufferType::Vertex)
		{
			throw Exception(
				"VkGpuMesh",
				"VkGpuMesh",
				"Buffer has not vertex type");
		}
		if(_indexBuffer && _indexBuffer->getType() != GpuBufferType::Index)
		{
			throw Exception(
				"VkGpuMesh",
				"VkGpuMesh",
				"Buffer has not index type");
		}
	}

	std::shared_ptr<GpuBuffer> VkGpuMesh::getVertexBuffer() const
	{
		return vertexBuffer;
	}
	void VkGpuMesh::setVertexBuffer(const std::shared_ptr<GpuBuffer>& buffer)
	{
		if(buffer && buffer->getType() != GpuBufferType::Vertex)
		{
			throw Exception(
				"VkGpuMesh",
				"setVertexBuffer",
				"Buffer has not vertex type");
		}

		vertexBuffer = std::dynamic_pointer_cast<VkGpuBuffer>(buffer);
	}

	std::shared_ptr<GpuBuffer> VkGpuMesh::getIndexBuffer() const
	{
		return indexBuffer;
	}
	void VkGpuMesh::setIndexBuffer(const std::shared_ptr<GpuBuffer>& buffer)
	{
		if(buffer && buffer->getType() != GpuBufferType::Index)
		{
			throw Exception(
				"VkGpuMesh",
				"setIndexBuffer",
				"Buffer has not index type");
		}

		indexBuffer = std::dynamic_pointer_cast<VkGpuBuffer>(buffer);
	}

	void VkGpuMesh::draw(vk::CommandBuffer commandBuffer)
	{
		if(!commandBuffer)
		{
			throw NullException(
				"VkGpuMesh",
				"draw",
				"commandBuffer");
		}

		if (!vertexBuffer || !indexBuffer)
			return;

		const VkDeviceSize offset = 0;
		auto buffer = vertexBuffer->getBuffer();

		commandBuffer.bindVertexBuffers(
			0,
			1,
			&buffer,
			&offset);

		commandBuffer.bindIndexBuffer(
			indexBuffer->getBuffer(),
			0,
			vk::IndexType::eUint32);

		commandBuffer.drawIndexed(
			static_cast<uint32_t>(indexCount),
			1,
			0,
			0,
			0);
	}
}
