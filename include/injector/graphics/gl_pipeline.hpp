#pragma once
#include <injector/graphics/pipeline.hpp>
#include <GL/glew.h>

namespace INJECTOR_NAMESPACE
{
	/*class GlPipeline : public Pipeline
	{
	protected:
		uint32_t instance;

		static uint32_t create() noexcept;
		static void destroy(uint32_t program) noexcept;
		static void use(uint32_t program) noexcept;

		static void attach(uint32_t program, uint32_t shader) noexcept;
		static void detach(uint32_t program, uint32_t shader) noexcept;

		static void link(uint32_t program) noexcept;
		static bool getLinkStatus(uint32_t program) noexcept;
		static std::string getInfoLog(uint32_t program) noexcept;

		static int32_t getUniformLocation(uint32_t program, const std::string& name);

		static void setUniform(int32_t index, int value) noexcept;
		static void setUniform(int32_t index, float value) noexcept;
		static void setUniform(int32_t index, const Vector2& vector) noexcept;
		static void setUniform(int32_t index, const Vector3& vector) noexcept;
		static void setUniform(int32_t index, const Vector4& vector) noexcept;
		static void setUniform(int32_t index, const Matrix2& matrix) noexcept;
		static void setUniform(int32_t index, const Matrix3& matrix) noexcept;
		static void setUniform(int32_t index, const Matrix4& matrix) noexcept;

		static void enableDepthTest() noexcept;
		static void disableDepthTest() noexcept;
		static void setDepthTestFunction(uint32_t function) noexcept;

		static void enableBlend() noexcept;
		static void disableBlend() noexcept;
		static void setBlendFunction(uint32_t source, uint32_t destination) noexcept;
		static void setBlendFunction(uint32_t sourceRgb, uint32_t destinationRgb,
			uint32_t sourceAlpha, uint32_t destinationAlpha) noexcept;

		int32_t getUniformLocation(const std::string& name);
	public:
		GlPipeline(const GlShader& shader);
		GlPipeline(const GlShader& shader1,
			const GlShader& shader2);
		GlPipeline(const GlShader& shader1,
			const GlShader& shader2,
			const GlShader& shader3);
		GlPipeline(const GlShader& shader1,
			const GlShader& shader2,
			const GlShader& shader3,
			const GlShader& shader4);
		virtual ~GlMaterial();

		uint32_t getInstance() const noexcept;

		void use() override;
		void unuse() override;
	};*/
}
