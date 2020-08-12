#include <injector/graphics/vk_mesh.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkMesh::VkMesh(vk::IndexType _index,
		size_t indexCount,
		const VkBufferHandle& _vertexBuffer,
		const VkBufferHandle& _indexBuffer) :
		Mesh(indexCount),
		index(_index),
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer)
	{}
	VkMesh::~VkMesh()
	{}

	MeshIndex VkMesh::getIndex() const
	{
		return toIndex(index);
	}
	void VkMesh::setIndex(MeshIndex _index)
	{
		index = toVkIndex(_index);
	}

	const BufferHandle& VkMesh::getVertexBuffer() const
	{
		return vertexBuffer;
	}
	const BufferHandle& VkMesh::getIndexBuffer() const
	{
		return indexBuffer;
	}

	void VkMesh::draw(vk::CommandBuffer commandBuffer)
	{
		VkDeviceSize offset = 0;
		commandBuffer.bindVertexBuffers(0, 1, &vertexBuffer->getBuffer(), &offset);
		commandBuffer.bindIndexBuffer(indexBuffer->getBuffer(), 0, index);
		commandBuffer.drawIndexed(indexCount, 1, 0, 0, 0);
	}

	vk::IndexType VkMesh::toVkIndex(MeshIndex index)
	{
		if (index == MeshIndex::Ushort)
			return vk::IndexType::eUint16;
		else if (index == MeshIndex::Uint)
			return vk::IndexType::eUint32;
		else
			throw std::runtime_error("Unsupported Vulkan mesh index type");
	}
	MeshIndex VkMesh::toIndex(vk::IndexType index)
	{
		if (index == vk::IndexType::eUint16)
			return MeshIndex::Ushort;
		else if (index == vk::IndexType::eUint32)
			return MeshIndex::Uint;
		else
			throw std::runtime_error("Unsupported Vulkan mesh index type");
	}
}
