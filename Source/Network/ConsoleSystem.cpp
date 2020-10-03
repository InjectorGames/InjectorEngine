#include "Injector/Network/ConsoleSystem.hpp"
#include <iostream>

namespace Injector
{
	void ConsoleSystem::inputHandle()
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

	ConsoleSystem::ConsoleSystem(
		const std::map<std::string, std::function<void(
			const std::string&)>>& _commandHandles) noexcept :
		running(true),
		mutex(),
		thread(&ConsoleSystem::inputHandle, this),
		commandHandles(_commandHandles),
		inputCommands()
	{
		thread.detach();
	}
	ConsoleSystem::~ConsoleSystem()
	{
		running = false;
	}

	void ConsoleSystem::update()
	{
		mutex.lock();

		for (auto& inputCommand : inputCommands)
		{
			auto command = inputCommand.substr(
				0, inputCommand.find(' '));

			auto iterator = commandHandles.find(command);

			if(iterator == commandHandles.end())
			{
				std::cout << "Unknown console command: " <<
					command << "\n";

				continue;
			}


			if(iterator->second)
				iterator->second(inputCommand);
		}

		inputCommands.clear();
		mutex.unlock();
	}
}
