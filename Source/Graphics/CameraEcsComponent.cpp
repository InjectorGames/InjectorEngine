#include "Injector/Graphics/CameraEcsComponent.hpp"

namespace Injector
{
	CameraEcsComponent::CameraEcsComponent(
		int _queue,
		CameraType _type,
		float _fieldOfView,
		const FloatVector4& _frustum,
		const FloatVector2& _clipPlane,
		float _aspectRatio,
		bool _render,
		const FloatMatrix4& _matrix,
		const std::set<std::shared_ptr<EcsEntity>>& _renders) noexcept :
		renderQueue(_queue),
		type(_type),
		fieldOfView(_fieldOfView),
		frustum(_frustum),
		clipPlane(_clipPlane),
		aspectRatio(_aspectRatio),
		render(_render),
		matrix(_matrix),
		renders(_renders)
	{
	}
}
