#include <iostream>

#include "Server.hpp"

/*
	Чат на клиент-серверной концепции.
	Клиент отправляет заранее заданное сообщение с определенный интервалов времени.
	Сервер записывает входящие сообщения в один файл.
*/

int main(int argc, char **argv)
{
	if (argc <= 4) {
		std::cout 
			<< "Usage: " << argv[0] << ' '
			<< "(filepath) "
			<< "(client_amount) "
			<< "(client_delay_s) (client_msg) "
			<< "[(client_delay_s) (client_msg)]\n";
		return 0;
	}
	
	int client_amount = std::atoi(argv[2]);
	if (client_amount <= 0) {
		std::cout << "client_amount must be positive integer" << std::endl;
		return 1;
	}
	if (client_amount * 2 + 3 != argc) { // offset 3 is  argv[0], filepath, client_amount
		std::cout << "Pair amount of client_delay_s and client_msg must be equals client_amount" << std::endl;
		return 1;
	}

	try {
		// запуск сервера с указанием пути до файла:
		Server server(argv[1]);

		// инициализация клиентов:
		bool success = true;
		for (int i = 3; i < argc && success; i += 2) {
			auto const delay_s = Client::seconds{atol(argv[i])};
			if (delay_s == Client::seconds{0}) {
				throw std::runtime_error("client_delay_s must be positive integer");
			}
			success = server.create_client(delay_s, argv[i + 1]);
		}
		if (!success) {
			std::cout << "Reached the maximum of client amount" << std::endl;
		}

		// выполнение работы сервера:
		server.run();
	} catch (std::runtime_error const &err) {
		std::cerr << err.what() << std::endl;
	} catch (std::bad_alloc const &err) {
		std::cerr << "Cannot allocate memory for server" << std::endl;
	}

}