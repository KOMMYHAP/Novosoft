#include "Server.hpp"

#include <iostream> /* cerr in run() */
#include <stdexcept> /* runtime_error */
#include <algorithm> /* max_element */
#include <thread>

#include <chrono>

Server::Server(std::string const &filepath) 
	: _client_manager_ptr(new ClientManager())
	, _file_manager_ptr(new FileManager(filepath))
{}

Server::~Server() {}

bool Server::createClient(seconds delay_s, std::string const &msg)
{
	return _client_manager_ptr->create(delay_s, msg);
}

void Server::run()
{
	seconds 
		optimal_time_step_s = _client_manager_ptr->getOptimalDelay(),
		delay_s {0};

	chrono::steady_clock::time_point start_tp, end_tp;
	while (true) {
		 std::this_thread::sleep_for(optimal_time_step_s);

		 start_tp = chrono::steady_clock::now();
		 {
			_client_manager_ptr->update(optimal_time_step_s + delay_s);

			auto const readyClients = _client_manager_ptr->readyClients();
			try {
				for (auto const &client : readyClients) {
					send(client);
				}
			} catch (std::runtime_error const &err) {
				std::cerr << err.what() << std::endl;
			}
		}
		end_tp = chrono::steady_clock::now();
		delay_s = chrono::duration_cast<seconds>(end_tp - start_tp);
	}
}

void Server::send(Client const &client)
{
	_file_manager_ptr->sent(client);
}
