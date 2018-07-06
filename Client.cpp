#include "Client.hpp"

using std::string;
using std::chrono::seconds;

Client::Client(id_t id, seconds const &delay_s, string const &msg)
	: _message(msg)
	, _id(id)
	, _delay_s(delay_s)
{}


Client::Client(Client const &client)
	: _message(client._message)
	, _id(client._id)
	, _delay_s(client._delay_s)
{}

Client & Client::operator=(Client const &client)
{
	if (this != &client) {
		_message = client._message;
		_id = client._id;
		_delay_s = client._delay_s;
	}

	return *this;
}

Client::~Client()
{}

string const & Client::message() const {return _message;}
Client::id_t Client::id() const {return _id;}
seconds Client::delay() const {return _delay_s;}