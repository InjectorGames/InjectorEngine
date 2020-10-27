#pragma once
#include "Injector/ECS/EcsSystem.hpp"

#include <map>
#include <mutex>
#include <vector>
#include <thread>
#include <functional>

namespace Injector
{
	class ConsoleEcsSystem : public EcsSystem
	{
	 protected:
		bool running;
		std::mutex mutex;
		std::thread thread;

		std::map<std::string, std::function<void(
			const std::string&)>> commandHandles;
		std::vector<std::string> inputCommands;

		void inputHandle();
	 public:
		explicit ConsoleEcsSystem(
			const std::map<std::string, std::function<void(
				const std::string&)>>& commandHandles) noexcept;
		~ConsoleEcsSystem() override;

		void update() override;
	};
}
