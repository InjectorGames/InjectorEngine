#pragma once
#include "Injector/Graphics/GpuBufferType.hpp"
#include "Injector/Graphics/GpuBufferAccess.hpp"

#include <cstdlib>

namespace Injector
{
	// Graphics Processing Unit buffer class
	class GpuBuffer
	{
	 protected:
		// Buffer type value
		GpuBufferType type;
		// Buffer size value
		size_t size;
		// Is buffer mappable
		bool mappable;
		// Is buffer mapped
		bool mapped;
		// Buffer map access value
		GpuBufferAccess mapAccess;
		// Buffer map size value
		size_t mapSize;
		// Buffer map offset value
		size_t mapOffset;
	 public:
		// Creates a new GPU buffer
		GpuBuffer(
			GpuBufferType type,
			size_t size,
			bool mappable);
		// Deleted GPU buffer copy constructor
		GpuBuffer(GpuBuffer&& buffer) = delete;
		// Deleted GPU buffer move constructor
		GpuBuffer(const GpuBuffer& buffer) = delete;
		// Destroys GPU buffer
		virtual ~GpuBuffer() = default;

		// Returns buffer type
		GpuBufferType getType() const noexcept;
		// Returns buffer size
		size_t getSize() const noexcept;
		// Returns true if buffer is mappable
		bool isMappable() const noexcept;
		// Returns true if buffer is mapped
		bool isMapped() const noexcept;
		// Returns buffer map access
		GpuBufferAccess getMapAccess() const noexcept;
		// Returns buffer map size
		size_t getMapSize() const noexcept;
		// Returns buffer map offset
		size_t getMapOffset() const noexcept;

		// Returns mapped buffer map
		// with specified access
		virtual void* map(
			GpuBufferAccess access) = 0;
		// Returns mapped buffer map
		// with specified access, size and offset
		virtual void* map(
			GpuBufferAccess access,
			size_t size,
			size_t offset) = 0;
		// Unmaps buffer map
		virtual void unmap() = 0;

		// Sets data to the buffer
		virtual void setData(
			const void* data,
			size_t size) = 0;
		// Sets data to the buffer
		// with specified offset
		virtual void setData(
			const void* data,
			size_t size,
			size_t offset) = 0;
	};
}
