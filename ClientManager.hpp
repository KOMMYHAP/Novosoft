#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <vector>
#include <cstdint> /* uint8_t */
#include <string>

using std::string;
using std::vector;

#include "Client.hpp"

class ClientManager
{
public:
	using id_t = Client::id_t;
	using seconds = Client::seconds;

	ClientManager();

	ClientManager(ClientManager const &) = delete;
	ClientManager& operator=(ClientManager const &) = delete;

	~ClientManager();

	bool create(seconds delay_s, string const &msg);

	void update(seconds elapsed_s);

	vector<Client> const & clients() const;
	vector<Client> readyClients() const;
private:
	vector<Client> _clients;
	id_t _max_id {0};
};

#endif