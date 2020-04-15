#pragma once
#include <injector_engine/engine.hpp>

namespace InjectorEngine
{
	class GlGraphics;
	class GlMaterial;
	class GlMaterialColor;
	class GlShader;
	class GlWindow;

	class GlGraphics : public System
	{
	protected:
		GlMaterialColor* materialColor;
	public:
		GlGraphics(GlWindow* window, int updateQueue = 20000);
		~GlGraphics();

		void OnUpdate(Window* window) override;
	};

	class GlMaterial
	{
	protected:
		static gl::GLuint Create();
		static void Delete(gl::GLuint program);

		static void Attach(gl::GLuint program, gl::GLuint shader);
		static void Detach(gl::GLuint program, gl::GLuint shader);

		static void Link(gl::GLuint program);
		static bool GetLinkStatus(gl::GLuint program);
		static std::string GetInfoLog(gl::GLuint program);

		static gl::GLint GetUniformLocation(gl::GLuint program, const std::string& name);

		static void SetUniform(gl::GLint index, gl::GLint value);
		static void SetUniform(gl::GLint index, gl::GLfloat value);
		static void SetUniform(gl::GLint index, const glm::vec2& value);
		static void SetUniform(gl::GLint index, const glm::vec3& value);
		static void SetUniform(gl::GLint index, const glm::vec4& value);
		static void SetUniform(gl::GLint index, const glm::mat2& value);
		static void SetUniform(gl::GLint index, const glm::mat3& value);
		static void SetUniform(gl::GLint index, const glm::mat4& value);
	public:
		const gl::GLuint program;

		GlMaterial(gl::GLuint shader);
		GlMaterial(gl::GLuint shader1, gl::GLuint shader2);
		GlMaterial(gl::GLuint shader1, gl::GLuint shader2, gl::GLuint shader3);
		GlMaterial(gl::GLuint shader1, gl::GLuint shader2, gl::GLuint shader3, gl::GLuint shader4);

		~GlMaterial();

		gl::GLint GetUniformLocation(const std::string& name) const;
	};

	class GlMaterialColor : public GlMaterial
	{
	public:
		const gl::GLint mvpLocation;
		const gl::GLint colorLocation;

		GlMaterialColor(gl::GLuint vertex, gl::GLuint fragment);

		void SetMVP(const glm::mat4& value) const;
		void SetColor(const glm::vec4& value) const;
	};

	class GlShader : public Shader
	{
	protected:
		static gl::GLenum TypeToEnum(ShaderType type);
		
		static gl::GLuint Create(ShaderType type);
		static void Delete(gl::GLuint shader);

		static void SetSource(gl::GLuint shader, const char* source);
		static void SetSource(gl::GLuint shader, const std::vector<const char*>& sources);

		static void Compile(gl::GLuint shader);
		static bool GetCompileStatus(gl::GLuint shader);
		static std::string GetInfoLog(gl::GLuint shader);
	public:
		const gl::GLuint shader;
		
		GlShader(ShaderType type, const std::vector<const char*>& sources);
		GlShader(ShaderType type, const std::string& string, bool readFile);

		~GlShader();

		static const std::string OpenGLESMacros;
		static const std::string PrecisionMacros;
	};

	class GlWindow : public Window
	{
	protected:
		bool isES;
	public:
		GlWindow(bool isES = false, std::string title = "Injector Engine - Editor", glm::ivec2 size = glm::ivec2(800, 600), GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

		bool IsES() const;

		void OnFramebufferResize(glm::ivec2 size) override;
	};
}
