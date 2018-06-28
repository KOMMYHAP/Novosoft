/* ---------------------------------------------------------------- */
#include <cstdint>

#include "ClientManager.hpp"
class Server
{
public:
	using id_t = ClientManager::id_t;
	using time_t = Client::time_t;

public:
	Server() 
		: _client_manager_ptr(new ClientManager())
		, _print_manager_ptr(new PrintManager())
	{}
	~Server() {}

	void create_client(time_t delay_s, string const &msg)
	{
		try {
			_client_manager_ptr->create(delay_s, msg)
		} catch (...) {
			// overflow of id_t type
		}
	}

	// добавить вывод в формате, указанном в тз
	void sent(Client const &client)
	{
		_print_manager_ptr->print(client->id(), client->msg());
	}

	void update()
	{
		_client_manager_ptr->update();
	}
private:
	ClientManager *_client_manager_ptr;
	PrintManager *_print_manager_ptr;
};


/* ---------------------------------------------------------------- */
#include <chrono> /* seconds */

/*
	Сервер создает каждого клиента.
	server.create_client(time_t delay_s, string const &msg)
	Таким образом каждый клиент имеет уникальной id
*/
class Client
{
public:
	using id_t Server::id_t;
	using time_t std::chrono::seconds;

	Client(id_t id, time_t delay_s, string const &msg)
		: _delay_s(delay_s)
		, _message(msg)
		, _id(id)
	{}

	Client(Client const &) = delete;
	Client & operator=(Client const &) = delete;

	~Client()
	{}

	void update(Server &server, time_t elapsed_s)
	{
		_elapsed_s += elapsed_s;
		if (_delay_s >= elapsed_s) {
			server.sent(_message);
		}
	}
private:
	string const _message;
	time_t const _delay_s;
	time_t _elapsed_s;
};

/* ---------------------------------------------------------------- */