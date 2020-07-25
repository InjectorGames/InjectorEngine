#pragma once
#include <injector/material.hpp>

namespace INJECTOR_NAMESPACE
{
	struct RenderComponent
	{
		enum class Order
		{
			Ascending,
			Descending,
			Front,
			Back,
		};

		Order order;
		int queue;
		int offset;
		MaterialHandle material;
		bool render;

		RenderComponent(
			Order order = Order::Ascending,
			int queue = 0,
			int offset = 0,
			const MaterialHandle& material = nullptr,
			bool render = true);
	};
}
