#pragma once
#include "Injector/Graphics/GpuImageWrap.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	static GLint toGlGpuImageWrap(
		GpuImageWrap wrap)
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
				THIS_FUNCTION_NAME,
				"Unsupported image wrap");
		}
	}
}
