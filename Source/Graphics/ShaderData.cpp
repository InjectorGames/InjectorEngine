#include "Injector/Graphics/ShaderData.hpp"

namespace Injector
{
	ShaderData::ShaderData() :
		code()
	{
	}
	ShaderData::ShaderData(
		const std::vector<uint8_t>& _code) :
		code(_code)
	{
	}
	ShaderData::~ShaderData()
	{
	}
}
