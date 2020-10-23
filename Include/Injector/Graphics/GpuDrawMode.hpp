#pragma once

namespace Injector
{
	enum class GpuDrawMode
	{
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip,
		LineListWithAdjacency,
		LineStripWithAdjacency,
		TriangleListWithAdjacency,
		TriangleStripWithAdjacency,
		PatchList,
	};
}
