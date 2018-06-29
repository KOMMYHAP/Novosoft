#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream> /* cerr in run() */
#include <stdexcept> /* runtime_error */
#include <utility> /* unique_ptr */
#include <algorithm> /* max_element */
#include <string>
#include <thread>

#include "Client.hpp"
#include "ClientManager.hpp"
#include "FileManager.hpp"

using std::string;

class Server
{
public:
	friend class Client;
	using seconds = Client::seconds;

public:
	Server(string const &filepath);

	~Server();

	bool create_client(seconds delay_s, string const &msg);

	void run();
private:

	void sent(Client const &client);

	seconds gcd(seconds, seconds) const;
	seconds maximumDelay() const;
private:
	std::unique_ptr<ClientManager> _client_manager_ptr;
	std::unique_ptr<FileManager> _file_manager_ptr;
};

#endif