#include "Server.hpp"

#include <iostream> /* cerr in run() */
#include <stdexcept> /* runtime_error */
#include <thread>

#include <chrono>

using std::chrono::seconds;
using std::chrono::steady_clock;

Server::Server(std::string const &filepath) 
	: _client_manager_ptr(new ClientManager())
	, _file_manager_ptr(new FileManager(filepath))
{}

Server::~Server() {}

void Server::createClient(seconds delay_s, std::string const &msg)
{
	_client_manager_ptr->createClient(delay_s, msg);
}

void Server::run()
{
	seconds const optimal_time_step_s = 
		_client_manager_ptr->getOptimalDelayTime();

	while (true) {
		 std::this_thread::sleep_for(optimal_time_step_s);

		_client_manager_ptr->update(optimal_time_step_s);

		auto const readyClients = _client_manager_ptr->readyClients();
		try {
			for (auto const &client : readyClients) {
				send(client);
			}
		} catch (std::runtime_error const &err) {
			std::cerr << err.what() << std::endl;
		}
	}
}

void Server::send(Client const &client)
{
	_file_manager_ptr->send(client);
}
