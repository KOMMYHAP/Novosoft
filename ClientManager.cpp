#include "ClientManager.hpp"

#include <cstdint> /* uint8_t */

using std::string;
using std::vector;

ClientManager::ClientManager() {}

ClientManager::~ClientManager() {}

bool ClientManager::create(seconds delay_s, string const &msg)
{
	if (_max_id == std::numeric_limits<id_t>::max()) {
		return false;
	}
	_clients.emplace_back(Client(_max_id, delay_s, msg));
	_max_id++;
	return true;
}

void ClientManager::update(seconds elapsed_s)
{
	for (auto &client : _clients) {
		client.update(elapsed_s);
	}
}

vector<Client> const & ClientManager::clients() const
{
	return _clients;
}

vector<Client> ClientManager::readyClients() const
{
	vector<Client> result;
	for (auto const &client : _clients) {
		if (client.readyToSend()) {
			result.push_back(client);
			client.resetElapsedTime();
		}
	}
	return result;
}