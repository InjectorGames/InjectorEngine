#pragma once
#include <injector/graphics/buffer_type.hpp>
#include <injector/graphics/buffer_usage.hpp>
#include <injector/graphics/buffer_access.hpp>

#include <memory>
#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	class Buffer
	{
	protected:
		size_t size;
		BufferType type;
		BufferUsage usage;
		bool mappable;
		bool mapped;
		BufferAccess mapAccess;
		size_t mapSize;
		size_t mapOffset;
	public:
		Buffer(size_t size,
			BufferType type,
			BufferUsage usage);
		virtual ~Buffer();
		
		size_t getSize() const noexcept;
		BufferType getType() const noexcept;
		BufferUsage getUsage() const noexcept;
		bool isMappable() const noexcept;
		bool isMapped() const noexcept;
		BufferAccess getMapAccess() const noexcept;

		virtual void* map(BufferAccess access);
		virtual void* map(BufferAccess access, size_t size, size_t offset);
		virtual void unmap();

		virtual void setData(const void* data, size_t size);
		virtual void setData(const void* data, size_t size, size_t offset);
	};

	using BufferHandle = std::shared_ptr<Buffer>;
}
