#include "Injector/Graphics/OpenGL/GlGpuFramebuffer.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	GlGpuFramebuffer::GlGpuFramebuffer(
		const std::shared_ptr<GlGpuImage>& colorImage,
		const std::shared_ptr<GlGpuImage>& depthImage,
		const std::shared_ptr<GlGpuImage>& stencilImage) :
		GpuFramebuffer(colorImage, depthImage, stencilImage)
	{
		glGenFramebuffers(GL_ONE, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		if(colorImage->getType() == GpuImageType::Image1D)
		{
			glFramebufferTexture1D(
				GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				colorImage->getGlType(),
				colorImage->getTexture(),
				0);
		}
		else if(colorImage->getType() == GpuImageType::Image2D)
		{
			glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				colorImage->getGlType(),
				colorImage->getTexture(),
				0);
		}
		else if(colorImage->getType() == GpuImageType::Image3D)
		{
			glFramebufferTexture3D(
				GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				colorImage->getGlType(),
				colorImage->getTexture(),
				0,
				0);
		}
		else
		{
			throw Exception(
				"GlGpuFramebuffer",
				"GlGpuFramebuffer",
				"Unsupported color image type");
		}

		if(depthImage)
		{
			if (depthImage == stencilImage)
			{
				if (depthImage->getType() == GpuImageType::Image1D)
				{
					glFramebufferTexture1D(
						GL_FRAMEBUFFER,
						GL_DEPTH_STENCIL_ATTACHMENT,
						depthImage->getGlType(),
						depthImage->getTexture(),
						0);
				}
				else if (depthImage->getType() == GpuImageType::Image2D)
				{
					glFramebufferTexture2D(
						GL_FRAMEBUFFER,
						GL_DEPTH_STENCIL_ATTACHMENT,
						depthImage->getGlType(),
						depthImage->getTexture(),
						0);
				}
				else if (depthImage->getType() == GpuImageType::Image3D)
				{
					glFramebufferTexture3D(
						GL_FRAMEBUFFER,
						GL_DEPTH_STENCIL_ATTACHMENT,
						depthImage->getGlType(),
						depthImage->getTexture(),
						0,
						0);
				}
				else
				{
					throw Exception(
						"GlGpuFramebuffer",
						"GlGpuFramebuffer",
						"Unsupported depth stencil image type");
				}
			}
			else
			{
				if (depthImage->getType() == GpuImageType::Image1D)
				{
					glFramebufferTexture1D(
						GL_FRAMEBUFFER,
						GL_DEPTH_ATTACHMENT,
						depthImage->getGlType(),
						depthImage->getTexture(),
						0);
				}
				else if (depthImage->getType() == GpuImageType::Image2D)
				{
					glFramebufferTexture2D(
						GL_FRAMEBUFFER,
						GL_DEPTH_ATTACHMENT,
						depthImage->getGlType(),
						depthImage->getTexture(),
						0);
				}
				else if (depthImage->getType() == GpuImageType::Image3D)
				{
					glFramebufferTexture3D(
						GL_FRAMEBUFFER,
						GL_DEPTH_ATTACHMENT,
						depthImage->getGlType(),
						depthImage->getTexture(),
						0,
						0);
				}
				else
				{
					throw Exception(
						"GlGpuFramebuffer",
						"GlGpuFramebuffer",
						"Unsupported depth image type");
				}
			}
		}

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, GL_ZERO);

			throw Exception(
				"GlGpuFramebuffer",
				"GlGpuFramebuffer",
				"Framebuffer is not complete");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, GL_ZERO);
	}
	GlGpuFramebuffer::~GlGpuFramebuffer()
	{
		glDeleteFramebuffers(GL_ONE, &framebuffer);
	}

	GLuint GlGpuFramebuffer::getFramebuffer() const noexcept
	{
		return framebuffer;
	}

	void GlGpuFramebuffer::bind() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	}
	void GlGpuFramebuffer::unbind() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, GL_ZERO);
	}
}
