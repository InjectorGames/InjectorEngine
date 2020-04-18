#pragma once
#include <injector_engine/engine.hpp>

namespace InjectorEngine
{
	enum class GlBufferType
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
	
	enum class GlBufferUsage
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

	enum class GlAttributeType
	{
		Byte = GL_BYTE,
		UnsignedByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UnsignedShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
		HalfFloat = GL_HALF_FLOAT,
		Float = GL_FLOAT,
		Double = GL_DOUBLE,
		Fixed = GL_FIXED,
		Int_2_10_10_10_Rev = GL_INT_2_10_10_10_REV,
		UnsignedInt_2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
		UnsignedInt_10f_11f_11f_Rev = GL_UNSIGNED_INT_10F_11F_11F_REV, // GL 4.4
	};
	enum class GlAttributeSize
	{
		One = 1,
		Two = 2,
		Three = 3,
		Four = 4,
	};

	enum class GlDrawMode
	{
		Points = GL_POINTS,
		LineStrip = GL_LINE_STRIP,
		LineLoop = GL_LINE_LOOP,
		Lines = GL_LINES,
		LineStripAdjacency = GL_LINE_STRIP_ADJACENCY, // GL 3.2
		LinesAdjacency = GL_LINES_ADJACENCY, // GL 3.2
		TriangleStrip = GL_TRIANGLE_STRIP,
		TriangleFan = GL_TRIANGLE_FAN,
		Triangles = GL_TRIANGLES,
		TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY, // GL 3.2
		TrianglesAdjacency = GL_TRIANGLES_ADJACENCY, // GL 3.2
		Patches = GL_PATCHES,
	};

	enum class GlDrawType
	{
		UnsignedByte = GL_UNSIGNED_BYTE,
		UnsignedShort = GL_UNSIGNED_SHORT,
		UnsignedInt = GL_UNSIGNED_INT,
	};

	class GlPrimitive
	{
	public:
		inline static const std::vector<float_t> SquareVertices =
		{
			-0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
		};
		inline static const std::vector<float_t> SquareNormals =
		{
			0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
		};
		inline static const std::vector<float_t> SquareTexCoords =
		{
			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		};
		inline static const std::vector<uint8_t> SquareIndices =
		{
			0, 1, 2, 0, 2, 3,
		};

		inline static const std::vector<float_t> CubeVertices =
		{
			-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
		};
		inline static const std::vector<float_t> CubeNormals =
		{
			-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		};
		inline static const std::vector<uint8_t> CubeIndices =
		{
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,
			8, 9, 10, 8, 10, 11,
			12, 13, 14, 12, 14, 15,
			16, 17, 18, 16, 18, 19,
			20, 21, 22, 20, 22, 23,
		};
	};

	class GlWindow : public Window
	{
	protected:
		bool isES;

		inline static void SetViewport(glm::ivec2 offset, glm::ivec2 size)
		{
			glViewport(static_cast<GLdouble>(offset.x), static_cast<GLdouble>(offset.y), static_cast<GLdouble>(size.x), static_cast<GLdouble>(size.y));
		}
	public:
		GlWindow(bool _isES = false, std::string title = "Injector Engine - Editor", glm::ivec2 size = glm::ivec2(800, 600), GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr) :
			Window(title + (_isES ? " (OpenGL ES)" : " (OpenGL)"), size)
		{
			if (_isES)
			{
				window = nullptr;
			}
			else
			{
				glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

				window = glfwCreateWindow(size.x, size.y, title.c_str(), monitor, share);
			}

			if (!window)
			{
				glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

				window = glfwCreateWindow(size.x, size.y, title.c_str(), monitor, share);

				if (!window)
					throw std::runtime_error("Failed to create OpenGL/ES window.");

				_isES = true;
			}

			isES = _isES;

			glfwMakeContextCurrent(window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
				throw std::runtime_error("Failed to load OpenGL/ES loader.");
		}

		inline bool IsES() const
		{
			return isES;
		}

		void OnUpdate(double deltaTime) override
		{
			glfwMakeContextCurrent(window);
			Window::OnUpdate(deltaTime);
			glfwSwapBuffers(window);
		}
		void OnFramebufferResize(glm::ivec2 size) override
		{
			SetViewport(glm::ivec2(0), size);
		}
	};

	class GlShader : public Shader
	{
	protected:
		inline static uint32_t TypeToEnum(ShaderType type)
		{
			switch (type)
			{
			default:
				throw std::runtime_error("Unsupported OpenGL shader type.");
			case ShaderType::Vertex:
				return GL_VERTEX_SHADER;
			case ShaderType::TessellationControl:
				return GL_TESS_CONTROL_SHADER;
			case ShaderType::TessellationEvaluation:
				return GL_TESS_EVALUATION_SHADER;
			case ShaderType::Geometry:
				return GL_GEOMETRY_SHADER;
			case ShaderType::Fragment:
				return GL_FRAGMENT_SHADER;
			case ShaderType::Compute:
				return GL_COMPUTE_SHADER;
			}
		}

		inline static uint32_t Create(ShaderType type)
		{
			return static_cast<uint32_t>(glCreateShader(static_cast<GLenum>(TypeToEnum(type))));
		}
		inline static void Delete(uint32_t shader)
		{
			glDeleteShader(static_cast<GLuint>(shader));
		}

		inline static void SetSource(uint32_t shader, const char* source)
		{
			glShaderSource(static_cast<GLuint>(shader), GL_ONE, static_cast<const GLchar* const*>(&source), nullptr);
		}
		inline static void SetSource(uint32_t shader, const std::vector<const char*>& sources)
		{
			glShaderSource(static_cast<GLuint>(shader), static_cast<GLsizei>(sources.size()), static_cast<const GLchar* const*>(sources.data()), nullptr);
		}

		inline static void Compile(uint32_t shader)
		{
			glCompileShader(static_cast<GLuint>(shader));
		}
		inline static bool GetCompileStatus(uint32_t shader)
		{
			GLint success;
			glGetShaderiv(static_cast<GLuint>(shader), GL_COMPILE_STATUS, &success);
			return success == GL_TRUE;
		}
		inline static std::string GetInfoLog(uint32_t shader)
		{
			GLint length;
			glGetShaderiv(static_cast<GLuint>(shader), GL_INFO_LOG_LENGTH, &length);
			std::string infoLog(static_cast<size_t>(length), ' ');
			glGetShaderInfoLog(static_cast<GLuint>(shader), length, &length, static_cast<GLchar*>(infoLog.data()));
			return infoLog;
		}
	public:
		const uint32_t shader;

		GlShader(ShaderType type, const std::vector<const char*>& sources) :
			Shader(type),
			shader(Create(type))
		{
			SetSource(shader, sources);
			Compile(shader);

			if (!GetCompileStatus(shader))
				throw std::runtime_error("Failed to compile OpenGL shader. " + GetInfoLog(shader));
		}
		GlShader(ShaderType type, const std::string& string, bool readFile) :
			Shader(type),
			shader(Create(type)) 
		{
			std::string sourceCode;

			if (readFile)
				sourceCode = Engine::ReadTextFromFile(string);
			else
				sourceCode = string;

			std::vector<const char*> sources;
			sources.push_back(sourceCode.c_str());

			// TODO: parse include

			SetSource(shader, sources);
			Compile(shader);

			if (!GetCompileStatus(shader))
			{
				auto infoLog = GetInfoLog(shader);
				throw std::runtime_error("Failed to compile OpenGL shader. " + infoLog);
			}
		}

		~GlShader()
		{
			Delete(shader);
		}
	};

	class GlMaterial
	{
	protected:
		inline static uint32_t Create()
		{
			return static_cast<uint32_t>(glCreateProgram());
		}
		inline static void Delete(uint32_t program)
		{
			glDeleteProgram(static_cast<GLuint>(program));
		}
		inline static void Use(uint32_t program)
		{
			glUseProgram(static_cast<GLuint>(program));
		}

		inline static void Attach(uint32_t program, uint32_t shader)
		{
			glAttachShader(static_cast<GLuint>(program), static_cast<GLuint>(shader));
		}
		inline static void Detach(uint32_t program, uint32_t shader)
		{
			glDetachShader(static_cast<GLuint>(program), static_cast<GLuint>(shader));
		}

		inline static void Link(uint32_t program)
		{
			glLinkProgram(static_cast<GLuint>(program));
		}
		inline static bool GetLinkStatus(uint32_t program)
		{
			GLint success;
			glGetProgramiv(static_cast<GLuint>(program), GL_LINK_STATUS, &success);
			return success == GL_TRUE;
		}
		inline static std::string GetInfoLog(uint32_t program)
		{
			GLint length;
			glGetProgramiv(static_cast<GLuint>(program), GL_INFO_LOG_LENGTH, &length);
			std::string infoLog(static_cast<size_t>(length), ' ');
			glGetProgramInfoLog(static_cast<GLuint>(program), length, &length, static_cast<GLchar*>(infoLog.data()));
			return infoLog;
		}

		inline static int32_t GetUniformLocation(uint32_t program, const std::string& name)
		{
			auto location = static_cast<GLint>(glGetUniformLocation(static_cast<GLuint>(program), static_cast<const GLchar*>(name.c_str())));
			if (location == -1)
				throw std::runtime_error("Failed to get uniform location");
			return location;
		}

		static void SetUniform(int32_t index, int32_t value)
		{
			glUniform1i(static_cast<GLint>(index), static_cast<GLint>(value));
		}
		static void SetUniform(int32_t index, float_t value)
		{
			glUniform1f(static_cast<GLint>(index), static_cast<GLfloat>(value));
		}
		static void SetUniform(int32_t index, const glm::vec2& value)
		{
			glUniform2fv(static_cast<GLint>(index), GL_ONE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		static void SetUniform(int32_t index, const glm::vec3& value)
		{
			glUniform3fv(static_cast<GLint>(index), GL_ONE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		static void SetUniform(int32_t index, const glm::vec4& value)
		{
			glUniform4fv(static_cast<GLint>(index), GL_ONE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		static void SetUniform(int32_t index, const glm::mat2& value)
		{
			glUniformMatrix2fv(static_cast<GLint>(index), GL_ONE, GL_FALSE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		static void SetUniform(int32_t index, const glm::mat3& value)
		{
			glUniformMatrix3fv(static_cast<GLint>(index), GL_ONE, GL_FALSE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
		static void SetUniform(int32_t index, const glm::mat4& value)
		{
			glUniformMatrix4fv(static_cast<GLint>(index), GL_ONE, GL_FALSE, static_cast<const GLfloat*>(glm::value_ptr(value)));
		}
	public:
		const uint32_t program;

		GlMaterial(uint32_t shader) : program(Create())
		{
			Attach(program, shader);
			Link(program);
			Detach(program, shader);

			if (!GetLinkStatus(program))
			{
				auto infoLog = GetInfoLog(program);
				throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
			}
		}
		GlMaterial(uint32_t shader1, uint32_t shader2) : program(Create())
		{
			Attach(program, shader1);
			Attach(program, shader2);
			Link(program);
			Detach(program, shader2);
			Detach(program, shader1);

			if (!GetLinkStatus(program))
			{
				auto infoLog = GetInfoLog(program);
				throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
			}
		}
		GlMaterial(uint32_t shader1, uint32_t shader2, uint32_t shader3) : program(Create())
		{
			Attach(program, shader1);
			Attach(program, shader2);
			Attach(program, shader3);
			Link(program);
			Detach(program, shader3);
			Detach(program, shader2);
			Detach(program, shader1);

			if (!GetLinkStatus(program))
			{
				auto infoLog = GetInfoLog(program);
				throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
			}
		}
		GlMaterial(uint32_t shader1, uint32_t shader2, uint32_t shader3, uint32_t shader4) : program(Create())
		{
			Attach(program, shader1);
			Attach(program, shader2);
			Attach(program, shader3);
			Attach(program, shader4);
			Link(program);
			Attach(program, shader4);
			Detach(program, shader3);
			Detach(program, shader2);
			Detach(program, shader1);

			if (!GetLinkStatus(program))
			{
				auto infoLog = GetInfoLog(program);
				throw std::runtime_error("Failed to link OpenGL program. " + infoLog);
			}
		}

		~GlMaterial()
		{
			Delete(program);
		}

		inline int32_t GetUniformLocation(const std::string& name) const
		{
			return GetUniformLocation(program, name);
		}

		virtual void Use() const
		{
			Use(program);
		}
		virtual void Unuse() const
		{
			Use(0);
		}

		virtual void SetModel(const glm::mat4& value) const {}
		virtual void SetView(const glm::mat4& value) const {}
		virtual void SetProj(const glm::mat4& value) const {}
		virtual void SetViewProj(const glm::mat4& value) const {}
		virtual void SetMVP(const glm::mat4& value) const {}
	};
	class GlColorMaterial : public GlMaterial
	{
	public:
		const int32_t mvpLocation;
		const int32_t colorLocation;

		GlColorMaterial(uint32_t vertex, uint32_t fragment) :
			GlMaterial(vertex, fragment),
			mvpLocation(GetUniformLocation("u_MVP")),
			colorLocation(GetUniformLocation("u_Color"))
		{
			Use();
			SetColor(glm::vec4(1.0f));
			Unuse();
		}

		void SetMVP(const glm::mat4& value) const override
		{
			SetUniform(mvpLocation, value);
		}
		void SetColor(const glm::vec4& value) const
		{
			SetUniform(colorLocation, value);
		}
	};

	class GlBuffer
	{
	protected:
		uint64_t size;
		GlBufferUsage usage;

		inline static uint32_t Generate()
		{
			GLuint buffer;
			glGenBuffers(GL_ONE, &buffer);
			return static_cast<uint32_t>(buffer);
		}
		inline static void Delete(uint32_t buffer)
		{
			glDeleteBuffers(GL_ONE, static_cast<const GLuint*>(&buffer));
		}
		inline static void Bind(GlBufferType type, uint32_t buffer)
		{
			glBindBuffer(static_cast<GLenum>(type), static_cast<GLuint>(buffer));
		}

		template<class TData>
		inline static void SetData(GlBufferType type, const std::vector<TData>& data, GlBufferUsage usage)
		{
			glBufferData(static_cast<GLenum>(type), static_cast<GLsizeiptr>(data.size() * sizeof(TData)), static_cast<const GLvoid*>(data.data()), static_cast<GLenum>(usage));
		}

		template<class TData>
		inline static void SetSubData(GlBufferType type, uint64_t offset, const std::vector<TData>& data)
		{
			glBufferSubData(static_cast<GLenum>(type), static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(data.size() * sizeof(TData)), static_cast<const GLvoid*>(data.data()));
		}
	public:
		const uint32_t buffer;
		const GlBufferType type;

		GlBuffer(GlBufferType _type, GlBufferUsage _usage) :
			buffer(Generate()),
			type(_type),
			usage(_usage),
			size(0)
		{}
		~GlBuffer()
		{
			Delete(buffer);
		}

		inline void Bind() const
		{
			Bind(type, buffer);
		}
		inline void Unbind() const
		{
			Bind(type, 0);
		}

		template<class TData>
		inline void SetData(const std::vector<TData>& data)
		{
			size = data.size() * sizeof(TData);
			SetData(type, data, usage);
		}
		template<class TData>
		inline void SetData(const std::vector<TData>& data, GlBufferUsage _usage)
		{
			size = data.size() * sizeof(TData);
			usage = _usage;
			SetData(type, data, _usage);
		}

		template<class TData>
		inline void SetSubData(uint64_t offset, const std::vector<TData>& data)
		{
			SetSubData<TData>(type, offset, data);
		}
	};

	class GlAttribute
	{
	protected:
		inline static void Enable(uint32_t index)
		{
			glEnableVertexAttribArray(static_cast<GLuint>(index));
		}
		inline static void Disable(uint32_t index)
		{
			glDisableVertexAttribArray(static_cast<GLuint>(index));
		}

		inline static void SetPointer(uint32_t index, GlAttributeSize size, GlAttributeType type, bool normalized, int32_t stride, uint64_t offset)
		{
			glVertexAttribPointer(
				static_cast<GLuint>(index),
				static_cast<GLint>(size),
				static_cast<GLenum>(type),
				normalized ? GL_TRUE : GL_FALSE,
				static_cast<GLsizei>(stride),
				reinterpret_cast<const GLvoid*>(offset));
		}
	public:
		const uint32_t index;
		const GlAttributeSize size;
		const GlAttributeType type;
		const bool normalized;
		const int32_t stride;
		const uint64_t offset;

		GlAttribute(uint32_t _index, GlAttributeSize _size, GlAttributeType _type, bool _normalized, int32_t _stride, uint64_t _offset) :
			index(_index),
			size(_size),
			type(_type),
			normalized(_normalized),
			stride(_stride),
			offset(_offset)
		{}

		inline void Enable() const
		{
			Enable(index);
		}
		inline void Disable() const
		{
			Disable(index);
		}

		inline void SetPointer() const
		{
			SetPointer(index, size, type, normalized, stride, offset);
		}
	};
	
	class GlBatch
	{
	protected:
		inline static uint32_t Generate()
		{
			GLuint vertexArray;
			glGenVertexArrays(GL_ONE, &vertexArray);
			return static_cast<uint32_t>(vertexArray);
		}
		inline static void Delete(uint32_t vertexArray)
		{
			glDeleteVertexArrays(GL_ONE, static_cast<const GLuint*>(&vertexArray));
		}

		inline static void Bind(uint32_t vertexArray)
		{
			glBindVertexArray(static_cast<GLuint>(vertexArray));
		}
	public:
		const uint32_t vertexArray;

		GlBatch() : vertexArray(Generate()) {}
		~GlBatch()
		{
			Delete(vertexArray);
		}

		inline void Bind() const
		{
			Bind(vertexArray);
		}
		inline static void Unbind()
		{
			Bind(0);
		}
	};

	class GlMesh : public GlBatch
	{
	protected:
		inline static void DrawElements(GlDrawMode mode, uint32_t count, GlDrawType type)
		{
			glDrawElements(static_cast<GLenum>(mode), static_cast<GLsizei>(count), static_cast<GLenum>(type), nullptr);
		}
	public:
		GlBuffer* const vertexBuffer;
		GlBuffer* const indexBuffer;

		uint32_t indexCount;
		GlDrawMode drawMode;
		GlDrawType drawType;

		GlMesh(GlBuffer* _vertexBuffer, GlBuffer* _indexBuffer, const std::vector<GlAttribute>& _attributes, uint32_t _indexCount, GlDrawMode _drawMode, GlDrawType _drawType) :
			vertexBuffer(_vertexBuffer),
			indexBuffer(_indexBuffer),
			indexCount(_indexCount),
			drawMode(_drawMode),
			drawType(_drawType)
		{
			Bind();
			vertexBuffer->Bind();
			indexBuffer->Bind();

			for (const auto& attribute : _attributes)
			{
				attribute.Enable();
				attribute.SetPointer();
			}

			Unbind();
			vertexBuffer->Unbind();
			indexBuffer->Unbind();
		}

		inline void Draw()
		{
			DrawElements(drawMode, indexCount, drawType);
		}
		inline void Draw(GlDrawMode mode)
		{
			DrawElements(mode, indexCount, drawType);
		}
	};

	struct GlRendererComponent : public Component<GlRendererComponent>
	{
		GlMaterial* material;
		GlMesh* mesh;
		bool draw;

		GlRendererComponent(GlMaterial* _material = nullptr, GlMesh* _mesh = nullptr, bool _draw = true) :
			material(_material),
			mesh(_mesh),
			draw(_draw)
		{}
	};

	class GlGraphicsSystem : public System<GlGraphicsSystem>
	{
	protected:
		GlColorMaterial* colorMaterial;

		GlMesh* squareMesh;
		GlMesh* cubeMesh;

		Entity mainCamera;
	public:
		GlGraphicsSystem(GlWindow* window)
		{
			if (!window->IsES())
			{
				auto colorVert = GlShader(ShaderType::Vertex, "resources/shaders/color.vert", true);
				auto colorFrag = GlShader(ShaderType::Fragment, "resources/shaders/color.frag", true);
				colorMaterial = new GlColorMaterial(colorVert.shader, colorFrag.shader);
			}
			else
			{
				auto colorVert = GlShader(ShaderType::Vertex, "resources/shaders/es_color.vert", true);
				auto colorFrag = GlShader(ShaderType::Fragment, "resources/shaders/es_color.frag", true);
				colorMaterial = new GlColorMaterial(colorVert.shader, colorFrag.shader);
			}

			auto vertexBuffer = new GlBuffer(GlBufferType::Array, GlBufferUsage::StaticDraw);
			vertexBuffer->Bind();
			vertexBuffer->SetData(GlPrimitive::SquareVertices);
			vertexBuffer->Unbind();
			auto indexBuffer = new GlBuffer(GlBufferType::ElementArray, GlBufferUsage::StaticDraw);
			indexBuffer->Bind();
			indexBuffer->SetData(GlPrimitive::SquareIndices);
			indexBuffer->Unbind();
			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttributeSize::Three, GlAttributeType::Float, false, 0, 0),
			};
			squareMesh = new GlMesh(vertexBuffer, indexBuffer, attributes, GlPrimitive::SquareIndices.size(), GlDrawMode::Triangles, GlDrawType::UnsignedByte);
		}
		~GlGraphicsSystem()
		{
			delete squareMesh->indexBuffer;
			delete squareMesh->vertexBuffer;
			delete squareMesh;

			delete colorMaterial;
		}

		void configure(EntityManager& entities, EventManager& events) override
		{
			mainCamera = entities.create();
			mainCamera.assign<CameraComponent>();
			mainCamera.assign<TransformComponent>(glm::vec3(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			auto testSquare = entities.create();
			testSquare.assign<GlRendererComponent>(colorMaterial, squareMesh, true);
			testSquare.assign<TransformComponent>();
		}
		void update(EntityManager& entities, EventManager& events, TimeDelta deltaTime) override
		{
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);

			glClear(GL_COLOR_BUFFER_BIT);

			ComponentHandle<TransformComponent> transformComponent;
			ComponentHandle<CameraComponent> cameraComponent;
			ComponentHandle<GlRendererComponent> rendererComponent;

			std::multimap<int, Entity> cameraEntities;

			for (auto entity : entities.entities_with_components(cameraComponent, transformComponent))
				cameraEntities.emplace(cameraComponent->renderQueue, entity);

			for (auto cameraEntity : cameraEntities)
			{
				cameraComponent = cameraEntity.second.component<CameraComponent>();
				transformComponent = cameraEntity.second.component<TransformComponent>();

				const auto& viewMatrix = transformComponent->matrix;
				const auto& projMatrix = cameraComponent->matrix;
				const auto viewProjMatrix = projMatrix * viewMatrix;
				
				for (auto rendererEntity : entities.entities_with_components(rendererComponent, transformComponent))
				{
					const auto material = rendererComponent->material;
					const auto mesh = rendererComponent->mesh;

					if (rendererComponent->draw && material && mesh)
					{
						const auto& modelMatrix = transformComponent->matrix;
						const auto mvpMatrix = viewProjMatrix * modelMatrix;

						material->Use();
						material->SetModel(modelMatrix);
						material->SetView(viewMatrix);
						material->SetProj(projMatrix);
						material->SetViewProj(viewProjMatrix);
						material->SetMVP(mvpMatrix);

						mesh->Bind();
						mesh->Draw();
						mesh->Unbind();

						material->Unuse();
					}
				}
			}
		}
	};
}
