#include "Injector/Graphics/VkMesh.hpp"
#include "Injector/Exception/CastException.hpp"

namespace Injector
{
	VkMesh::VkMesh(
		size_t indexCount,
		BufferIndex indexType,
		const std::shared_ptr<Buffer>& vertexBuffer,
		const std::shared_ptr<Buffer>& indexBuffer) :
		Mesh(indexCount, indexType, vertexBuffer, indexBuffer)
	{
		if(!std::dynamic_pointer_cast<VkBuffer>(vertexBuffer))
			throw CastException("VkBuffer", "VkBuffer", "vertexBuffer");
		if(!std::dynamic_pointer_cast<VkBuffer>(vertexBuffer))
			throw CastException("VkBuffer", "VkBuffer", "indexBuffer");
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
			throw CastException("VkBuffer", "setVertexBuffer", "vertexBuffer");

		vertexBuffer = std::shared_ptr<Buffer>(_vertexBuffer);
	}
	void VkMesh::setIndexBuffer(const std::shared_ptr<Buffer>& _indexBuffer)
	{
		if(!std::dynamic_pointer_cast<VkBuffer>(_indexBuffer))
			throw CastException("VkBuffer", "setIndexBuffer", "indexBuffer");

		indexBuffer = std::shared_ptr<Buffer>(_indexBuffer);
	}
}
