#pragma once
#include "Injector/System.hpp"
#include "asio.hpp"

namespace Injector
{
	class NetContextSystem : public System
	{
	 private:
		std::shared_ptr<asio::io_context> context;
	 public:
		NetContextSystem(
			const std::shared_ptr<asio::io_context>& context =
				std::make_shared<asio::io_context>());

		std::shared_ptr<asio::io_context> getContext() const noexcept;
		void update() override;
	};
}
