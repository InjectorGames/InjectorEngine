#include "Injector/Graphics/VkMesh.hpp"

namespace Injector::Graphics
{
	VkMesh::VkMesh(
		size_t indexCount,
		BufferIndex indexType,
		const shared_ptr<VkBuffer>& _vertexBuffer,
		const shared_ptr<VkBuffer>& _indexBuffer) :
		Mesh(indexCount, indexType),
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer)
	{}
	VkMesh::~VkMesh()
	{}

	const shared_ptr<VkBuffer>& VkMesh::getVertexBuffer() const noexcept
	{
		return vertexBuffer;
	}
	const shared_ptr<VkBuffer>& VkMesh::getIndexBuffer() const noexcept
	{
		return indexBuffer;
	}

	void VkMesh::draw(vk::CommandBuffer commandBuffer) noexcept
	{
		const VkDeviceSize offset = 0;
		auto buffer = vertexBuffer->getBuffer();
		commandBuffer.bindVertexBuffers(0, 1, &buffer, &offset);

		auto index = (indexType == BufferIndex::UnsignedShort) ? 
			vk::IndexType::eUint16 : vk::IndexType::eUint32;

		commandBuffer.bindIndexBuffer(indexBuffer->getBuffer(), 0, index);
		commandBuffer.drawIndexed(static_cast<uint32_t>(indexCount), 1, 0, 0, 0);
	}

	void VkMesh::setVertexData(void* data, size_t size)
	{
		vertexBuffer->setData(data, size);
	}
	void VkMesh::setVertexData(void* data, size_t size, size_t offset)
	{
		vertexBuffer->setData(data, size, offset);
	}

	void VkMesh::setIndexData(void* data, size_t size)
	{
		indexBuffer->setData(data, size);
	}
	void VkMesh::setIndexData(void* data, size_t size, size_t offset)
	{
		indexBuffer->setData(data, size, offset);
	}
}
