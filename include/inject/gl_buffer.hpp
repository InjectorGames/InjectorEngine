#pragma once
#include <GL/glew.h>
#include <SDL_opengl.h>

#include <vector>

namespace inject
{
	class GlBuffer
	{
	public:
		enum class Type
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

		enum class Usage
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
		uint32_t buffer;
		uint64_t size;
		Type type;
		Usage usage;

		inline static uint32_t create() noexcept
		{
			GLuint buffer;
			glGenBuffers(GL_ONE, &buffer);
			return static_cast<uint32_t>(buffer);
		}
		inline static void destroy(const uint32_t buffer) noexcept
		{
			glDeleteBuffers(GL_ONE, static_cast<const GLuint*>(&buffer));
		}
		inline static void bind(const Type type, const uint32_t buffer) noexcept
		{
			glBindBuffer(static_cast<GLenum>(type), static_cast<GLuint>(buffer));
		}

		template<class TData>
		inline static void setData(const Type type, const std::vector<TData>& data, Usage usage) noexcept
		{
			glBufferData(static_cast<GLenum>(type),
				static_cast<GLsizeiptr>(data.size() * sizeof(TData)),
				static_cast<const GLvoid*>(data.data()),
				static_cast<GLenum>(usage));
		}

		template<class TData>
		inline static void setSubData(const Type type, const uint64_t offset, const std::vector<TData>& data)
		{
			// TODO: add range check

			glBufferSubData(static_cast<GLenum>(type),
				static_cast<GLintptr>(offset),
				static_cast<GLsizeiptr>(data.size() * sizeof(TData)),
				static_cast<const GLvoid*>(data.data()));
		}
	public:
		GlBuffer(const Type _type, const Usage _usage) :
			size(0),
			type(_type),
			usage(_usage)
		{
			buffer = create();
		}
		virtual ~GlBuffer()
		{
			destroy(buffer);
		}

		inline uint32_t getBuffer() const noexcept
		{
			return buffer;
		}
		inline uint64_t getSize() const noexcept
		{
			return size;
		}
		inline Type getType() const noexcept
		{
			return type;
		}
		inline Usage getUsage() const noexcept
		{
			return usage;
		}

		inline void bind() const noexcept
		{
			bind(type, buffer);
		}
		inline void unbind() const noexcept
		{
			bind(type, 0);
		}

		template<class TData>
		inline void setData(const std::vector<TData>& data) noexcept
		{
			size = data.size() * sizeof(TData);
			setData(type, data, usage);
		}
		template<class TData>
		inline void setData(const std::vector<TData>& data, Usage _usage) noexcept
		{
			size = data.size() * sizeof(TData);
			usage = _usage;
			setData(type, data, _usage);
		}

		template<class TData>
		inline void setSubData(const uint64_t offset, const std::vector<TData>& data) const
		{
			setSubData<TData>(type, offset, data);
		}
	};
}