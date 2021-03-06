#pragma once
#include "Injector/Graphics/GpuBufferType.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/GlfwDefines.hpp"

namespace Injector
{
	static GLenum toGlGpuBufferType(
		GpuBufferType type)
	{
		switch (type)
		{
		case GpuBufferType::Uniform:
			return GL_UNIFORM_BUFFER;
		case GpuBufferType::Index:
			return GL_ELEMENT_ARRAY_BUFFER;
		case GpuBufferType::Vertex:
			return GL_ARRAY_BUFFER;
		case GpuBufferType::TransformFeedback:
			return GL_TRANSFORM_FEEDBACK_BUFFER;
		default:
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported buffer type");
		}
	}
}
