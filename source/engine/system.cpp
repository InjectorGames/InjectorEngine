#include <injector_engine/engine.hpp>

namespace InjectorEngine
{
	bool System::Comparator::operator()(const System& a, const System& b) const
	{
		return a.updateQueue < b.updateQueue;
	}
	bool System::Comparator::operator()(const System* a, const System* b) const
	{
		return a->updateQueue < b->updateQueue;
	}

	System::System(int _updateQueue) : updateQueue(_updateQueue) {}

	void System::OnUpdateBegin(Window* window) {}
	void System::OnUpdate(Window* window) {}
	void System::OnUpdateEnd(Window* window) {}
}
