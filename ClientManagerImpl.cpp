#include "ClientManagerImpl.hpp"

#include <utility>
#include <stdexcept>

void ClientManagerImpl::emplace(seconds delay_s, std::string const &msg)
{
	if (isMaximumId()) {
		throw std::runtime_error{"[CLIENTMANAGER]: Reached limit of client numbers"};
	}

	_clients.emplace_back(Client(_max_id, delay_s, msg));
	_max_id++;

	sort(); // sort array of client by delay
	updateOptimalDelay(delay_s); // recompute optimal delay with new value
}

void ClientManagerImpl::update(seconds elapsed_s)
{
	if (!_clients.empty()) {
		auto const max_delay_s = _clients.crbegin()->delay();
		if (_elapsed_s >= max_delay_s) {
			elapsed_s += max_delay_s - _elapsed_s;
			resetElapsedTime();
		}

		_elapsed_s += elapsed_s;	
	}
}

void ClientManagerImpl::resetElapsedTime()
{
	_elapsed_s = seconds{0};
}

void ClientManagerImpl::sort()
{
	auto const by_delay = [] (Client const &lhs, Client const &rhs) {
		return lhs.delay() < rhs.delay();
	};
	_clients.sort(by_delay);
}

ClientManagerImpl::storage_t const & ClientManagerImpl::clients() const
{
	return _clients;
}

ClientManagerImpl::storage_t  ClientManagerImpl::readyClients() const
{
	storage_t result;
	for (auto const client : _clients) {
		if (_elapsed_s % client.delay() == seconds{0}) {
			result.push_back(client);
		}
	}
	return result;
}

bool ClientManagerImpl::isMaximumId() const
{
	return std::numeric_limits<id_t>::max() == _max_id;
}

ClientManagerImpl::seconds
ClientManagerImpl::getOptimalDelayTime() const
{
	return _optimal_delay_s;
}

void ClientManagerImpl::updateOptimalDelay(seconds other_delay_s) 
{
	_optimal_delay_s = _optimal_delay_s != seconds{0} ? 
		gcd(_optimal_delay_s, other_delay_s) :
		other_delay_s;
}

ClientManagerImpl::seconds 
ClientManagerImpl::gcd(seconds a, seconds b) const
{
	while (a != b) {
		if (a > b) {
			a -= b;
		} else {
			b -= a;
		}
	}
	return a;	
}