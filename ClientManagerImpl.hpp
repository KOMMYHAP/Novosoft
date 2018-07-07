#ifndef CLIENT_MANAGER_IMPL_HPP
#define CLIENT_MANAGER_IMPL_HPP

#include "ClientManager.hpp"

#include <list>

class ClientManagerImpl
{
public:
	using id_t = ClientManager::id_t;
	using seconds = ClientManager::seconds;

	using storage_t = std::list<Client>;
	using const_iterator_t = typename storage_t::const_iterator;

public:
	ClientManagerImpl() = default;

	// temporary removed
	ClientManagerImpl(ClientManagerImpl const&) = delete;
	ClientManagerImpl& operator=(ClientManagerImpl const &) = delete;

	~ClientManagerImpl() = default;
	
	seconds getOptimalDelayTime() const;

	bool isMaximumId() const;

	void update(seconds elapsed_s);
	void emplace(seconds delay_s, std::string const &msg);
	void sort();

	storage_t const & clients() const;
	storage_t readyClients() const;
private:
	void resetElapsedTime();
	
	seconds gcd(seconds a, seconds b) const;
	void updateOptimalDelay(seconds other_delay_s);
private:
	storage_t _clients;

	seconds _optimal_delay_s {0};
	seconds _elapsed_s {0};
	id_t _max_id {0};
};

#endif