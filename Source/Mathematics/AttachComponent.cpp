#include "Injector/Mathematics/AttachComponent.hpp"

namespace Injector::Mathematics
{
	AttachComponent::AttachComponent(
		const shared_ptr<Entity>& _target) :
		target(_target)
	{}
	AttachComponent::~AttachComponent()
	{}
}
