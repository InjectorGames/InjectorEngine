#pragma once
#include "Injector/Graphics/GpuDrawMode.hpp"
#include "Injector/Exception/Exception.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	static vk::PrimitiveTopology toVkGpuDrawMode(
		GpuDrawMode mode)
	{
		switch(mode)
		{
		case GpuDrawMode::PointList:
			return vk::PrimitiveTopology::ePointList;
		case GpuDrawMode::LineList:
			return vk::PrimitiveTopology::eLineList;
		case GpuDrawMode::LineStrip:
			return vk::PrimitiveTopology::eLineStrip;
		case GpuDrawMode::TriangleList:
			return vk::PrimitiveTopology::eTriangleList;
		case GpuDrawMode::TriangleStrip:
			return vk::PrimitiveTopology::eTriangleStrip;
		case GpuDrawMode::LineListWithAdjacency:
			return vk::PrimitiveTopology::eLineListWithAdjacency;
		case GpuDrawMode::LineStripWithAdjacency:
			return vk::PrimitiveTopology::eLineStripWithAdjacency;
		case GpuDrawMode::TriangleListWithAdjacency:
			return vk::PrimitiveTopology::eTriangleListWithAdjacency;
		case GpuDrawMode::TriangleStripWithAdjacency:
			return vk::PrimitiveTopology::eTriangleStripWithAdjacency;
		case GpuDrawMode::PatchList:
			return vk::PrimitiveTopology::ePatchList;
		default:
			throw Exception(
				"",
				"toVkGpuDrawMode",
				"Unsupported draw mode");
		}
	}
}
