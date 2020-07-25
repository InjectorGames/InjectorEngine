#include <injector/camera_component.hpp>

namespace INJECTOR_NAMESPACE
{
	CameraComponent::CameraComponent(
		int _queue,
		Type _type,
		float _aspectRatio,
		float _fieldOfView,
		const Vector4& _frustum,
		const Vector2& _clipPlane,
		const Matrix4& _matrix,
		bool _changed) :
		queue(_queue),
		type(_type),
		aspectRatio(_aspectRatio),
		fieldOfView(_fieldOfView),
		frustum(_frustum),
		clipPlane(_clipPlane),
		matrix(_matrix),
		changed(_changed)
	{}
}
