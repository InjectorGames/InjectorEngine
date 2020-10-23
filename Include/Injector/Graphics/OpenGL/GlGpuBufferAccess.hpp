#pragma once
#include "Injector/Graphics/GpuBufferAccess.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	static GLbitfield toGlGpuBufferAccess(GpuBufferAccess access)
	{
		if (access == GpuBufferAccess::ReadOnly)
		{
			return GL_MAP_READ_BIT;
		}
		else if (access == GpuBufferAccess::WriteOnly)
		{
			//TODO: Check if this correct
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
				"",
				"toGlGpuBufferAccess",
				"Unsupported buffer access");
		}
	}
}