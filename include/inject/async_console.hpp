#pragma once
#include <queue>
#include <mutex>
#include <thread>
#include <string>
#include <iostream>

namespace inject
{
	class AsyncConsole
	{
	protected:
		bool isRunning;
		std::mutex mutex;
		std::thread thread;
		std::queue<std::string> commands;

		inline void handleInput()
		{
			while (isRunning)
			{
				std::string command;
				std::cin >> command;

				mutex.lock();
				commands.push(command);
				mutex.unlock();
			}
		}
	public:
		AsyncConsole() :
			isRunning(true),
			mutex(),
			commands()
		{
			thread = std::thread(&AsyncConsole::handleInput, this);
			thread.detach();
		}
		virtual ~AsyncConsole()
		{
			isRunning = false;
		}

		AsyncConsole(const AsyncConsole&) = delete;

		inline const bool getNextCommand(
			std::string& command) noexcept
		{
			mutex.lock();
			
			if (commands.size() < 1)
			{
				mutex.unlock();
				return false;
			}

			command = std::string(commands.front());
			commands.pop();

			mutex.unlock();
			return true;
		}

		inline void clearQueue() noexcept
		{
			mutex.lock();
			commands = std::queue<std::string>();
			mutex.unlock();
		}
	};
}
