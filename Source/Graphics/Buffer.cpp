#include "Injector/Graphics/Buffer.hpp"
#include "Injector/Graphics/GraphicsException.hpp"

namespace Injector
{
    Buffer::Buffer(
        BufferType _type,
        size_t _size,
        bool _mappable) :
        type(_type),
        size(_size),
        mappable(_mappable),
        mapped(false),
        mapAccess(),
        mapSize(),
        mapOffset()
    {}
    Buffer::~Buffer()
    {}

    BufferType Buffer::getType() const noexcept
	{
		return type;
	}
    size_t Buffer::getSize() const noexcept
	{
		return size;
	}
    bool Buffer::isMappable() const noexcept
	{
		return mappable;
	}
	bool Buffer::isMapped() const noexcept
	{
		return mapped;
	}
	BufferAccess Buffer::getMapAccess() const noexcept
	{
		return mapAccess;
	}
	size_t Buffer::getMapSize() const noexcept
	{
		return mapSize;
	}
	size_t Buffer::getMapOffset() const noexcept
	{
		return mapOffset;
	}

    void* Buffer::map(BufferAccess access)
    {
        if (!mappable)
			throw GraphicsException("Failed to map buffer, not mappable");
		if (mapped)
			throw GraphicsException("Failed to map buffer, already mapped");

        mapped = true;
		mapAccess = access;
		mapSize = size;
		mapOffset = 0;
    }
	void* Buffer::map(BufferAccess access, size_t _size, size_t offset)
    {
        if (!mappable)
			throw GraphicsException("Failed to map buffer, not mappable");
		if (mapped)
			throw GraphicsException("Failed to map buffer, already mapped");
		if (_size + offset > size)
			throw GraphicsException("Failed to map buffer, out of range");

        mapped = true;
		mapAccess = access;
		mapSize = _size;
		mapOffset = offset;
    }
	void Buffer::unmap()
    {
        if (!mapped)
			throw GraphicsException("Failed to unmap buffer, not mapped");

        mapped = false;
    }

	void Buffer::setData(const void* data, size_t size)
    {
        throw GraphicsException("Not implemented buffer function");
    }
	void Buffer::setData(const void* data, size_t size, size_t offset)
    {
        throw GraphicsException("Not implemented buffer function");
    }
}
