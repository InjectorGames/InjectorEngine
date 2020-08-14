#pragma once
#include <injector/defines.hpp>
#include <memory>

namespace INJECTOR_NAMESPACE
{
	class Pipeline
	{
	public:
		Pipeline();
		virtual ~Pipeline();
	};

	using PipelineHandle = std::shared_ptr<Pipeline>;
}
