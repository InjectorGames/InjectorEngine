#include "Injector/Mathematics/TranslateEcsComponent.hpp"

namespace Injector
{
	TranslateEcsComponent::TranslateEcsComponent(
		const FloatVector3& _translation) noexcept :
		translation(_translation)
	{
	}
}
