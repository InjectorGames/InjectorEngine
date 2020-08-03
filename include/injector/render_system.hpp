#pragma once
#include <injector/manager.hpp>
#include <injector/render_component.hpp>
#include <injector/window_component.hpp>
#include <injector/camera_component.hpp>
#include <injector/transform_component.hpp>

namespace INJECTOR_NAMESPACE
{
	class RenderSystem final : public System
	{
	private:
		ShaderHandle(*createShaderPointer)(ShaderStage, const std::string&);
		MaterialHandle(*createColorPointer)(
			const std::string& vertexPath, const std::string& fragmentPath);

		std::set<EntityHandle> cameras;
		std::set<EntityHandle> renders;

		static ShaderHandle createShaderOpenGL(
			ShaderStage stage, const std::string& path);
		static ShaderHandle createShaderOpenGLES(
			ShaderStage stage, const std::string& path);
		static ShaderHandle createShaderVulkan(
			ShaderStage stage, const std::string& path);

		static MaterialHandle createColorOpenGL(
			const std::string& vertexPath, const std::string& fragmentPath);
		static MaterialHandle createColorOpenGLES(
			const std::string& vertexPath, const std::string& fragmentPath);
		static MaterialHandle createColorVulkan(
			const std::string& vertexPath, const std::string& fragmentPath);
	public:
		EntityHandle window;

		RenderSystem(const EntityHandle& window = nullptr);

		void update() override;

		bool addCamera(const EntityHandle& entity) noexcept;
		bool removeCamera(const EntityHandle& entity) noexcept;
		void removeCameras() noexcept;
		size_t getCameraCount() const noexcept;

		bool addRender(const EntityHandle& entity) noexcept;
		bool removeRender(const EntityHandle& entity) noexcept;
		void removeRenders() noexcept;
		size_t getRenderCount() const noexcept;

		ShaderHandle createShader(ShaderStage stage, const std::string& filePath);

		MaterialHandle createColorMaterial(
			const std::string& vertexPath, const std::string& fragmentPath);

		MeshHandle createCubeMesh();
	};
}
