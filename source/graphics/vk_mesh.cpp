#include <injector/graphics/vk_mesh.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkMesh::VkMesh(
		size_t indexCount,
		MeshIndex indexType,
		const BufferHandle& vertexBuffer,
		const BufferHandle& indexBuffer) :
		Mesh(indexCount, indexType, vertexBuffer, indexBuffer)
	{
		vkIndexType = toVkIndexType(indexType);
		vkVertexBuffer = std::dynamic_pointer_cast<VkBuffer>(vertexBuffer)->getBuffer();
		vkIndexBuffer = std::dynamic_pointer_cast<VkBuffer>(indexBuffer)->getBuffer();
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
		if (indexType == MeshIndex::Ushort)
			return vk::IndexType::eUint16;
		else if (indexType == MeshIndex::Uint)
			return vk::IndexType::eUint32;
		else
			throw std::runtime_error("Unsupported Vulkan mesh index type");
	}
	MeshIndex VkMesh::toIndexType(vk::IndexType indexType)
	{
		if (indexType == vk::IndexType::eUint16)
			return MeshIndex::Ushort;
		else if (indexType == vk::IndexType::eUint32)
			return MeshIndex::Uint;
		else
			throw std::runtime_error("Unsupported Vulkan mesh index type");
	}
}
