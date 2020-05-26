#pragma once
#include <inject/gl/batch.hpp>
#include <inject/gl/buffer.hpp>
#include <inject/gl/attribute.hpp>
#include <inject/gl/primitive.hpp>

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

		inline const std::shared_ptr<GlBuffer>& getVertexBuffer() const noexcept
		{
			return vertexBuffer;
		}
		inline const std::shared_ptr<GlBuffer>& getIndexBuffer() const noexcept
		{
			return indexBuffer;
		}

		virtual void draw(const DrawMode mode) const
		{
			draw(mode, indexCount, drawType);
		}

		template<class TV, class TI>
		inline static const std::shared_ptr<GlMesh> Create(
			const std::vector<TV>& vertices,
			const std::vector<TI>& indices,
			const std::vector<GlAttribute>& attributes,
			const GlBuffer::Usage usage,
			const DrawType drawType) noexcept
		{
			auto vertexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::Array, usage);
			vertexBuffer->bind();
			vertexBuffer->setData<TV>(vertices);
			vertexBuffer->unbind();

			auto indexBuffer = std::make_shared<GlBuffer>(
				GlBuffer::Type::ElementArray, usage);
			indexBuffer->bind();
			indexBuffer->setData<TI>(indices);
			indexBuffer->unbind();

			return std::make_shared<GlMesh>(
				vertexBuffer,
				indexBuffer,
				attributes,
				indices.size(),
				drawType);
		}

		inline static const std::shared_ptr<GlMesh> CreateSquareV() noexcept
		{
			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
			};

			return Create(GlPrimitive::squareVertices, GlPrimitive::squareIndices, attributes,
				GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}
		inline static const std::shared_ptr<GlMesh> CreateSquareVN() noexcept
		{
			auto vertices(GlPrimitive::squareVertices);
			std::copy(GlPrimitive::squareNormals.begin(), GlPrimitive::squareNormals.end(), std::back_inserter(vertices));

			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
				GlAttribute(1, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0,
				GlPrimitive::squareVertices.size() * sizeof(float)),
			};

			return Create(vertices, GlPrimitive::squareIndices, attributes,
				GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}

		inline static const std::shared_ptr<GlMesh> CreateCubeV() noexcept
		{
			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
			};

			return Create(GlPrimitive::cubeVertices, GlPrimitive::cubeIndices, attributes,
				GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}
		inline static const std::shared_ptr<GlMesh> CreateCubeVN() noexcept
		{
			auto vertices(GlPrimitive::cubeVertices);
			std::copy(GlPrimitive::cubeNormals.begin(), GlPrimitive::cubeNormals.end(), std::back_inserter(vertices));

			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
				GlAttribute(1, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0,
				GlPrimitive::cubeVertices.size() * sizeof(float)),
			};

			return Create(vertices, GlPrimitive::cubeIndices, attributes,
				GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}

		inline static const std::shared_ptr<GlMesh> CreateAxisV() noexcept
		{
			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
			};

			return Create(GlPrimitive::axisVertices, GlPrimitive::axisIndices, attributes,
				GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}
		inline static const std::shared_ptr<GlMesh> CreateAxisVC() noexcept
		{
			auto vertices(GlPrimitive::axisVertices);
			std::copy(GlPrimitive::axisColors.begin(), GlPrimitive::axisColors.end(), std::back_inserter(vertices));

			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
				GlAttribute(1, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0,
				GlPrimitive::axisVertices.size() * sizeof(float)),
			};

			return Create(vertices, GlPrimitive::axisIndices, attributes,
				GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}

		inline static const std::shared_ptr<GlMesh> CreateGradientSky() noexcept
		{
			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
			};

			return Create(GlPrimitive::gradientSkyVertices, GlPrimitive::gradientSkyIndices, attributes,
				GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}
	};
}
