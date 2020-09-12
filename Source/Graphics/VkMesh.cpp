#include "Injector/Graphics/VkMesh.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector
{
	VkMesh::VkMesh(
		size_t indexCount,
		BufferIndex indexType,
		const std::shared_ptr<Buffer>& vertexBuffer,
		const std::shared_ptr<Buffer>& indexBuffer) :
		Mesh(indexCount, indexType, vertexBuffer, indexBuffer)
	{
		if(!std::dynamic_pointer_cast<VkBuffer>(vertexBuffer) ||
			!std::dynamic_pointer_cast<VkBuffer>(indexBuffer))
		{
			throw GraphicsException("Failed to cast Vulkan buffer");
		}	
	}
	VkMesh::~VkMesh()
	{}

	void VkMesh::draw(vk::CommandBuffer commandBuffer) noexcept
	{
		const VkDeviceSize offset = 0;

		auto buffer = std::dynamic_pointer_cast<VkBuffer>(vertexBuffer)->getBuffer();
		commandBuffer.bindVertexBuffers(0, 1, &buffer, &offset);

		auto index = (indexType == BufferIndex::UnsignedShort) ? 
			vk::IndexType::eUint16 : vk::IndexType::eUint32;

		commandBuffer.bindIndexBuffer(
			std::dynamic_pointer_cast<VkBuffer>(indexBuffer)->getBuffer(), 0, index);
		commandBuffer.drawIndexed(static_cast<uint32_t>(indexCount), 1, 0, 0, 0);
	}

	void VkMesh::setVertexBuffer(const std::shared_ptr<Buffer>& _vertexBuffer)
	{
		if(!std::dynamic_pointer_cast<VkBuffer>(_vertexBuffer))
			throw GraphicsException("Failed to cast Vulkan vertex buffer");

		vertexBuffer = std::shared_ptr<Buffer>(_vertexBuffer);
	}
	void VkMesh::setIndexBuffer(const std::shared_ptr<Buffer>& _indexBuffer)
	{
		if(!std::dynamic_pointer_cast<VkBuffer>(_indexBuffer))
			throw GraphicsException("Failed to cast Vulkan index buffer");

		indexBuffer = std::shared_ptr<Buffer>(_indexBuffer);
	}
}
