#include <injector/graphics/buffer.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Buffer::Buffer(
		size_t _size,
		BufferType _type,
		BufferUsage _usage) :
		size(_size),
		type(_type),
		usage(_usage),
		mapped(false),
		mapAccess(),
		mapSize(),
		mapOffset()
	{
		if (usage == BufferUsage::CpuOnly ||
			usage == BufferUsage::CpuToGpu ||
			usage == BufferUsage::GpuToCpu)
			mappable = true;
		else
			mappable = false;
	}
	Buffer::~Buffer()
	{}

	size_t Buffer::getSize() const noexcept
	{
		return size;
	}
	BufferType Buffer::getType() const noexcept
	{
		return type;
	}
	BufferUsage Buffer::getUsage() const noexcept
	{
		return usage;
	}
	bool Buffer::isMapped() const noexcept
	{
		return mapped;
	}
	BufferAccess Buffer::getMapAccess() const noexcept
	{
		return mapAccess;
	}

	void* Buffer::map(BufferAccess access)
	{
		if (!mappable)
			throw std::runtime_error("Failed to map buffer, not mappeble");
		if (mapped)
			throw std::runtime_error("Failed to map buffer, already mapped");

		mapAccess = access;
		mapSize = size;
		mapOffset = 0;
		mapped = true;
	}
	void* Buffer::map(BufferAccess access, size_t _size, size_t offset)
	{
		if (!mappable)
			throw std::runtime_error("Failed to map buffer, not mappeble");
		if (mapped)
			throw std::runtime_error("Failed to map buffer, already mapped");
		if (_size + offset > size)
			throw std::runtime_error("Failed to map buffer, out of range");

		mapAccess = access;
		mapSize = _size;
		mapOffset = offset;
		mapped = true;
	}
	void Buffer::unmap()
	{
		if (!mapped)
			throw std::runtime_error("Failed to unmap buffer, not mapped");

		mapped = false;
	}

	void Buffer::setData(const void* data, size_t size)
	{
		throw std::runtime_error("Not implemented buffer function");
	}
	void Buffer::setData(const void* data, size_t size, size_t offset)
	{
		throw std::runtime_error("Not implemented buffer function");
	}
}
