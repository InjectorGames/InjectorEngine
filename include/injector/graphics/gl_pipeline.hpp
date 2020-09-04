#pragma once
#include <injector/graphics/pipeline.hpp>
#include <injector/graphics/gl_vertex_attribute.hpp>

#include <GL/glew.h>

#include <string>
#include <vector>
#include <memory>

namespace injector::graphics
{
	class GlPipeline : public Pipeline
	{
	protected:
		GLuint program;
		GLenum drawMode;
		std::vector<GlVertexAttribute> vertexAttributes;
		

		/*
		static void setUniform(GLint index, int value) noexcept;
		static void setUniform(GLint index, float value) noexcept;
		static void setUniform(GLint index, const Vector2& vector) noexcept;
		static void setUniform(GLint index, const Vector3& vector) noexcept;
		static void setUniform(GLint index, const Vector4& vector) noexcept;
		static void setUniform(GLint index, const Matrix2& matrix) noexcept;
		static void setUniform(GLint index, const Matrix3& matrix) noexcept;
		static void setUniform(GLint index, const Matrix4& matrix) noexcept;

		static void enableDepthTest() noexcept;
		static void disableDepthTest() noexcept;
		static void setDepthTestFunction(uint32_t function) noexcept;

		static void enableBlend() noexcept;
		static void disableBlend() noexcept;
		static void setBlendFunction(uint32_t source, uint32_t destination) noexcept;
		static void setBlendFunction(uint32_t sourceRgb, uint32_t destinationRgb,
			uint32_t sourceAlpha, uint32_t destinationAlpha) noexcept;

		int32_t getUniformLocation(const std::string& name);*/
	public:
		GlPipeline(
			GLenum drawMode,
			const std::vector<GlVertexAttribute>& vertexAttributes);
		virtual ~GlPipeline();

		GLuint getProgram() const noexcept;
		GLenum getDrawMode() const noexcept;
		const std::vector<GlVertexAttribute>& getVertexAttributes() const noexcept;

		virtual void flush();
		virtual void bind();

		static bool getLinkStatus(GLuint program) noexcept;
		static std::string getInfoLog(GLuint program) noexcept;
		static GLint getUniformLocation(GLuint program, const std::string& name);
	};

	using GlPipelineHandle = std::shared_ptr<GlPipeline>;
}
