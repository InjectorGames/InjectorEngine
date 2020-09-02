#include <injector/graphics/gl_diffuse_pipeline.hpp>
#include <injector/graphics/gl_shader.hpp>
#include <injector/file_stream.hpp>

namespace INJECTOR_NAMESPACE
{
    const std::vector<GlVertexAttribute> GlDiffusePipeline::vertexAttributes =
	{
		GlVertexAttribute(0, 3, GL_FLOAT, false, sizeof(Vector3) * 2, 0),
        GlVertexAttribute(1, 3, GL_FLOAT, false, sizeof(Vector3) * 2, sizeof(Vector3)),
	};

    GlDiffusePipeline::GlDiffusePipeline(
        bool gles,
        const Vector4& _objectColor,
        const Vector4& _ambientColor,
        const Vector4& _lightColor,
        const Vector3& _lightDirection) :
        GlPipeline(GL_TRIANGLES, vertexAttributes),
		objectColor(_objectColor),
        ambientColor(_ambientColor),
        lightColor(_lightColor),
        lightDirection(_lightDirection.getNormalized())
    {
        auto vertexSource = FileStream::readAllText(
			"resources/shaders/diffuse.vert");
		auto vertexShader = GlShader(GL_VERTEX_SHADER, vertexSource, gles);

		auto fragmentSource = FileStream::readAllText(
			"resources/shaders/diffuse.frag");
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
		normalLocation = getUniformLocation(program, "u_Normal");
        objectColorLocation = getUniformLocation(program, "u_ObjectColor");
        ambientColorLocation = getUniformLocation(program, "u_AmbientColor");
        lightColorLocation = getUniformLocation(program, "u_LightColor");
        lightDirectionLocation = getUniformLocation(program, "u_LightDirection");
    }
    GlDiffusePipeline::~GlDiffusePipeline()
    {}

    const Vector4& GlDiffusePipeline::getObjectColor() const
    {
        return objectColor;
    }
	void GlDiffusePipeline::setObjectColor(const Vector4& _objectColor)
    {
        objectColor = Vector4(_objectColor);
    }

    const Vector4& GlDiffusePipeline::getAmbientColor() const
    {
        return ambientColor;
    }
	void GlDiffusePipeline::setAmbientColor(const Vector4& _ambientColor)
    {
        ambientColor = Vector4(_ambientColor);
    }

	const Vector4& GlDiffusePipeline::getLightColor() const
    {
        return lightColor;
    }
	void GlDiffusePipeline::setLightColor(const Vector4& _lightColor)
    {
        lightColor = Vector4(_lightColor);
    }

	const Vector3& GlDiffusePipeline::getLightDirection() const
    {
        return lightDirection;
    }
	void GlDiffusePipeline::setLightDirection(const Vector3& _lightDirection)
    {
        lightDirection = Vector3(_lightDirection.getNormalized());
    }

    void GlDiffusePipeline::flush()
	{
		GlPipeline::bind();

		glUniform4fv(objectColorLocation, GL_ONE, 
			reinterpret_cast<const GLfloat*>(&objectColor));
        glUniform4fv(ambientColorLocation, GL_ONE, 
			reinterpret_cast<const GLfloat*>(&ambientColor));
        glUniform4fv(lightColorLocation, GL_ONE, 
			reinterpret_cast<const GLfloat*>(&lightColor));
        glUniform3fv(lightDirectionLocation, GL_ONE, 
			reinterpret_cast<const GLfloat*>(&lightDirection));
	}
	void GlDiffusePipeline::bind()
	{
		GlPipeline::bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK); 
		glFrontFace(GL_CW); 
	}

	void GlDiffusePipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
        auto normal = model.getInversed().getTransposed().getMatrix3();
		glUniformMatrix4fv(mvpLocation, GL_ONE, GL_FALSE,
			reinterpret_cast<const GLfloat*>(&mvp));
        glUniformMatrix3fv(normalLocation, GL_ONE, GL_FALSE,
			reinterpret_cast<const GLfloat*>(&normal));
	}
}
