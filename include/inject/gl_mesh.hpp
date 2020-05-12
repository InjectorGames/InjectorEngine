#pragma once
#include <inject/gl_batch.hpp>
#include <inject/gl_buffer.hpp>
#include <inject/gl_attribute.hpp>
#include <inject/gl_primitive.hpp>

namespace inject
{
	class GlMesh : public GlBatch
	{
	public:
		enum class DrawMode : GLenum
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

		enum class DrawType : GLenum
		{
			UnsignedByte = GL_UNSIGNED_BYTE,
			UnsignedShort = GL_UNSIGNED_SHORT,
			UnsignedInt = GL_UNSIGNED_INT,
		};
	protected:
		std::shared_ptr<GlBuffer> vertexBuffer;
		std::shared_ptr<GlBuffer> indexBuffer;

		inline static void draw(const DrawMode mode, const uint32_t count, const DrawType type) noexcept
		{
			glDrawElements(
				static_cast<GLenum>(mode),
				static_cast<GLsizei>(count),
				static_cast<GLenum>(type),
				nullptr);
		}
	public:
		uint32_t indexCount;
		DrawType drawType;

		GlMesh(const std::shared_ptr<GlBuffer>& _vertexBuffer,
			const std::shared_ptr<GlBuffer>& _indexBuffer,
			const std::vector<GlAttribute>& _attributes,
			const uint32_t _indexCount,
			const DrawType _drawType) :
			vertexBuffer(_vertexBuffer),
			indexBuffer(_indexBuffer),
			indexCount(_indexCount),
			drawType(_drawType)
		{
			bind();
			vertexBuffer->bind();
			indexBuffer->bind();

			for (const auto& attribute : _attributes)
			{
				attribute.enable();
				attribute.setPointer();
			}

			unbind();
			vertexBuffer->unbind();
			indexBuffer->unbind();
		}

		inline std::shared_ptr<GlBuffer> getVertexBuffer() const noexcept
		{
			return vertexBuffer;
		}
		inline std::shared_ptr<GlBuffer> getIndexBuffer() const noexcept
		{
			return indexBuffer;
		}

		virtual void draw(const DrawMode mode) const
		{
			draw(mode, indexCount, drawType);
		}

		inline static std::shared_ptr<GlMesh> CreateSquareV() noexcept
		{
			auto vertexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::Array,
				GlBuffer::Usage::StaticDraw);
			vertexBuffer->bind();
			vertexBuffer->setData(GlPrimitive::squareVertices);
			vertexBuffer->unbind();

			auto indexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::ElementArray,
				GlBuffer::Usage::StaticDraw);
			indexBuffer->bind();
			indexBuffer->setData(GlPrimitive::squareIndices);
			indexBuffer->unbind();

			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
			};

			return std::make_shared<GlMesh>(
				vertexBuffer,
				indexBuffer,
				attributes,
				GlPrimitive::squareIndices.size(),
				DrawType::UnsignedByte);
		}
		inline static std::shared_ptr<GlMesh> CreateSquareVN() noexcept
		{
			auto vertices(GlPrimitive::squareVertices);
			std::copy(GlPrimitive::squareNormals.begin(), GlPrimitive::squareNormals.end(), std::back_inserter(vertices));

			auto vertexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::Array,
				GlBuffer::Usage::StaticDraw);
			vertexBuffer->bind();
			vertexBuffer->setData(vertices);
			vertexBuffer->unbind();

			auto indexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::ElementArray,
				GlBuffer::Usage::StaticDraw);
			indexBuffer->bind();
			indexBuffer->setData(GlPrimitive::squareIndices);
			indexBuffer->unbind();

			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
				GlAttribute(1, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0,
				GlPrimitive::squareVertices.size() * sizeof(float)),
			};

			return std::make_shared<GlMesh>(
				vertexBuffer,
				indexBuffer,
				attributes,
				GlPrimitive::squareIndices.size(),
				DrawType::UnsignedByte);
		}

		inline static std::shared_ptr<GlMesh> CreateCubeV() noexcept
		{
			auto vertexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::Array,
				GlBuffer::Usage::StaticDraw);
			vertexBuffer->bind();
			vertexBuffer->setData(GlPrimitive::cubeVertices);
			vertexBuffer->unbind();

			auto indexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::ElementArray,
				GlBuffer::Usage::StaticDraw);
			indexBuffer->bind();
			indexBuffer->setData(GlPrimitive::cubeIndices);
			indexBuffer->unbind();

			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
			};

			return std::make_shared<GlMesh>(
				vertexBuffer,
				indexBuffer,
				attributes,
				GlPrimitive::cubeIndices.size(),
				DrawType::UnsignedByte);
		}
		inline static std::shared_ptr<GlMesh> CreateCubeVN() noexcept
		{
			auto vertices(GlPrimitive::cubeVertices);
			std::copy(GlPrimitive::cubeNormals.begin(), GlPrimitive::cubeNormals.end(), std::back_inserter(vertices));

			auto vertexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::Array,
				GlBuffer::Usage::StaticDraw);
			vertexBuffer->bind();
			vertexBuffer->setData(vertices);
			vertexBuffer->unbind();

			auto indexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::ElementArray,
				GlBuffer::Usage::StaticDraw);
			indexBuffer->bind();
			indexBuffer->setData(GlPrimitive::cubeIndices);
			indexBuffer->unbind();

			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
				GlAttribute(1, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0,
				GlPrimitive::cubeVertices.size() * sizeof(float)),
			};

			return std::make_shared<GlMesh>(
				vertexBuffer,
				indexBuffer,
				attributes,
				GlPrimitive::cubeIndices.size(),
				DrawType::UnsignedByte);
		}

		inline static std::shared_ptr<GlMesh> CreateGradientSky() noexcept
		{
			auto vertexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::Array,
				GlBuffer::Usage::StaticDraw);
			vertexBuffer->bind();
			vertexBuffer->setData(GlPrimitive::gradientSkyVertices);
			vertexBuffer->unbind();

			auto indexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::ElementArray,
				GlBuffer::Usage::StaticDraw);
			indexBuffer->bind();
			indexBuffer->setData(GlPrimitive::gradientSkyIndices);
			indexBuffer->unbind();

			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
			};

			return std::make_shared<GlMesh>(
				vertexBuffer,
				indexBuffer,
				attributes,
				GlPrimitive::gradientSkyIndices.size(),
				DrawType::UnsignedByte);
		}
	};
}
