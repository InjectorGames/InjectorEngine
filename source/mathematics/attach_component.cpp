#include <injector/mathematics/attach_component.hpp>

namespace INJECTOR_NAMESPACE
{
	AttachComponent::AttachComponent(
		const EntityHandle& _target) :
		target(_target)
	{}
	AttachComponent::~AttachComponent()
	{}
}
