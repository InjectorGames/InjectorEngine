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
		const std::shared_ptr<ImageData>& imageData) :
		GpuImage(
			type,
			format,
			size,
			useMipmap),
		glType(toGlGpuImageType(type))
	{
		if(size.x < 1 || size.y < 1 || size.z < 1)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Size x/y/z is less than one");
		}

		glGenTextures(GL_ONE, &texture);
		glBindTexture(glType, texture);

		GLenum dataFormat;
		GLenum dataType;
		void* data;

		if(imageData)
		{
			if (imageData->componentCount == 1)
			{
				dataFormat = GL_RED;
			}
			else if (imageData->componentCount == 2)
			{
				dataFormat = GL_RG;
			}
			else if (imageData->componentCount == 3)
			{
				dataFormat = GL_RGB;
			}
			else if (imageData->componentCount == 4)
			{
				dataFormat = GL_RGBA;
			}
			else
			{
				throw Exception(
					THIS_FUNCTION_NAME,
					"Unsupported image format");
			}

			if (imageData->component16)
				dataType = GL_UNSIGNED_SHORT;
			else
				dataType = GL_UNSIGNED_BYTE;

			data = imageData->pixels.data();
		}
		else
		{
			// TODO: better look
			switch (format)
			{
			case GpuImageFormat::R8:
				dataFormat = GL_RED;
				dataType = GL_UNSIGNED_BYTE;
				break;
			case GpuImageFormat::RG8:
				dataFormat = GL_RG;
				dataType = GL_UNSIGNED_BYTE;
				break;
			case GpuImageFormat::RGB8:
				dataFormat = GL_RGB;
				dataType = GL_UNSIGNED_BYTE;
				break;
			case GpuImageFormat::RGBA8:
				dataFormat = GL_RGBA;
				dataType = GL_UNSIGNED_BYTE;
				break;
			case GpuImageFormat::D24S8:
				dataFormat = GL_DEPTH_STENCIL;
				dataType = GL_UNSIGNED_INT_24_8;
				break;
			default:
				throw Exception(
					THIS_FUNCTION_NAME,
					"Unsupported null image format");
			};

			data = nullptr;
		}

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
}
