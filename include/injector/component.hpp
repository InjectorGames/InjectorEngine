#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	template<class T>
	struct Component
	{
		T value;

		Component(const T& _value) :
			value(_value)
		{}
	};
}
