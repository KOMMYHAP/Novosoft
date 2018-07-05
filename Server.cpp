#include "Server.hpp"

Server::Server(string const &filepath) 
	: _client_manager_ptr(new ClientManager())
	, _file_manager_ptr(new FileManager(filepath))
{}

Server::~Server() {}

bool Server::createClient(seconds delay_s, string const &msg)
{
	return _client_manager_ptr->create(delay_s, msg);
}

void Server::run()
{
	seconds maximum_step = maximumDelay();

	vector<Client> readyClients;
	while (true) {
		 std::this_thread::sleep_for(maximum_step);
		_client_manager_ptr->update(maximum_step);

		readyClients = _client_manager_ptr->readyClients();
		try {
			for (auto const &client : readyClients) {
				sent(client);
			}
		} catch (std::runtime_error const &err) {
			std::cerr << err.what() << std::endl;
		}
	}
}

void Server::sent(Client const &client)
{
	_file_manager_ptr->sent(client);
}

seconds Server::gcd(seconds a, seconds b) const
{
	while (a != b) {
		if (a > b) {
			a -= b;
		} else {
			b -= a;
		}
	}
	return a;
}

seconds Server::maximumDelay() const
{
	auto const &clients = _client_manager_ptr->clients();
	seconds temp = clients[0].delay();
	for (size_t i = 1; i < clients.size(); ++i) {
		temp = gcd(temp, clients[i].delay());
	}
	return temp;
}