#include "Injector/Graphics/GpuBuffer.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	GpuBuffer::GpuBuffer(
		GpuBufferType _type,
		size_t _size,
		bool _mappable) :
		type(_type),
		size(_size),
		mappable(_mappable),
		mapped(false),
		mapAccess(),
		mapSize(),
		mapOffset()
	{
	}
	GpuBuffer::~GpuBuffer()
	{
	}

	GpuBufferType GpuBuffer::getType() const noexcept
	{
		return type;
	}
	size_t GpuBuffer::getSize() const noexcept
	{
		return size;
	}
	bool GpuBuffer::isMappable() const noexcept
	{
		return mappable;
	}
	bool GpuBuffer::isMapped() const noexcept
	{
		return mapped;
	}
	GpuBufferAccess GpuBuffer::getMapAccess() const noexcept
	{
		return mapAccess;
	}
	size_t GpuBuffer::getMapSize() const noexcept
	{
		return mapSize;
	}
	size_t GpuBuffer::getMapOffset() const noexcept
	{
		return mapOffset;
	}

	void* GpuBuffer::map(GpuBufferAccess access)
	{
		if (!mappable)
		{
			throw Exception(
				"GpuBuffer",
				"map",
				"Not mappable");
		}
		if (mapped)
		{
			throw Exception(
				"GpuBuffer",
				"map",
				"Already mapped");
		}

		mapped = true;
		mapAccess = access;
		mapSize = size;
		mapOffset = 0;
		return nullptr;
	}
	void* GpuBuffer::map(GpuBufferAccess access, size_t _size, size_t offset)
	{
		if (!mappable)
		{
			throw Exception(
				"GpuBuffer",
				"map",
				"Not mappable");
		}
		if (mapped)
		{
			throw Exception(
				"GpuBuffer",
				"map",
				"Already mapped");
		}
		if (_size + offset > size)
		{
			throw OutOfRangeException(
				"GpuBuffer",
				"map",
				_size + offset,
				size);
		}

		mapped = true;
		mapAccess = access;
		mapSize = _size;
		mapOffset = offset;
		return nullptr;
	}
	void GpuBuffer::unmap()
	{
		if (!mapped)
		{
			throw Exception(
				"GpuBuffer",
				"map",
				"Not mapped");
		}

		mapped = false;
	}

	void GpuBuffer::setData(const void* data, size_t size)
	{
		throw NotImplementedException(
			"GpuBuffer",
			"setData");
	}
	void GpuBuffer::setData(const void* data, size_t size, size_t offset)
	{
		throw NotImplementedException(
			"GpuBuffer",
			"setData");
	}
}
