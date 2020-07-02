#pragma once
#include <inject/gl/batch.hpp>
#include <inject/gl/buffer.hpp>
#include <inject/gl/attribute.hpp>
#include <inject/gl/primitives.hpp>

namespace INJECT_NAMESPACE
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
		template<class TV, class TI>
		inline static const std::shared_ptr<GlMesh> Create(
			const std::vector<const std::vector<TV>*>& vertexArrays,
			const std::vector<TI>& indices,
			const std::vector<GlAttribute>& attributes,
			const GlBuffer::Usage usage,
			const DrawType drawType) noexcept
		{
			if (vertexArrays.size() != attributes.size())
				throw std::runtime_error("Incorrect data sizez");

			auto vertexCount = static_cast<size_t>(0);
			for (size_t i = 0; i < vertexArrays.size(); i++)
				vertexCount += vertexArrays[i]->size();

			std::vector<TV> vertices(vertexCount);

			for (size_t i = 0; i < vertexArrays.size(); i++)
			{
				const auto _vertices = vertexArrays[i];
				const auto size = static_cast<size_t>(attributes[i].size);
				const auto stride = attributes[i].stride / sizeof(TV);
				const auto offset = attributes[i].offset / sizeof(TV);

				for (size_t j = 0, o = offset; j < _vertices->size(); j += size, o += stride)
					std::copy_n(&_vertices[0][j], size, &vertices[o]);
			}

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

			return Create(GlPrimitives::squareVertices, GlPrimitives::squareIndices,
				attributes, GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}
		inline static const std::shared_ptr<GlMesh> CreateSquareVN() noexcept
		{
			auto vertices = std::vector<const std::vector<float>*>
			{
				&GlPrimitives::squareVertices,
				&GlPrimitives::squareNormals,
			};
			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, sizeof(float) * 6, 0),
				GlAttribute(1, GlAttribute::Size::Three, GlAttribute::Type::Float, false, sizeof(float) * 6, sizeof(float) * 3),
			};

			return Create(vertices, GlPrimitives::squareIndices,
				attributes, GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}

		inline static const std::shared_ptr<GlMesh> CreateCubeV() noexcept
		{
			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
			};

			return Create(GlPrimitives::cubeVertices, GlPrimitives::cubeIndices,
				attributes, GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}
		inline static const std::shared_ptr<GlMesh> CreateCubeVN() noexcept
		{
			auto vertices = std::vector<const std::vector<float>*>
			{
				&GlPrimitives::cubeVertices,
				&GlPrimitives::cubeNormals,
			};
			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, sizeof(float) * 6, 0),
				GlAttribute(1, GlAttribute::Size::Three, GlAttribute::Type::Float, false, sizeof(float) * 6, sizeof(float) * 3),
			};

			return Create(vertices, GlPrimitives::cubeIndices,
				attributes, GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}

		inline static const std::shared_ptr<GlMesh> CreateAxisV() noexcept
		{
			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
			};

			return Create(GlPrimitives::axisVertices, GlPrimitives::axisIndices,
				attributes, GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}
		inline static const std::shared_ptr<GlMesh> CreateAxisVC() noexcept
		{
			auto vertices = std::vector<const std::vector<float>*>
			{
				&GlPrimitives::axisVertices,
				&GlPrimitives::axisColors,
			};

			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, sizeof(float) * 6, 0),
				GlAttribute(1, GlAttribute::Size::Three, GlAttribute::Type::Float, false, sizeof(float) * 6, sizeof(float) * 3),
			};

			return Create(vertices, GlPrimitives::axisIndices,
				attributes, GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}

		inline static const std::shared_ptr<GlMesh> CreateGradientSky() noexcept
		{
			auto attributes = std::vector<GlAttribute>
			{
				GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, 0, 0),
			};

			return Create(GlPrimitives::gradientSkyVertices, GlPrimitives::gradientSkyIndices,
				attributes, GlBuffer::Usage::StaticDraw, DrawType::UnsignedByte);
		}
	};
}
