#pragma once
#include "Injector/Graphics/Texture.hpp"
#include "Injector/Graphics/Image.hpp"

#include "GL/glew.h"

namespace Injector
{
    class GlTexture : public Texture
    {
    protected:
        GLuint texture;
        GLenum glType;
    public:
        GlTexture(TextureType type,
            IntVector3 size,
            TextureFormat format,
            TextureFilter minFilter,
            TextureFilter magFilter,
            TextureWrap wrapU,
            TextureWrap wrapV,
            TextureWrap wrapW,
            bool useMipmap,
            const std::shared_ptr<Image>& image);
        virtual ~GlTexture();

        GLuint getTexture() const noexcept;
		GLenum getGlType() const noexcept;

        void bind() noexcept;
	    void unbind() noexcept;

        static GLenum toGlType(TextureType type);
        static GLenum toGlFormat(TextureFormat format);
        static GLint toGlFilter(TextureFilter filter, bool useMipmap);
        static GLint toGlWrap(TextureWrap wrap);
    };
}
