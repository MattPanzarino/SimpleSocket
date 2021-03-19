#pragma once
#include <string>
#include <vector>
#include <memory>
#define windows 1
#define linux 0

#if windows
#include <WinSock2.h>
#endif
#include <WS2tcpip.h>

namespace SimpleSocket
{
	enum struct SocketFamily
	{
		TCP, UDP
	};

	class ServerSocket
	{
	public:
		ServerSocket(std::string address, unsigned int port, SocketFamily family = SocketFamily::TCP)
		{

		}

		~ServerSocket()
		{

		}

		int send(std::vector<uint8_t>& data)
		{
			send(data.data(), data.size());
		}

		int send(uint8_t* data, size_t size);

		std::vector<uint8_t> receive(size_t amount)
		{
			std::vector<uint8_t> receive_vector(amount);
			receive(receive_vector.data(), amount);
		}

		int receive(uint8_t* buffer, size_t amount);
	private:
		int Accept()
		{

		}

		int close();


	};


	class ClientSocket
	{
		ClientSocket(std::string address, unsigned int port, SocketFamily family = SocketFamily::TCP)
		{

		}

		~ClientSocket()
		{

		}

		int send(std::vector<uint8_t>& data)
		{
			send(data.data(), data.size());
		}

		int send(uint8_t* data, size_t size);

		std::vector<uint8_t> receive(size_t amount)
		{
			std::vector<uint8_t> receive_vector(amount);
			receive(receive_vector.data(), amount);
		}

		int receive(uint8_t* buffer, size_t amount);
	private:
		int Accept()
		{

		}
	};
}
class SocketError {};
namespace WindowsSocket
{
	static bool WINSOCK_INITIALIZED = false;
	static int obj_count = 0;
	
	bool try_initialize()
	{
		WSADATA wsaData;

		auto result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	}

	class WindowsServerSocket
	{
	public:
		WindowsServerSocket(const std::string& host, const std::string& port, const SimpleSocket::SocketFamily family)
		{
			addrinfo info;
			info.ai_family = AF_INET;
			info.ai_socktype = SOCK_STREAM;
			if (family == SimpleSocket::SocketFamily::TCP)
			{
				info.ai_family = IPPROTO_TCP;
			}
			else if (family == SimpleSocket::SocketFamily::UDP)
			{
				info.ai_family = IPPROTO_UDP;
			}
			else
			{
				throw(SocketError());
			}
			info.ai_flags = AI_PASSIVE;

			auto res = getaddrinfo(host.c_str(), port.c_str(), &info, &address_info);

			if (res != 0)
			{
				throw(SocketError());
				//Cleanup
			}
			sock_ = socket(address_info->ai_family, address_info->ai_socktype, address_info->ai_protocol);
		
		}
	private:
		SOCKET sock_;
		addrinfo * address_info = 0;
	};
}