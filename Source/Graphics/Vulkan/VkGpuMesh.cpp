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
				std::string(typeid(VkGpuMesh).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer type is not vertex");
		}
		if(_indexBuffer && _indexBuffer->getType() != GpuBufferType::Index)
		{
			throw Exception(
				std::string(typeid(VkGpuMesh).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer type is not index");
		}
	}

	std::shared_ptr<GpuBuffer> VkGpuMesh::getVertexBuffer() const
	{
		return vertexBuffer;
	}
	void VkGpuMesh::setVertexBuffer(
		const std::shared_ptr<GpuBuffer>& buffer)
	{
		if(buffer && buffer->getType() != GpuBufferType::Vertex)
		{
			throw Exception(
				std::string(typeid(VkGpuMesh).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer type is not vertex");
		}

		vertexBuffer = std::dynamic_pointer_cast<VkGpuBuffer>(buffer);
	}

	std::shared_ptr<GpuBuffer> VkGpuMesh::getIndexBuffer() const
	{
		return indexBuffer;
	}
	void VkGpuMesh::setIndexBuffer(
		const std::shared_ptr<GpuBuffer>& buffer)
	{
		if(buffer && buffer->getType() != GpuBufferType::Index)
		{
			throw Exception(
				std::string(typeid(VkGpuMesh).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Buffer type is not index");
		}

		indexBuffer = std::dynamic_pointer_cast<VkGpuBuffer>(buffer);
	}

	void VkGpuMesh::draw(vk::CommandBuffer commandBuffer)
	{
		if(!commandBuffer)
		{
			throw NullException(
				std::string(typeid(VkGpuMesh).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
