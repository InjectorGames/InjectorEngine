#include "Injector/Mathematics/AttachComponent.hpp"

namespace Injector
{
	AttachComponent::AttachComponent(
		const std::shared_ptr<Entity>& _target) :
		target(_target)
	{}
	AttachComponent::~AttachComponent()
	{}
}
