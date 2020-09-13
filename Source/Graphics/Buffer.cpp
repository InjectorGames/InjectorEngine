#include "Injector/Graphics/Buffer.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

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
			throw Exception("Buffer", "map", "Not mappable");
		if (mapped)
			throw Exception("Buffer", "map", "Already mapped");

        mapped = true;
		mapAccess = access;
		mapSize = size;
		mapOffset = 0;
    }
	void* Buffer::map(BufferAccess access, size_t _size, size_t offset)
    {
        if (!mappable)
			throw Exception("Buffer", "map", "Not mappable");
		if (mapped)
			throw Exception("Buffer", "map", "Already mapped");
		if (_size + offset > size)
			throw OutOfRangeException("Buffer", "map", _size + offset, size);

        mapped = true;
		mapAccess = access;
		mapSize = _size;
		mapOffset = offset;
    }
	void Buffer::unmap()
    {
        if (!mapped)
			throw Exception("Buffer", "map", "Not mapped");

        mapped = false;
    }

	void Buffer::setData(const void* data, size_t size)
    {
        throw NotImplementedException("Buffer", "setData");
    }
	void Buffer::setData(const void* data, size_t size, size_t offset)
    {
        throw NotImplementedException("Buffer", "setData");
    }
}
