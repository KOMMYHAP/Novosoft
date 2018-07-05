#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <chrono>

/* 	Client хранит индивидуальную информацию, 
	а также имеет getter-ы для доступа к ней. */
class Client
{
public:
	using id_t = uint8_t;
	using seconds = std::chrono::seconds;

	Client(id_t id, seconds const &delay_s, std::string const &msg);

	Client(Client const &);
	Client & operator=(Client const &);

	~Client();

	void update(seconds elapsed_s);
    void resetElapsedTime() const;

	bool readyToSent() const;

	std::string const & message() const;
	id_t id() const;
	seconds delay() const;

private:
	std::string _message;
	id_t _id;

	seconds _delay_s;
	mutable seconds _elapsed_s {0};
};


#endif