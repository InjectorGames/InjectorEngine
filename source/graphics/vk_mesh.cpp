#include <injector/graphics/vk_mesh.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkMesh::VkMesh(
		size_t indexCount,
		MeshIndex indexType,
		const VkBufferHandle& vertexBuffer,
		const VkBufferHandle& indexBuffer) :
		Mesh(indexCount, indexType, vertexBuffer, indexBuffer)
	{
		vkIndexType = toVkIndexType(indexType);
		vkVertexBuffer = vertexBuffer->getBuffer();
		vkIndexBuffer = indexBuffer->getBuffer();
	}
	VkMesh::~VkMesh()
	{}

	vk::IndexType VkMesh::getVkIndexType() const noexcept
	{
		return vkIndexType;
	}
	vk::Buffer VkMesh::getVkVertexBuffer() const noexcept
	{
		return vkVertexBuffer;
	}
	vk::Buffer VkMesh::getVkIndexBuffer() const noexcept
	{
		return vkIndexBuffer;
	}

	void VkMesh::draw(vk::CommandBuffer commandBuffer) noexcept
	{
		VkDeviceSize offset = 0;
		commandBuffer.bindVertexBuffers(0, 1, &vkVertexBuffer, &offset);
		commandBuffer.bindIndexBuffer(vkIndexBuffer, 0, vkIndexType);
		commandBuffer.drawIndexed(static_cast<uint32_t>(indexCount), 1, 0, 0, 0);
	}

	vk::IndexType VkMesh::toVkIndexType(MeshIndex indexType)
	{
		if (indexType == MeshIndex::UnsignedShort)
			return vk::IndexType::eUint16;
		else if (indexType == MeshIndex::UnsignedInt)
			return vk::IndexType::eUint32;
		else
			throw std::runtime_error("Unsupported Vulkan mesh index type");
	}
	MeshIndex VkMesh::toIndexType(vk::IndexType indexType)
	{
		if (indexType == vk::IndexType::eUint16)
			return MeshIndex::UnsignedShort;
		else if (indexType == vk::IndexType::eUint32)
			return MeshIndex::UnsignedInt;
		else
			throw std::runtime_error("Unsupported Vulkan mesh index type");
	}
}
