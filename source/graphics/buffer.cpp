#include <injector/graphics/buffer.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Buffer::Buffer(size_t _size) :
		size(_size),
		mapped(false),
		mapAccess(),
		mapSize(),
		mapOffset()
	{}
	Buffer::~Buffer()
	{}

	size_t Buffer::getSize() const noexcept
	{
		return size;
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
		if (mapped)
			throw std::runtime_error("Failed to map buffer, already mapped");

		mapAccess = access;
		mapSize = size;
		mapOffset = 0;
		mapped = true;
	}
	void* Buffer::map(BufferAccess access, size_t _size, size_t offset)
	{
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
