#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <fstream>
#include <string>

#include "Client.hpp"

using std::ofstream;
using std::string;

class FileManager
{
public:
	FileManager(string const &filepath);

	FileManager(FileManager const &) = delete;
	FileManager& operator=(FileManager const &) = delete;

	~FileManager();

	void sent(Client const &);
private:
	ofstream _file;
	string _filepath;
};

#endif