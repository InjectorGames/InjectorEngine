#include "Injector/Graphics/GlGpuImage.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlGpuImage::GlGpuImage(
		GpuImageType type,
		IntVector3 size,
		GpuImageFormat format,
		GpuImageFilter minFilter,
		GpuImageFilter magFilter,
		GpuImageWrap wrapU,
		GpuImageWrap wrapV,
		GpuImageWrap wrapW,
		bool useMipmap,
		const std::shared_ptr<ImageData>& data) :
		GpuImage(type, size, format, minFilter, magFilter,
			wrapU, wrapV, wrapW, useMipmap),
		glType(toGlType(type))
	{
		if (!data)
		{
			throw NullException(
				"GlGpuImage",
				"GlGpuImage",
				"data");
		}

		glGenTextures(GL_ONE, &texture);
		glBindTexture(glType, texture);

		glTexParameteri(
			glType,
			GL_TEXTURE_MIN_FILTER,
			toGlFilter(minFilter, useMipmap));
		glTexParameteri(
			glType,
			GL_TEXTURE_MAG_FILTER,
			toGlFilter(magFilter, false));

		GLenum dataFormat;

		if (data->componentCount == 1)
		{
			dataFormat = GL_RED;
		}
		else if (data->componentCount == 2)
		{
			dataFormat = GL_RG;
		}
		else if (data->componentCount == 3)
		{
			dataFormat = GL_RGB;
		}
		else if (data->componentCount == 4)
		{
			dataFormat = GL_RGBA;
		}
		else
		{
			throw Exception(
				"GlGpuImage",
				"GlGpuImage",
				"Unsupported image format");
		}

		GLenum dataType;

		if (data->component16)
			dataType = GL_UNSIGNED_SHORT;
		else
			dataType = GL_UNSIGNED_BYTE;

		if (type == GpuImageType::Image1D)
		{
			glTexParameteri(
				glType,
				GL_TEXTURE_WRAP_S,
				toGlWrap(wrapU));

			glTexImage1D(
				glType,
				0,
				toGlFormat(format),
				size.x,
				0,
				dataFormat,
				dataType,
				data->pixels.data());
		}
		else if (type == GpuImageType::Image2D)
		{
			glTexParameteri(
				glType,
				GL_TEXTURE_WRAP_S,
				toGlWrap(wrapU));
			glTexParameteri(
				glType,
				GL_TEXTURE_WRAP_T,
				toGlWrap(wrapV));

			glTexImage2D(
				glType,
				0,
				toGlFormat(format),
				size.x,
				size.y,
				0,
				dataFormat,
				dataType,
				data->pixels.data());
		}
		else if (type == GpuImageType::Image3D)
		{
			glTexParameteri(
				glType,
				GL_TEXTURE_WRAP_S,
				toGlWrap(wrapU));
			glTexParameteri(
				glType,
				GL_TEXTURE_WRAP_T,
				toGlWrap(wrapV));
			glTexParameteri(
				glType,
				GL_TEXTURE_WRAP_R,
				toGlWrap(wrapW));

			glTexImage3D(
				glType,
				0,
				toGlFormat(format),
				size.x,
				size.y,
				size.z,
				0,
				dataFormat,
				dataType,
				data->pixels.data());
		}

		if (useMipmap)
			glGenerateMipmap(glType);
	}
	GlGpuImage::~GlGpuImage()
	{
		glDeleteTextures(GL_ONE, &texture);
	}

	GLuint GlGpuImage::getTexture() const noexcept
	{
		return texture;
	}
	GLenum GlGpuImage::getGlType() const noexcept
	{
		return glType;
	}

	void GlGpuImage::bind() noexcept
	{
		glBindTexture(glType, texture);
	}
	void GlGpuImage::unbind() noexcept
	{
		glBindTexture(glType, GL_ZERO);
	}

	GLenum GlGpuImage::toGlType(GpuImageType type)
	{
		if (type == GpuImageType::Image1D)
		{
			return GL_TEXTURE_1D;
		}
		else if (type == GpuImageType::Image2D)
		{
			return GL_TEXTURE_2D;
		}
		else if (type == GpuImageType::Image3D)
		{
			return GL_TEXTURE_3D;
		}
		else
		{
			throw Exception(
				"GlGpuImage",
				"toGlType",
				"Unsupported type");
		}
	}
	GLenum GlGpuImage::toGlFormat(GpuImageFormat format)
	{
		switch (format)
		{
		case GpuImageFormat::R8:
			return GL_R8;
		case GpuImageFormat::R8U:
			return GL_R8UI;
		case GpuImageFormat::R8I:
			return GL_R8I;
		case GpuImageFormat::RG8:
			return GL_RG8;
		case GpuImageFormat::RG8U:
			return GL_RG8UI;
		case GpuImageFormat::RG8I:
			return GL_RG8I;
		case GpuImageFormat::RGB8:
			return GL_RGB8;
		case GpuImageFormat::RGB8U:
			return GL_RGB8UI;
		case GpuImageFormat::RGB8I:
			return GL_RGB8I;
		case GpuImageFormat::RGBA8:
			return GL_RGBA8;
		case GpuImageFormat::RGBA8U:
			return GL_RGBA8UI;
		case GpuImageFormat::RGBA8I:
			return GL_RGBA8I;
		case GpuImageFormat::R16:
			return GL_R16;
		case GpuImageFormat::R16U:
			return GL_R16UI;
		case GpuImageFormat::R16I:
			return GL_R16I;
		case GpuImageFormat::RG16:
			return GL_RG16;
		case GpuImageFormat::RG16U:
			return GL_RG16UI;
		case GpuImageFormat::RG16I:
			return GL_RG16I;
		case GpuImageFormat::RGB16:
			return GL_RGB16;
		case GpuImageFormat::RGB16U:
			return GL_RGB16UI;
		case GpuImageFormat::RGB16I:
			return GL_RGB16I;
		case GpuImageFormat::RGBA16:
			return GL_RGBA16;
		case GpuImageFormat::RGBA16U:
			return GL_RGBA16UI;
		case GpuImageFormat::RGBA16I:
			return GL_RGBA16I;
		case GpuImageFormat::R32F:
			return GL_R32F;
		case GpuImageFormat::R32U:
			return GL_R32UI;
		case GpuImageFormat::R32I:
			return GL_R32I;
		case GpuImageFormat::RG32F:
			return GL_RG32F;
		case GpuImageFormat::RG32U:
			return GL_RG32UI;
		case GpuImageFormat::RG32I:
			return GL_RG32I;
		case GpuImageFormat::RGB32F:
			return GL_RGB32F;
		case GpuImageFormat::RGB32U:
			return GL_RGB32UI;
		case GpuImageFormat::RGB32I:
			return GL_RGB32I;
		case GpuImageFormat::RGBA32F:
			return GL_RGBA32F;
		case GpuImageFormat::RGBA32U:
			return GL_RGBA32UI;
		case GpuImageFormat::RGBA32I:
			return GL_RGBA32I;
		default:
			throw Exception(
				"GlGpuImage",
				"toGlFormat",
				"Unsupported format");
		}
	}
	GLint GlGpuImage::toGlFilter(GpuImageFilter filter, bool useMipmap)
	{
		if (filter == GpuImageFilter::Nearest)
		{
			if (useMipmap)
				return GL_NEAREST_MIPMAP_LINEAR;
			else
				return GL_NEAREST;
		}
		else if (filter == GpuImageFilter::Linear)
		{
			if (useMipmap)
				return GL_LINEAR_MIPMAP_LINEAR;
			else
				return GL_LINEAR;
		}
		else
		{
			throw Exception(
				"GlGpuImage",
				"toGlFilter",
				"Unsupported filter");
		}
	}
	GLint GlGpuImage::toGlWrap(GpuImageWrap wrap)
	{
		switch (wrap)
		{
		case GpuImageWrap::Repeat:
			return GL_REPEAT;
		case GpuImageWrap::MirroredRepeat:
			return GL_MIRRORED_REPEAT;
		case GpuImageWrap::ClampToEdge:
			return GL_CLAMP_TO_EDGE;
		case GpuImageWrap::ClampToBorder:
			return GL_CLAMP_TO_BORDER;
		case GpuImageWrap::MirrorClampToEdge:
			return GL_MIRROR_CLAMP_TO_EDGE;
		default:
			throw Exception(
				"GlGpuImage",
				"toGlWrap",
				"Unsupported wrap");
		}
	}
}
