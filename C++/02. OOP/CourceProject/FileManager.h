#ifndef FILE_MANAGER_HEADER_INCLLUDED
#define FILE_MANAGER_HEADER_INCLLUDED

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class FileManager
{
public:

	FileManager();
	~FileManager();

	bool open(string filePath);
	void close();
	void write(string content, string destination);

	void setFilePath(string filePath);

	string getFilePath() const;
	string getFileName() const;
	string getFileContent() const;
	bool getIfFileOpened() const;

private:
	string filePath;
	string fileContent;
	string fileName;
	bool isFileOpened;

	string getFileNameFromPath(string path) const;
};

#endif
