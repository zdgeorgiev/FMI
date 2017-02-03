/**
*
* Solution to course project
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Zdravko Georgiev
* @idnumber 45115
* @task course project
* @compiler VC
*
*/
#include "ArchiverUtils.h"

char* getAbsolutePath(char* buffer, WIN32_FIND_DATA& ffd)
{
	char* absoliutePath = new char[1024];
	strcpy(absoliutePath, "");
	strcat(absoliutePath, buffer);
	strcat(absoliutePath, "\\");
	strcat(absoliutePath, ffd.cFileName);
	return absoliutePath;
}

char* getRelativePath(char* absoliutePath, const char* originalPath)
{
	char* relativePath = new char[1024];
	strcpy(relativePath, strstr(absoliutePath, originalPath) + strlen(originalPath));
	return relativePath;
}

unsigned char getFileTypeAndName(std::ifstream& is)
{
	unsigned char fileTypeAndName;
	is.read((char*)&fileTypeAndName, sizeof(fileTypeAndName));
	return fileTypeAndName;
}

char* getFileName(unsigned char fileTypeAndName, std::ifstream& is)
{
	unsigned char fileLen = ((1 << 7) - 1) & fileTypeAndName;

	char* fileName = new char[fileLen + 1];
	is.read((char*)fileName, sizeof(char) * fileLen);
	fileName[fileLen] = '\0';
	return fileName;
}

bool getFileType(unsigned char fileTypeAndName)
{
	return (1 << 7) & fileTypeAndName;
}

void ArchiverUtils::compress(const char* source, const char* destination, const char* originalPath, std::ofstream& os)
{
	compressFiles(source, destination, originalPath, os);
	compressDirectories(source, destination, originalPath, os);
}

void ArchiverUtils::compressFiles(const char* source, const char* destination, const char* originalPath, std::ofstream& os)
{
	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR buffer[4096] = TEXT("");

	// Prepare string for use with FindFile functions. First, copy the
	// string to a buffer, then append '\*' to the directory name.
	StringCchCopy(szDir, MAX_PATH, source);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory.
	hFind = FindFirstFile(szDir, &ffd);

	do
	{
		GetFullPathName(source, 4096, buffer, NULL);
		char* nextFileAbsolutePath = getAbsolutePath(buffer, ffd);
		char* nextFileRelativePath = getRelativePath(nextFileAbsolutePath, originalPath);

		// Iterate only the files
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			std::cout << "Compressing file : " << nextFileRelativePath << std::endl;

			// [FileType and FileNameLen] => 8 bit
			// (first bit = 1 => directory , 0 => file, other 7 bits are the name lenght (0-127))
			unsigned char fileLenAndType = 0 + strlen(ffd.cFileName);
			os.write((char*)&fileLenAndType, sizeof(fileLenAndType));

			// [FileName] => FileNameLen * sizeof(char)
			os.write((char*)ffd.cFileName, sizeof(char) * fileLenAndType);

			char buffer[1024];
			strcpy(buffer, source);
			strcat(buffer, "\\");
			strcat(buffer, ffd.cFileName);

			std::ifstream is(buffer, std::ios_base::binary);
			HuffmanTree t(is);
			t.serialize(is, os);
			is.close();
		}

	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
}

void ArchiverUtils::compressDirectories(const char* source, const char* destination, const char* originalPath, std::ofstream& os)
{
	WIN32_FIND_DATA ffd;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR buffer[4096] = TEXT("");

	// Prepare string for use with FindFile functions. First, copy the
	// string to a buffer, then append '\*' to the directory name.
	StringCchCopy(szDir, MAX_PATH, source);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory.
	hFind = FindFirstFile(szDir, &ffd);

	int c = 0;
	do
	{
		// skip the current folder and parent one
		if (c++ < 2)
			continue;

		GetFullPathName(source, 4096, buffer, NULL);
		char* nextFileAbsolutePath = getAbsolutePath(buffer, ffd);
		char* nextFileRelativePath = getRelativePath(nextFileAbsolutePath, originalPath);

		// Iterate only the directories
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// [FileType and FileNameLen] => 8 bit
			// (first bit = 1 => directory , 0 => file, other 7 bits are the name lenght (0-127))
			unsigned char fileLen = strlen(ffd.cFileName);
			unsigned char fileLenAndType = (1 << 7) + fileLen;
			os.write((char*)&fileLenAndType, sizeof(fileLenAndType));

			// [Actual Name] => FileNameLen * sizeof(char)
			os.write((char*)ffd.cFileName, sizeof(char) * fileLen);

			// [RelativePathLen] => 16 bit (0-65,535)
			unsigned short relPathLen = strlen(nextFileRelativePath);
			os.write((char*)&relPathLen, sizeof(relPathLen));

			// [Relative Path] => RelativePathLen * sizeof(char)
			os.write((char*)nextFileRelativePath, sizeof(char) * relPathLen);

			compress(nextFileAbsolutePath, destination, originalPath, os);
		}

		delete[] nextFileAbsolutePath;
		delete[] nextFileRelativePath;

	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
}

void ArchiverUtils::decompress(const char* source, const char* destination, const char* originalPath, std::ifstream& is)
{
	while (true)
	{
		unsigned char fileTypeAndName = getFileTypeAndName(is);
		char* fileName = getFileName(fileTypeAndName, is);
		bool fileType = getFileType(fileTypeAndName);

		if (!is.good() || is.eof())
			break;

		switch (fileType)
		{
		case DIRECTORY:
		{
			decompressDirectory(fileName, source, originalPath, is);
			break;
		}
		case FILE:
		{
			decompressFile(fileName, destination, is);
			break;
		}
		default:
			throw "Illegal state of the decompressing. File type is " + fileType;
		}

		delete[] fileName;
	}
}

void ArchiverUtils::decompressDirectory(char* directoryName, const char* source, const char* originalPath, std::ifstream& is)
{
	char* absolutePath = new char[1024];
	
	unsigned short relPathLen;
	is.read((char*)&relPathLen, sizeof(relPathLen));

	char* relPath = new char[relPathLen + 1];
	is.read(relPath, sizeof(char) * relPathLen);
	relPath[relPathLen] = '\0';

	strcpy(absolutePath, originalPath);
	strcat(absolutePath, relPath);

	_mkdir(absolutePath);

	delete[] relPath;
	decompress(source, absolutePath, originalPath, is);
	delete[] absolutePath;
}

void ArchiverUtils::decompressFile(char* fileName, const char* destination, std::ifstream& is)
{
	std::cout << "Decompressing file : " << fileName << std::endl;

	char* absolutePath = new char[1024];
	strcpy(absolutePath, destination);
	strcat(absolutePath, "\\");
	strcat(absolutePath, fileName);

	std::ofstream os(absolutePath, std::ios::binary);
	Trie t;
	t.deserializeFile(is, os);
	os.close();

	delete[] absolutePath;
}

void ArchiverUtils::listAllFiles(std::ifstream& is, std::ostream& os)
{
	unsigned long long fileSize;
	is.seekg(0, std::ios::end);
	fileSize = is.tellg() / sizeof(char);
	is.seekg(0, std::ios::beg);

	while (true)
	{
		unsigned char fileType;
		is.read((char*)&fileType, sizeof(fileType));

		if (is.eof())
			break;

		os << getFileName(fileType, is) << std::endl;

		switch (getFileType(fileType))
		{
		case FILE:
		{
			unsigned short headerLen;
			is.read((char*)&headerLen, sizeof(headerLen));
			is.seekg(headerLen, std::ios::cur);

			if (headerLen)
			{
				unsigned long long fileContent;
				is.read((char*)&fileContent, sizeof(fileContent));

				int bits = 0;
				while (bits < fileContent)
					bits += 32;

				is.seekg(bits / 8, std::ios::cur);
			}

			break;
		}
		case DIRECTORY:
		{
			unsigned short relPathLen;
			is.read((char*)&relPathLen, sizeof(relPathLen));
			is.seekg(relPathLen, std::ios::cur);
			break;
		}
		default:
			throw "Illegal file type " + fileType;
		}
	}
}