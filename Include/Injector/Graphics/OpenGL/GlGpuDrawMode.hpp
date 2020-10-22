#pragma once
#include "Injector/Graphics/GpuDrawMode.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	static GLenum toGlGpuDrawMode(
		GpuDrawMode mode)
	{
		switch(mode)
		{
		case GpuDrawMode::PointList:
			return GL_POINTS;
		case GpuDrawMode::LineList:
			return GL_LINES;
		case GpuDrawMode::LineStrip:
			return GL_LINE_STRIP;
		case GpuDrawMode::TriangleList:
			return GL_TRIANGLES;
		case GpuDrawMode::TriangleStrip:
			return GL_TRIANGLE_STRIP;
		default:
			throw Exception(
				"",
				"toGlGpuDrawMode",
				"Unsupported draw mode");
		}
	}
}
