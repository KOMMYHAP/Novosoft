#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <fstream>
#include <string>

#include "Client.hpp"

class FileManager
{
public:
	FileManager(string const &filepath);

	FileManager(FileManager const &) = delete;
	FileManager& operator=(FileManager const &) = delete;

	~FileManager();

	void sent(Client const &);
private:
	std::ofstream _file;
	std::string _filepath;
};

#endif