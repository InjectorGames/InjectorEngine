#include <injector/graphics/camera_component.hpp>

namespace INJECTOR_NAMESPACE
{
	CameraComponent::CameraComponent(
		int _queue,
		Type _type,
		float _aspectRatio,
		bool _updateAspect,
		float _fieldOfView,
		const Vector4& _frustum,
		const Vector2& _clipPlane,
		const Matrix4& _matrix,
		bool _changed,
		bool _render,
		const std::set<EntityHandle>& _renders) :
		queue(_queue),
		type(_type),
		aspectRatio(_aspectRatio),
		updateAspect(_updateAspect),
		fieldOfView(_fieldOfView),
		frustum(_frustum),
		clipPlane(_clipPlane),
		matrix(_matrix),
		changed(_changed),
		render(_render),
		renders(_renders)
	{}
	CameraComponent::~CameraComponent()
	{}
}
