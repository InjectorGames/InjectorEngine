#pragma once
#include <injector/defines.hpp>

#include <vector>
#include <memory>
#include <cstdint>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace INJECTOR_NAMESPACE
{
	class GlBuffer
	{
	public:
		enum class Type : GLenum
		{
			Array = GL_ARRAY_BUFFER, // GL 2.0
			AtomicCounter = GL_ATOMIC_COUNTER_BUFFER, // GL 4.3
			CopyRead = GL_COPY_READ_BUFFER, // GL 3.1
			CopyWrite = GL_COPY_WRITE_BUFFER, // GL 2.0
			DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER, // GL 4.3
			DrawIndirect = GL_DRAW_INDIRECT_BUFFER, // GL 2.0
			ElementArray = GL_ELEMENT_ARRAY_BUFFER, // GL 2.0
			PixelPack = GL_PIXEL_PACK_BUFFER, // GL 2.0
			PixelUnpack = GL_PIXEL_UNPACK_BUFFER, // GL 2.0
			Query = GL_QUERY_BUFFER, // GL 4.4
			ShaderStorage = GL_SHADER_STORAGE_BUFFER, // GL 4.3
			Texture = GL_TEXTURE_BUFFER, // GL 3.1
			TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER, // GL 2.0
			Uniform = GL_UNIFORM_BUFFER, // GL 3.1
		};
		enum class Usage : GLenum
		{
			// STREAM: The data store contents will be modified once and used at most a few times.
			// STATIC: The data store contents will be modified once and used many times.
			// DYNAMIC: The data store contents will be modified repeatedly and used many times.
			// DRAW: The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
			// READ: The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
			// COPY: The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.

			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY,
		};
	protected:
		uint32_t instance;
		size_t size;
		Type type;
		Usage usage;

		static uint32_t create() noexcept;
		static void destroy(uint32_t buffer) noexcept;
		static void bind(Type type, uint32_t buffer) noexcept;

		static void setData(Type type, Usage usage,
			const void* data, size_t size) noexcept;
		static void setSubData(Type type,
			const void* data, size_t size, size_t offset) noexcept;
	public:
		GlBuffer(Type type, Usage usage);
		virtual ~GlBuffer();

		uint32_t getInstance() const noexcept;
		size_t getSize() const noexcept;
		Type getType() const noexcept;
		Usage getUsage() const noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		template<class TData>
		void setData(const std::vector<TData>& data) noexcept
		{
			size = data.size() * sizeof(TData);
			setData(type, usage, data.data(), size);
		}
		template<class TData>
		void setData(Usage _usage, const std::vector<TData>& data) noexcept
		{
			usage = _usage;
			size = data.size() * sizeof(TData);
			setData(type, _usage, data.data(), size);
		}

		template<class TData>
		void setSubData(const std::vector<TData>& data, uint64_t offset) noexcept
		{
			auto size = data.size() * sizeof(TData);
			setSubData(type, data.data(), size, offset);
		}
	};

	using GlBufferHandle = std::shared_ptr<GlBuffer>;
}