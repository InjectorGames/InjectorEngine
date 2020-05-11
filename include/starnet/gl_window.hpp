#pragma once
#include <starnet/udp_server_system.hpp>
#include <starnet/udp_client_system.hpp>

#include <inject/gl_window.hpp>
#include <inject/gl_draw_system.hpp>
#include <inject/camera_system.hpp>
#include <inject/transform_system.hpp>
#include <inject/net_context_system.hpp>
#include <inject/free_camera_system.hpp>

namespace starnet
{
	class GlWindow final : public inject::GlWindow
	{
	public:
		GlWindow(const std::string& title = "Starnet (OpenGL)",
			const glm::ivec2& position = glm::ivec2(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
			const glm::ivec2& size = glm::ivec2(INJECT_WINDOW_WIDTH, INJECT_WINDOW_HEIGHT),
			const uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL) :
			inject::GlWindow(title, position, size, flags)
		{
			auto netContext = systems.add<inject::NetContextSystem>();
			auto server = systems.add<UdpServerSystem>(netContext->getContext());
			auto client = systems.add<UdpClientSystem>(netContext->getContext());

			server->start();
			client->connect(asio::ip::udp::endpoint(asio::ip::make_address_v6("::1"), 12345));
			client->sendConnectRequest("player_1");

			systems.add<inject::FreeCameraSystem>();
			systems.add<inject::TransformSystem>();
			systems.add<inject::CameraSystem>();
			systems.add<inject::GlDrawSystem>();
			systems.configure();
		}
	};
}
