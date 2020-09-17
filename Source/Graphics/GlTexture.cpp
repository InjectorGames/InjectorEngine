#include "Injector/Graphics/GlTexture.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
    GlTexture::GlTexture(
        TextureType type,
        IntVector3 size,
        TextureFormat format,
        TextureFilter minFilter,
        TextureFilter magFilter,
        TextureWrap wrapU,
        TextureWrap wrapV,
        TextureWrap wrapW,
        bool useMipmap,
        const std::shared_ptr<Image>& image) :
        Texture(type, size, format, minFilter, magFilter, 
            wrapU, wrapV, wrapW, useMipmap),
        glType(toGlType(type))
    {
        glGenTextures(GL_ONE, &texture);
        glBindTexture(glType, texture);
        glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, toGlFilter(minFilter, useMipmap));
        glTexParameteri(glType, GL_TEXTURE_MAG_FILTER, toGlFilter(magFilter, false));

        GLenum dataFormat;
        auto channelCount = image->getChannelCount();

        if(channelCount == 1)
            dataFormat = GL_RED;
        else if(channelCount == 2)
            dataFormat = GL_RG;
        else if(channelCount == 3)
            dataFormat = GL_RGB;
        else if(channelCount == 4)
            dataFormat = GL_RGBA;
        else
            throw Exception("GlTexture", "GlTexture", "Unsupported channel count");

        if(type == TextureType::T1D)
        {
            glTexParameteri(glType, GL_TEXTURE_WRAP_S, toGlWrap(wrapU));

            glTexImage1D(glType, 0, toGlFormat(format), size.x, 0,
                dataFormat, GL_UNSIGNED_BYTE, image->getData());
        }
        else if(type == TextureType::T2D)
        {
            glTexParameteri(glType, GL_TEXTURE_WRAP_S, toGlWrap(wrapU));
            glTexParameteri(glType, GL_TEXTURE_WRAP_T, toGlWrap(wrapV));

            glTexImage2D(glType, 0, toGlFormat(format), size.x, size.y, 0, 
                dataFormat, GL_UNSIGNED_BYTE, image->getData());
        }
        else if(type == TextureType::T3D)
        {
            glTexParameteri(glType, GL_TEXTURE_WRAP_S, toGlWrap(wrapU));
            glTexParameteri(glType, GL_TEXTURE_WRAP_T, toGlWrap(wrapV));
            glTexParameteri(glType, GL_TEXTURE_WRAP_R, toGlWrap(wrapW));

            glTexImage3D(glType, 0, toGlFormat(format), size.x, size.y, size.z, 0,
                dataFormat, GL_UNSIGNED_BYTE, image->getData());
        }

        if(useMipmap)
            glGenerateMipmap(glType);
    }
    GlTexture::~GlTexture()
    {
        glDeleteTextures(GL_ONE, &texture);
    }

    GLuint GlTexture::getTexture() const noexcept
	{
        return texture;
	}
	GLenum GlTexture::getGlType() const noexcept
    {
        return glType;
    }

    void GlTexture::bind() noexcept
	{
		glBindTexture(glType, texture);
	}
	void GlTexture::unbind() noexcept
	{
		glBindTexture(glType, GL_ZERO);
	}

    GLenum GlTexture::toGlType(TextureType type)
    {
        if(type == TextureType::T1D)
            return GL_TEXTURE_1D;
        else if(type == TextureType::T2D)
            return GL_TEXTURE_2D;
        else if(type == TextureType::T3D)
            return GL_TEXTURE_3D;
        else
            throw Exception("GlTexture", "toGlType", "Unsupported type");
    }
    GLenum GlTexture::toGlFormat(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::R8:
            return GL_R8;
        case TextureFormat::R8U:
            return GL_R8UI;
        case TextureFormat::R8I:
            return GL_R8I;
        case TextureFormat::RG8:
            return GL_RG8;
        case TextureFormat::RG8U:
            return GL_RG8UI;
        case TextureFormat::RG8I:
            return GL_RG8I;
        case TextureFormat::RGB8:
            return GL_RGB8;
        case TextureFormat::RGB8U:
            return GL_RGB8UI;
        case TextureFormat::RGB8I:
            return GL_RGB8I;
        case TextureFormat::RGBA8:
            return GL_RGBA8;
        case TextureFormat::RGBA8U:
            return GL_RGBA8UI;
        case TextureFormat::RGBA8I:
            return GL_RGBA8I;
        case TextureFormat::R16:
            return GL_R16;
        case TextureFormat::R16U:
            return GL_R16UI;
        case TextureFormat::R16I:
            return GL_R16I;
        case TextureFormat::RG16:
            return GL_RG16;
        case TextureFormat::RG16U:
            return GL_RG16UI;
        case TextureFormat::RG16I:
            return GL_RG16I;
        case TextureFormat::RGB16:
            return GL_RGB16;
        case TextureFormat::RGB16U:
            return GL_RGB16UI;
        case TextureFormat::RGB16I:
            return GL_RGB16I;
        case TextureFormat::RGBA16:
            return GL_RGBA16;
        case TextureFormat::RGBA16U:
            return GL_RGBA16UI;
        case TextureFormat::RGBA16I:
            return GL_RGBA16I;
        case TextureFormat::R32F:
            return GL_R32F;
        case TextureFormat::R32U:
            return GL_R32UI;
        case TextureFormat::R32I:
            return GL_R32I;
        case TextureFormat::RG32F:
            return GL_RG32F;
        case TextureFormat::RG32U:
            return GL_RG32UI;
        case TextureFormat::RG32I:
            return GL_RG32I;
        case TextureFormat::RGB32F:
            return GL_RGB32F;
        case TextureFormat::RGB32U:
            return GL_RGB32UI;
        case TextureFormat::RGB32I:
            return GL_RGB32I;
        case TextureFormat::RGBA32F:
            return GL_RGBA32F;
        case TextureFormat::RGBA32U:
            return GL_RGBA32UI;
        case TextureFormat::RGBA32I:
            return GL_RGBA32I;
        default:
            throw Exception("GlTexture", "toGlFormat", "Unsupported format");
        }
    }
    GLint GlTexture::toGlFilter(TextureFilter filter, bool useMipmap)
    {
        if(filter == TextureFilter::Nearest)
        {
            if(useMipmap)
                return GL_NEAREST_MIPMAP_LINEAR;
            else
                return GL_NEAREST;
        }
        else if(filter == TextureFilter::Linear)
        {
            if(useMipmap)
                return GL_LINEAR_MIPMAP_LINEAR;
            else
                return GL_LINEAR;
        }
        else
        {
            throw Exception("GlTexture", "toGlFilter", "Unsupported filter");
        } 
    }
    GLint GlTexture::toGlWrap(TextureWrap wrap)
    {
        switch (wrap)
        {
        case TextureWrap::Repeat:
            return GL_REPEAT;
        case TextureWrap::MirroredRepeat:
            return GL_MIRRORED_REPEAT;
        case TextureWrap::ClampToEdge:
            return GL_CLAMP_TO_EDGE;
        case TextureWrap::ClampToBorder:
            return GL_CLAMP_TO_BORDER;
        case TextureWrap::MirrorClampToEdge:
            return GL_MIRROR_CLAMP_TO_EDGE;
        default:
            throw Exception("GlTexture", "toGlWrap", "Unsupported wrap");
        }
    }
}
