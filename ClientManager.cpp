#include "ClientManager.hpp"

#include "ClientManagerImpl.hpp"

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

ClientManager::storage_t ClientManager::clients() const
{
	auto const &_clients = _impl_ptr->clients();
	return std::vector<Client>(_clients.cbegin(), _clients.cend());
}

ClientManager::storage_t ClientManager::readyClients() const
{
	auto const &_clients = _impl_ptr->readyClients();
	return std::vector<Client>(_clients.cbegin(), _clients.cend());	
}
