#pragma once
#include <asio.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace mirinae{
	using Endpoint = asio::ip::udp::endpoint;
	using Buffer = std::shared_ptr<const std::vector<std::uint8_t>>;

	class INetwork{
		public : 
			virtual ~INetwork() = default;

			virtual void start() = 0;
			virtual void stop() = 0;
			virtual void send(const Endpoint& to, const Buffer& buf) = 0;
	};
}
