#include "Injector/Network/ConsoleEcsSystem.hpp"
#include <iostream>

namespace Injector
{
	void ConsoleEcsSystem::inputHandle()
	{
		while (running)
		{
			std::string command;
			std::cin >> command;

			mutex.lock();
			inputCommands.push_back(command);
			mutex.unlock();
		}
	}

	ConsoleEcsSystem::ConsoleEcsSystem(
		const std::map<std::string, std::function<void(
			const std::string&)>>& _commandHandles) noexcept :
		running(true),
		mutex(),
		thread(&ConsoleEcsSystem::inputHandle, this),
		commandHandles(_commandHandles),
		inputCommands()
	{
		thread.detach();
	}
	ConsoleEcsSystem::~ConsoleEcsSystem()
	{
		running = false;
	}

	void ConsoleEcsSystem::update()
	{
		mutex.lock();

		for (auto& inputCommand : inputCommands)
		{
			auto command = inputCommand.substr(
				0, inputCommand.find(' '));

			auto iterator = commandHandles.find(command);

			if(iterator == commandHandles.end())
			{
				std::cout << "Engine: Unknown console command '" <<
					command << "'\n";

				continue;
			}


			if(iterator->second)
				iterator->second(inputCommand);
		}

		inputCommands.clear();
		mutex.unlock();
	}
}
