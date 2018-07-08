#ifndef SERVER_HPP
#define SERVER_HPP

#include <memory> /* unique_ptr */

#include "Client.hpp"
#include "ClientManager.hpp"
#include "FileManager.hpp"

class Server
{
public:
	using seconds = Client::seconds;

public:
	/*	Создание сервера.
		filepath: путь до файла, куда
		будут записываться сообщения клиентов. */
	Server(std::string const &filepath);

	// temporary removed
	Server(Server const &) = delete;
	Server& operator=(Server const &) = delete;

	~Server();

	/*	Добавление клиента на сервер.
		delay_s: период отправки сообщения
		msg: сообщение, посылаемое клиентом */
	void createClient(seconds delay_s, std::string const &msg);

	/*	Выполнение полезной работы в бесконечном цикле */
	void run();
private:
	/*	Запись информации о клиентe в файл.
		Формат: [текущее время с точностью до секунды]; [номер клиента]: [текст сообщения] */
	void send(Client const &client);

private:
	std::unique_ptr<ClientManager> _client_manager_ptr;
	std::unique_ptr<FileManager> _file_manager_ptr;
};

#endif