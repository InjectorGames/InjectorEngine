#pragma once
#include "Injector/Graphics/GpuBufferType.hpp"
#include "Injector/Graphics/GpuBufferAccess.hpp"

#include <cstdlib>

namespace Injector
{
	class GpuBuffer
	{
	 protected:
		GpuBufferType type;
		size_t size;
		bool mappable;
		bool mapped;
		GpuBufferAccess mapAccess;
		size_t mapSize;
		size_t mapOffset;
	 public:
		GpuBuffer(
			GpuBufferType type,
			size_t size,
			bool mappable);
		GpuBuffer(GpuBuffer&& buffer) = delete;
		GpuBuffer(const GpuBuffer& buffer) = delete;
		virtual ~GpuBuffer() = default;

		GpuBufferType getType() const noexcept;
		size_t getSize() const noexcept;
		bool isMappable() const noexcept;
		bool isMapped() const noexcept;
		GpuBufferAccess getMapAccess() const noexcept;
		size_t getMapSize() const noexcept;
		size_t getMapOffset() const noexcept;

		virtual void* map(
			GpuBufferAccess access) = 0;
		virtual void* map(
			GpuBufferAccess access,
			size_t size,
			size_t offset) = 0;
		virtual void unmap() = 0;

		virtual void setData(
			const void* data,
			size_t size) = 0;
		virtual void setData(
			const void* data,
			size_t size,
			size_t offset) = 0;
	};
}
