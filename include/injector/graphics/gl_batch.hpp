#pragma once
#include <injector/defines.hpp>

#include <memory>
#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	class GlBatch
	{
	protected:
		uint32_t instance;

		static uint32_t create() noexcept;
		static void destroy(uint32_t vertexArray) noexcept;
		static void bind(uint32_t vertexArray) noexcept;
	public:
		GlBatch();
		virtual ~GlBatch();

		uint32_t getInstance() const noexcept;

		void bind() noexcept;
		void unbind() noexcept;
	};

	using GlBatchHandle = std::shared_ptr<GlBatch>;
}
