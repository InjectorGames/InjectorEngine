#include "Injector/Mathematics/BoundingBox.hpp"

namespace Injector
{
	BoundingBox::BoundingBox(
		const Vector3& _position,
		const Vector3& _size) :
		position(_position),
		size(_size)
	{
	}

	bool BoundingBox::isColliding(
		const BoundingBox& box) noexcept
	{
		return
			position.x < box.position.x + box.size.x &&
			position.x + size.x > box.position.x &&
			position.y < box.position.y + box.size.y &&
			position.y + size.y > box.position.y &&
			position.z < box.position.z + box.size.z &&
			position.z + size.z > box.position.y;
	}
	bool BoundingBox::isColliding(
		const Vector3& point) noexcept
	{
		// TODO:
		return true;
	}
}
