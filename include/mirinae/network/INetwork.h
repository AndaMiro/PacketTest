#pragma once
#include <asio.hpp>
#include <cstdint>
#include <memory>
#include <vector>

namespace mirinae::network{
	using Endpoint = asio::ip::udp::endpoint;
	using Buffer = std::shared_ptr<const std::vector<std::uint8_t>>;
	using PacketCallBack = std::function<void(const void* data)>;

	class INetwork{
		public : 
			virtual ~INetwork() = default;

			virtual void start(PacketCallBack cb) = 0;
			virtual void stop() = 0;
			virtual void send(const Endpoint& to, const Buffer& buf) = 0;
	};
}
