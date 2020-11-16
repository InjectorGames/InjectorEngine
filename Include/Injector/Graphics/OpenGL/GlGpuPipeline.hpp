#pragma once
#include "Injector/Graphics/GpuPipeline.hpp"
#include "Injector/GlfwDefines.hpp"
#include "Injector/Mathematics/Vector4.hpp"

#include <string>
#include <vector>

namespace Injector
{
	class GlGpuPipeline : public GpuPipeline
	{
	 protected:
		GLuint program;
		GLenum glDrawMode;

		static bool getLinkStatus(
			GLuint program) noexcept;
		static std::string getInfoLog(
			GLuint program) noexcept;

		static GLint getUniformLocation(
			GLuint program,
			const std::string& name);
		static GLuint getUniformBlockIndex(
			GLuint program,
			const std::string& name);

		static void setVertexAttributePointer(
			GLuint index,
			GLint size,
			GLenum type,
			GLboolean normalized,
			size_t stride,
			size_t offset) noexcept;

		static void setUniform(
			GLint location, int32_t value) noexcept;
		static void setUniform(
			GLint location, uint32_t value) noexcept;
		static void setUniform(
			GLint location, float value) noexcept;
		static void setUniform(
			GLint location, const IntVector2& value) noexcept;
		static void setUniform(
			GLint location, const IntVector3& value) noexcept;
		static void setUniform(
			GLint location, const IntVector4& value) noexcept;
		static void setUniform(
			GLint location, const FloatVector2& value) noexcept;
		static void setUniform(
			GLint location, const FloatVector3& value) noexcept;
		static void setUniform(
			GLint location, const FloatVector4& value) noexcept;
		static void setUniform(
			GLint location,
			const FloatMatrix2& value) noexcept;
		static void setUniform(
			GLint location,
			const FloatMatrix3& value) noexcept;
		static void setUniform(
			GLint location,
			const FloatMatrix4& value) noexcept;
	 public:
		explicit GlGpuPipeline(
			GpuDrawMode drawMode) noexcept;
		~GlGpuPipeline() override;

		GLuint getProgram() const noexcept;
		GLenum getGlDrawMode() const noexcept;

		virtual void bind();
		virtual void unbind();

		virtual void flush() = 0;
		virtual void setAttributes() = 0;

		bool operator==(const GlGpuPipeline& pipeline) const noexcept;
		bool operator!=(const GlGpuPipeline& pipeline) const noexcept;

		static bool less(
			const GlGpuPipeline& a,
			const GlGpuPipeline& b);
	};
}
