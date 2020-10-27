#pragma once
#include "Injector/Graphics/GpuShaderStage.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	static GLenum toGlGpuShaderStage(
		GpuShaderStage stage)
	{
		switch (stage)
		{
		case GpuShaderStage::Vertex:
			return GL_VERTEX_SHADER;
		case GpuShaderStage::Geometry:
			return GL_GEOMETRY_SHADER;
		case GpuShaderStage::Fragment:
			return GL_FRAGMENT_SHADER;
		case GpuShaderStage::Compute:
			return GL_COMPUTE_SHADER;
		default:
			throw Exception(
				"",
				std::string(__func__),
				std::to_string(__LINE__),
				"Unsupported shader stage");
		}
	}
}
