#include "FileManager.hpp"

FileManager::FileManager(string const &filepath)
	: _file(filepath)
	, _filepath(filepath)
{
	_file.close();
}

FileManager::~FileManager() {}

void FileManager::sent(Client const &client)
{
	auto const time_now = std::chrono::system_clock::now();
	auto const time_now_c = std::chrono::system_clock::to_time_t(time_now);

	_file.open(_filepath, std::ios_base::app);
	if (!_file.is_open()) {
		throw std::runtime_error("[FILEMANAGER] Cannot open file");
	}
	_file 
		<< std::put_time(localtime(&time_now_c), "%T") << "; "
		<< uint64_t(client.id()) << ": "
		<< client.message() << '\n';
	_file.close();
}