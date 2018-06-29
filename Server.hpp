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
	using seconds = Client::seconds;

public:
	/*	Создание сервера.
		filepath: путь до файла, куда
		будет записываться сообщения клиентов. */
	Server(string const &filepath);

	~Server();

	/*	Добавление клиента на сервер.
		delay_s: период отправки сообщения
		msg: сообщение, посылаемое клиентом */
	bool create_client(seconds delay_s, string const &msg);

	/*	Выполнение полезной работы в бесконечном цикле */
	void run();
private:
	/*	Запись информации о клиентe в файл.
		Формат: [текущее время с точностью до секунды]; [номер клиента]: [текст сообщения] */
	void sent(Client const &client);

	/*	Вспомогательный функции для оптимизации бесконечного цикла в run()
		gcd - поиск НОД
		maximumDelay - поиск оптимального время сна
	*/
	seconds gcd(seconds, seconds) const;
	seconds maximumDelay() const;
private:
	std::unique_ptr<ClientManager> _client_manager_ptr;
	std::unique_ptr<FileManager> _file_manager_ptr;
};

#endif