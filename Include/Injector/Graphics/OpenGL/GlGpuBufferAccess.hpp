#pragma once
#include "Injector/Graphics/GpuBufferAccess.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/GlfwDefines.hpp"

namespace Injector
{
	// Returns OpenGL GPU buffer access
	static GLbitfield toGlGpuBufferAccess(GpuBufferAccess access)
	{
		if (access == GpuBufferAccess::ReadOnly)
		{
			return GL_MAP_READ_BIT;
		}
		else if (access == GpuBufferAccess::WriteOnly)
		{
			return GL_MAP_WRITE_BIT |
				   GL_MAP_FLUSH_EXPLICIT_BIT |
				   GL_MAP_INVALIDATE_RANGE_BIT;
		}
		else if (access == GpuBufferAccess::ReadWrite)
		{
			return GL_MAP_READ_BIT |
				   GL_MAP_WRITE_BIT |
				   GL_MAP_FLUSH_EXPLICIT_BIT;
		}
		else
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported buffer access");
		}
	}
}
