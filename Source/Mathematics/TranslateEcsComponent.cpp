#include "Injector/Mathematics/TranslateEcsComponent.hpp"

namespace Injector
{
	TranslateEcsComponent::TranslateEcsComponent(
		const Vector3& _translation) noexcept :
		translation(_translation)
	{
	}
}
