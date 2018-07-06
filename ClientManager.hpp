#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <string>
#include <vector>

#include "Client.hpp"

class ClientManagerImpl;

/*	Менеджер клиентов управляет списком всех клиентов, 
	подключенных к серверу.	*/
class ClientManager
{
public:
	using id_t = Client::id_t;
	using seconds = Client::seconds;

	ClientManager();

	ClientManager(ClientManager const &) = delete;
	ClientManager& operator=(ClientManager const &) = delete;

	~ClientManager();

	/*	Попытка добавить очередного клиента в список.
		Если список переполнен - возращается false,
		иначе - true. */
	void createClient(seconds delay_s, std::string const &msg);

	/*	Сообщает всем клиентам, что прошло
		elapsed_s секунд */
	void update(seconds elapsed_s);

	seconds getOptimalDelayTime() const;

	/*	Возвращает список всех клиентов */
	std::vector<Client> clients() const;

	/*	Возвращает список всех клиентов,
		готовых к отправке сообщения */
	std::vector<Client> readyClients() const;

private:
	ClientManagerImpl *_impl_ptr;
};

#endif