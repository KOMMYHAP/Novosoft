#include "ClientManager.hpp"

#include <list>

class ClientManagerImpl
{
public:
	using storage_t = std::list<Client>;
	using const_iterator_t = typename storage_t::const_iterator;

private:
	using id_t = ClientManager::id_t;
	using seconds = ClientManager::seconds;

public:
	ClientManagerImpl();
	~ClientManagerImpl() = default;

	std::pair<const_iterator_t, const_iterator_t>
	getMinMaxDelayIterators() const;

	bool isMaximumId() const;

	void update(seconds elapsed_s);
	void emplace(seconds delay_s, std::string const &msg);
	void sort();

	storage_t const & clients() const;
private:
	void reset();

private:
	storage_t _clients;

	std::pair<const_iterator_t, const_iterator_t> _min_max_delay_iterators;

	seconds _elapsed_s;
	id_t _max_id {0};
};

/* ------------------------------------------------------------------------- */

ClientManager::ClientManager() 
	: _impl_ptr(new ClientManagerImpl()) 
{}

ClientManager::~ClientManager() 
{
	delete _impl_ptr;
}

void ClientManager::createClient(seconds delay_s, std::string const &msg)
{
	_impl_ptr->emplace(delay_s, msg);
}

void ClientManager::update(seconds elapsed_s)
{
	_impl_ptr->update(elapsed_s);
}

ClientManager::seconds ClientManager::getOptimalDelayTime() const
{
	return seconds{0};
}

std::vector<Client> ClientManager::clients() const
{
	auto const &_clients = _impl_ptr->clients();
	return std::vector<Client>(_clients.cbegin(), _clients.cend());
}

std::vector<Client> ClientManager::readyClients() const
{
	std::vector<Client> result;
	auto const [it_begin, it_end] = _impl_ptr->getMinMaxDelayIterators();
	for (auto it = it_begin; it != it_end; std::next(it)) {
		result.push_back(*it);
	}
	return result;
}

/* ------------------------------------------------------------------------- */

#include <utility>
#include <stdexcept>

ClientManagerImpl::ClientManagerImpl()
	: _clients{}
	, _min_max_delay_iterators{_clients.cend(), _clients.cend()}
{}

void ClientManagerImpl::emplace(seconds delay_s, std::string const &msg);
{
	if (isMaximumId()) {
		throw std::runtime_error{"[CLIENTMANAGER]: Reached limit of client numbers"};
	}

	_clients.emplace_back(Client(_max_id, delay_s, msg));
	_max_id++;

	sort();
}

void ClientManagerImpl::update(seconds elapsed_s)
{
	if (_elapsed_s > _clients.crbegin().delay()) {
		// add difference to elapsed_s
		elapsed_s += _clients.crbegin().delay() - _elapsed_s;
		reset();
	}
	_elapsed_s += elapsed_s;
}

void ClientManagerImpl::reset()
{
	_elapsed_s = seconds{0};
	_min_max_delay_iterators = 
		std::make_pair(_clients.cbegin(), _clients.cend());
}

void ClientManagerImpl::sort()
{
	auto const by_delay = [] (Client const &lhs, Client const &rhs) {
		return lhs.delay() < rhs.delay();
	};
	_clients.sort(by_delay);
}

storage_t const & ClientManagerImpl::clients() const
{
	return _clients;
}

std::pair<const_iterator_t, const_iterator_t>
getMinMaxDelayIterators() const
{
	auto &[it_min, it_max] = _min_max_delay_iterators;

	for (; it_min != _clients.cend(); std::next(it_min)) {
		if (_elapsed_s > it_min.delay()) {
			break;
		}
	}

	for (it_max = it_min; it_max != _clients.cend(), std::next(it_max)) {
		if (it_max.delay() > _elapsed_s) {
			break;
		}
	}

	return _min_max_delay_iterators;
}

bool isMaximumId() const
{
	return std::numeric_limits<id_t>::max() == _max_id;
}