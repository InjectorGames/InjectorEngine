#pragma once
#include "Injector/System.hpp"
#include "Injector/Mathematics/RotateComponent.hpp"
#include "Injector/Mathematics/AttachComponent.hpp"
#include "Injector/Mathematics/TransformComponent.hpp"
#include "Injector/Mathematics/TranslateComponent.hpp"

#include <set>

namespace Injector::Mathematics
{
	using namespace std;

	class TransformSystem : public System
	{
	protected:
		set<shared_ptr<Entity>> transforms;
		set<shared_ptr<Entity>> translates;
		set<shared_ptr<Entity>> rotates;
		set<shared_ptr<Entity>> attaches;
	public:
		virtual ~TransformSystem();

		void update() override;

		size_t getTransformCount() const noexcept;

		bool addTransform(const shared_ptr<Entity>& entity) noexcept;
		bool removeTransform(const shared_ptr<Entity>& entity) noexcept;
		void removeTransforms() noexcept;

		bool addTranslate(const shared_ptr<Entity>& entity) noexcept;
		bool removeTranslate(const shared_ptr<Entity>& entity) noexcept;
		void removeTranslates() noexcept;

		bool addRotate(const shared_ptr<Entity>& entity) noexcept;
		bool removeRotate(const shared_ptr<Entity>& entity) noexcept;
		void removeRotates() noexcept;

		bool addAttach(const shared_ptr<Entity>& entity) noexcept;
		bool removeAttach(const shared_ptr<Entity>& entity) noexcept;
		void removeAttaches() noexcept;
	};
}
