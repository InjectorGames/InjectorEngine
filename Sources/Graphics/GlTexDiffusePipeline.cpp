#include "Injector/Graphics/GlTexDiffusePipeline.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
    GlTexDiffusePipeline::GlTexDiffusePipeline(
        bool gles,
        const std::shared_ptr<GlTexture>& _texture,
        const Vector4& objectColor,
		const Vector4& ambientColor,
		const Vector4& lightColor,
		const Vector3& lightDirection) :
        GlDiffusePipeline(gles, objectColor,
            ambientColor, lightColor, lightDirection),
        texture(_texture)
    {
        if(!_texture)
            throw NullException("GlTexDiffusePipeline", "GlTexDiffusePipeline", "texture");

        auto textureLocation = getUniformLocation(program, "u_Texture");

        GlPipeline::bind();
        glUniform1i(textureLocation, 0);
    }
    GlTexDiffusePipeline::~GlTexDiffusePipeline()
    {}

    std::shared_ptr<Texture> GlTexDiffusePipeline::getTexture() const
    {
        return texture;
    }

	void GlTexDiffusePipeline::bind()
    {
        GlDiffusePipeline::bind();
        glActiveTexture(GL_TEXTURE0);
        texture->bind();
    }
    void GlTexDiffusePipeline::setAttributes()
    {
        glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        setVertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vector3) * 2 + sizeof(Vector2));
		setVertexAttributePointer(1, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vector3) * 2 + sizeof(Vector2), sizeof(Vector3));
        setVertexAttributePointer(2, 2, GL_FLOAT, GL_FALSE,
            sizeof(Vector3) * 2 + sizeof(Vector2), sizeof(Vector3) * 2);
    }
}
