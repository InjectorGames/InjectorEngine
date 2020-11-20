#include "Injector/Graphics/OpenGL/GlGpuImage.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Graphics/OpenGL/GlGpuImageType.hpp"
#include "Injector/Graphics/OpenGL/GlGpuImageFormat.hpp"

namespace Injector
{
	GlGpuImage::GlGpuImage(
		GpuImageType type,
		GpuImageFormat format,
		const SizeVector3& size,
		bool useMipmap,
		const void* data) :
		GpuImage(
			type,
			format,
			size,
			useMipmap),
		glType(toGlGpuImageType(type))
	{
		glGenTextures(
			GL_ONE,
			&texture);

		glBindTexture(
			glType,
			texture);

		GLenum dataFormat;
		GLenum dataType;

		switch (format)
		{
		case GpuImageFormat::R8UNORM:
			dataFormat = GL_RED;
			dataType = GL_UNSIGNED_BYTE;
			break;
		case GpuImageFormat::R8SNORM:
			dataFormat = GL_RED;
			dataType = GL_BYTE;
			break;
		case GpuImageFormat::R8UINT:
			dataFormat = GL_RED_INTEGER;
			dataType = GL_UNSIGNED_BYTE;
			break;
		case GpuImageFormat::R8SINT:
			dataFormat = GL_RED_INTEGER;
			dataType = GL_BYTE;
			break;
		case GpuImageFormat::R8G8UNORM:
			dataFormat = GL_RG;
			dataType = GL_UNSIGNED_BYTE;
			break;
		case GpuImageFormat::R8G8SNORM:
			dataFormat = GL_RG;
			dataType = GL_BYTE;
			break;
		case GpuImageFormat::R8G8UINT:
			dataFormat = GL_RG_INTEGER;
			dataType = GL_UNSIGNED_BYTE;
			break;
		case GpuImageFormat::R8G8SINT:
			dataFormat = GL_RG_INTEGER;
			dataType = GL_BYTE;
			break;
		case GpuImageFormat::R8G8B8SRGB:
		case GpuImageFormat::R8G8B8UNORM:
			dataFormat = GL_RGB;
			dataType = GL_UNSIGNED_BYTE;
			break;
		case GpuImageFormat::R8G8B8SNORM:
			dataFormat = GL_RGB;
			dataType = GL_BYTE;
			break;
		case GpuImageFormat::R8G8B8UINT:
			dataFormat = GL_RGB_INTEGER;
			dataType = GL_UNSIGNED_BYTE;
			break;
		case GpuImageFormat::R8G8B8SINT:
			dataFormat = GL_RGB_INTEGER;
			dataType = GL_BYTE;
			break;
		case GpuImageFormat::R8G8B8A8SRGB:
		case GpuImageFormat::R8G8B8A8UNORM:
			dataFormat = GL_RGBA;
			dataType = GL_UNSIGNED_BYTE;
			break;
		case GpuImageFormat::R8G8B8A8SNORM:
			dataFormat = GL_RGBA;
			dataType = GL_BYTE;
			break;
		case GpuImageFormat::R8G8B8A8UINT:
			dataFormat = GL_RGBA_INTEGER;
			dataType = GL_UNSIGNED_BYTE;
			break;
		case GpuImageFormat::R8G8B8A8SINT:
			dataFormat = GL_RGBA_INTEGER;
			dataType = GL_BYTE;
			break;
		case GpuImageFormat::R16SFLOAT:
			dataFormat = GL_RED;
			dataType = GL_HALF_FLOAT;
			break;
		case GpuImageFormat::R16UINT:
			dataFormat = GL_RED_INTEGER;
			dataType = GL_UNSIGNED_SHORT;
			break;
		case GpuImageFormat::R16SINT:
			dataFormat = GL_RED_INTEGER;
			dataType = GL_SHORT;
			break;
		case GpuImageFormat::R16G16SFLOAT:
			dataFormat = GL_RG;
			dataType = GL_HALF_FLOAT;
			break;
		case GpuImageFormat::R16G16UINT:
			dataFormat = GL_RG_INTEGER;
			dataType = GL_UNSIGNED_SHORT;
			break;
		case GpuImageFormat::R16G16SINT:
			dataFormat = GL_RG_INTEGER;
			dataType = GL_SHORT;
			break;
		case GpuImageFormat::R16G16B16SFLOAT:
			dataFormat = GL_RGB;
			dataType = GL_HALF_FLOAT;
			break;
		case GpuImageFormat::R16G16B16UINT:
			dataFormat = GL_RGB_INTEGER;
			dataType = GL_UNSIGNED_SHORT;
			break;
		case GpuImageFormat::R16G16B16SINT:
			dataFormat = GL_RGB_INTEGER;
			dataType = GL_SHORT;
			break;
		case GpuImageFormat::R16G16B16A16SFLOAT:
			dataFormat = GL_RGBA;
			dataType = GL_HALF_FLOAT;
			break;
		case GpuImageFormat::R16G16B16A16UINT:
			dataFormat = GL_RGBA_INTEGER;
			dataType = GL_UNSIGNED_SHORT;
			break;
		case GpuImageFormat::R16G16B16A16SINT:
			dataFormat = GL_RGBA_INTEGER;
			dataType = GL_SHORT;
			break;
		case GpuImageFormat::R32SFLOAT:
			dataFormat = GL_RED;
			dataType = GL_FLOAT;
			break;
		case GpuImageFormat::R32UINT:
			dataFormat = GL_RED_INTEGER;
			dataType = GL_UNSIGNED_INT;
			break;
		case GpuImageFormat::R32SINT:
			dataFormat = GL_RED_INTEGER;
			dataType = GL_INT;
			break;
		case GpuImageFormat::R32G32SFLOAT:
			dataFormat = GL_RG;
			dataType = GL_FLOAT;
			break;
		case GpuImageFormat::R32G32UINT:
			dataFormat = GL_RG_INTEGER;
			dataType = GL_UNSIGNED_INT;
			break;
		case GpuImageFormat::R32G32SINT:
			dataFormat = GL_RG_INTEGER;
			dataType = GL_INT;
			break;
		case GpuImageFormat::R32G32B32SFLOAT:
			dataFormat = GL_RGB;
			dataType = GL_FLOAT;
			break;
		case GpuImageFormat::R32G32B32UINT:
			dataFormat = GL_RGB_INTEGER;
			dataType = GL_UNSIGNED_INT;
			break;
		case GpuImageFormat::R32G32B32SINT:
			dataFormat = GL_RGB_INTEGER;
			dataType = GL_INT;
			break;
		case GpuImageFormat::R32G32B32A32SFLOAT:
			dataFormat = GL_RGBA;
			dataType = GL_FLOAT;
			break;
		case GpuImageFormat::R32G32B32A32UINT:
			dataFormat = GL_RGBA_INTEGER;
			dataType = GL_UNSIGNED_INT;
			break;
		case GpuImageFormat::R32G32B32A32SINT:
			dataFormat = GL_RGBA_INTEGER;
			dataType = GL_INT;
			break;
		case GpuImageFormat::D16:
			dataFormat = GL_DEPTH_COMPONENT;
			dataType = GL_UNSIGNED_SHORT;
			break;
		case GpuImageFormat::D32:
			dataFormat = GL_DEPTH_COMPONENT;
			dataType = GL_FLOAT;
			break;
		case GpuImageFormat::D24S8:
			dataFormat = GL_DEPTH_STENCIL;
			dataType = GL_UNSIGNED_SHORT;
			break;
		case GpuImageFormat::D32S8:
			dataFormat = GL_DEPTH_STENCIL;
			dataType = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
			break;
		default:
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported null image format");
		};

		if (type == GpuImageType::Image1D)
		{
			glTexImage1D(
				glType,
				0,
				toGlGpuImageFormat(format),
				static_cast<GLsizei>(size.x),
				0,
				dataFormat,
				dataType,
				data);
		}
		else if (type == GpuImageType::Image2D)
		{
			glTexImage2D(
				glType,
				0,
				toGlGpuImageFormat(format),
				static_cast<GLsizei>(size.x),
				static_cast<GLsizei>(size.y),
				0,
				dataFormat,
				dataType,
				data);
		}
		else if (type == GpuImageType::Image3D)
		{
			glTexImage3D(
				glType,
				0,
				toGlGpuImageFormat(format),
				static_cast<GLsizei>(size.x),
				static_cast<GLsizei>(size.y),
				static_cast<GLsizei>(size.z),
				0,
				dataFormat,
				dataType,
				data);
		}
		else
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported image type");
		}

		if (useMipmap)
			glGenerateMipmap(glType);

		glBindTexture(
			glType,
			GL_ZERO);
	}
	GlGpuImage::~GlGpuImage()
	{
		glDeleteTextures(
			GL_ONE,
			&texture);
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
		glBindTexture(
			glType,
			texture);
	}
	void GlGpuImage::unbind() noexcept
	{
		glBindTexture(
			glType,
			GL_ZERO);
	}
}
