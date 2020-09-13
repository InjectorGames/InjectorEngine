#include "Injector/Graphics/GlColColorPipeline.hpp"

namespace Injector
{
    GlColColorPipeline::GlColColorPipeline(
        bool gles,
		const Vector4& color) :
        GlColorPipeline(gles, color)
    {}
	GlColColorPipeline::~GlColColorPipeline()
    {}

	void GlColColorPipeline::setAttributes()
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
			static_cast<GLsizei>(sizeof(Vector3) + sizeof(Vector4)),
            reinterpret_cast<const GLvoid*>(0));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 
			static_cast<GLsizei>(sizeof(Vector3) + sizeof(Vector4)),
            reinterpret_cast<const GLvoid*>(sizeof(Vector3)));
    }
}
