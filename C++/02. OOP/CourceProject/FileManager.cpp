#include "FileManager.h"

FileManager::FileManager()
{
	this->setFilePath("");
	this->isFileOpened = false;
}

FileManager::~FileManager()
{
	this->fileContent.clear();
	this->fileName.clear();
	this->filePath.clear();
}

bool FileManager::open(string filePath)
{
	if (this->isFileOpened)
	{
		cout << "To open another file first close the current one." << endl;
		return false;
	}

	this->setFilePath(filePath);

	ifstream f(this->filePath);

	if (f.good())
	{
		f.seekg(0, ios::end);
		int fileSize = f.tellg();
		f.seekg(0, ios::beg);

		this->fileContent.resize(fileSize);
		f.read((char*)this->fileContent.c_str(), fileSize);

		cout << "Successfully opened " << this->fileName << endl;
		this->isFileOpened = true;
		return true;
	}
	else
		cout << "File destination [" << this->filePath << "]" << " is invalid" << endl;

	f.close();
	return false;
}

void FileManager::close()
{
	if (!this->isFileOpened)
	{
		cout << "No file is opened" << endl;
		return;
	}

	this->fileContent.clear();
	cout << "Successfully closed " << this->fileName << endl;
	this->isFileOpened = false;
}

void FileManager::write(string content, string destination)
{
	if (!this->isFileOpened)
	{
		cout << "To write in file first you must open it" << endl;
		return;
	}

	ofstream f(destination, ios::trunc);

	if (f.good())
	{
		f.write(content.c_str(), content.size());

		if (f.good())
			cout << "Successfully saved " << destination << endl;
		else
			cout << "Erroe occured while writing to file [" << destination << "]" << endl;
	}

	f.close();
}

void FileManager::setFilePath(string filePath)
{
	this->filePath = filePath;
	this->fileName = getFileNameFromPath(filePath);
	this->fileContent.clear();
}

string FileManager::getFilePath() const
{
	return this->filePath;
}

string FileManager::getFileName() const
{
	return this->fileName;
}

string FileManager::getFileContent() const
{
	return this->fileContent;
}

bool FileManager::getIfFileOpened() const
{
	return this->isFileOpened;
}

string FileManager::getFileNameFromPath(string path) const
{
	string fileDelimiter = "\\";

	if(path.find(fileDelimiter) != -1)
		return path.substr(path.find_last_of(fileDelimiter) + 1);

	fileDelimiter.clear();
	return path;
}