#include "Injector/Graphics/GpuBuffer.hpp"
#include "Injector/Exception/Exception.hpp"

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
		if(_size == 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Size has zero value");
		}
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
}
