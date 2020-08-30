#include <injector/graphics/gl_color_pipeline.hpp>
#include <injector/graphics/gl_shader.hpp>
#include <injector/file_stream.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	/*GlAttribute(0, GlAttribute::Size::Three, GlAttribute::Type::Float, false, sizeof(float) * 6, 0),
		GlAttribute(1, GlAttribute::Size::Three, GlAttribute::Type::Float, false, sizeof(float) * 6, sizeof(float) * 3),*/

	const std::vector<GlVertexAttribute> GlColorPipeline::colorAttributes =
	{
		GlVertexAttribute(0, 3, GL_FLOAT, false, 0, 0),
	};

	GlColorPipeline::GlColorPipeline(
		bool gles,
		const Matrix4& _mvp,
		const Vector4& _color) :
		GlPipeline(colorAttributes),
		mvp(_mvp),
		color(_color)
	{
		auto vertexSource = FileStream::readAllText(
			"resources/shaders/color.vert");
		auto vertexShader = GlShader(GL_VERTEX_SHADER, vertexSource, gles);

		auto fragmentSource = FileStream::readAllText(
			"resources/shaders/color.frag");
		auto fragmentShader = GlShader(GL_FRAGMENT_SHADER, fragmentSource, gles);

		glAttachShader(program, vertexShader.getShader());
		glAttachShader(program, fragmentShader.getShader());
		glLinkProgram(program);
		glDetachShader(program, vertexShader.getShader());
		glDetachShader(program, fragmentShader.getShader());

		if (!getLinkStatus(program))
		{
			auto log = getInfoLog(program);
			glDeleteProgram(program);

			throw std::runtime_error("Failed to link OpenGL program: " + log);
		}

		mvpLocation = getUniformLocation(program, "u_MVP");
		colorLocation = getUniformLocation(program, "u_Color");
	}
	GlColorPipeline::~GlColorPipeline()
	{}

	const Matrix4& GlColorPipeline::getMVP() const
	{
		return mvp;
	}
	void GlColorPipeline::setMVP(const Matrix4& _mvp)
	{
		mvp = Matrix4(_mvp);
	}

	const Vector4& GlColorPipeline::getColor() const
	{
		return color;
	}
	void GlColorPipeline::setColor(const Vector4& _color)
	{
		color = Vector4(_color);
	}

	void GlColorPipeline::bind()
	{
		GlPipeline::bind();

		glUniformMatrix4fv(mvpLocation, GL_ONE, GL_FALSE,
			reinterpret_cast<const GLfloat*>(&mvp));
		glUniform4fv(colorLocation, GL_ONE,
			reinterpret_cast<const GLfloat*>(&color));

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
	}
}
