#pragma once
#include "Injector/Graphics/BufferType.hpp"
#include "Injector/Graphics/BufferAccess.hpp"
#include <cstdlib>

namespace Injector
{
    class Buffer
    {
    protected:
        BufferType type;
        size_t size;
        bool mappable;
		bool mapped;
		BufferAccess mapAccess;
		size_t mapSize;
		size_t mapOffset;
    public:
        Buffer(BufferType type,
            size_t size,
            bool mappable);
        virtual ~Buffer();

        BufferType getType() const noexcept;
        size_t getSize() const noexcept;
        bool isMappable() const noexcept;
		bool isMapped() const noexcept;
		BufferAccess getMapAccess() const noexcept;
		size_t getMapSize() const noexcept;
		size_t getMapOffset() const noexcept;

        virtual void* map(BufferAccess access);
		virtual void* map(BufferAccess access, size_t size, size_t offset);
		virtual void unmap();

		virtual void setData(const void* data, size_t size);
		virtual void setData(const void* data, size_t size, size_t offset);
    };
}
