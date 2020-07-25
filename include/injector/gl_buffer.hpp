#pragma once
#include <injector/defines.hpp>

#include <vector>
#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	class GlBuffer
	{
	protected:
		uint32_t instance;
		size_t size;
		uint32_t type;
		uint32_t usage;

		static uint32_t create() noexcept;
		static void destroy(uint32_t buffer) noexcept;
		static void bind(uint32_t type, uint32_t buffer) noexcept;

		static void setData(uint32_t type, uint32_t usage,
			const void* data, size_t size) noexcept;
		static void setSubData(uint32_t type,
			const void* data, size_t size, size_t offset) noexcept;
	public:
		GlBuffer(uint32_t _type, uint32_t _usage);
		virtual ~GlBuffer();

		uint32_t getInstance() const noexcept;
		uint64_t getSize() const noexcept;
		uint32_t getType() const noexcept;
		uint32_t getUsage() const noexcept;

		void bind() const noexcept;
		void unbind() const noexcept;

		template<class TData>
		void setData(const std::vector<TData>& data) noexcept
		{
			size = data.size() * sizeof(TData);
			setData(type, usage, data.data(), size);
		}
		template<class TData>
		void setData(const std::vector<TData>& data, uint32_t _usage) noexcept
		{
			size = data.size() * sizeof(TData);
			usage = _usage;
			setData(type, _usage, data.data(), size);
		}

		template<class TData>
		void setSubData(uint64_t offset, const std::vector<TData>& data) const
		{
			auto size = data.size() * sizeof(TData);
			setSubData(type, data.data(), size, offset);
		}
	};
}