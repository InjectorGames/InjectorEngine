#pragma once
#include "Injector/ECS/System.hpp"

#include <map>
#include <mutex>
#include <vector>
#include <thread>

namespace Injector
{
	class ConsoleSystem : public System
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
		ConsoleSystem(
			const std::map<std::string, std::function<void(
				const std::string&)>>& commandHandles) noexcept;
		~ConsoleSystem() override;
		ConsoleSystem(const ConsoleSystem&) = delete;

		void update() override;
	};
}
