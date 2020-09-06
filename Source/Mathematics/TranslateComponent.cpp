#include "Injector/Mathematics/TranslateComponent.hpp"

namespace Injector::Mathematics
{
	TranslateComponent::TranslateComponent(
		const Vector3& _translation) :
		translation(_translation)
	{}
	TranslateComponent::~TranslateComponent()
	{}
}
