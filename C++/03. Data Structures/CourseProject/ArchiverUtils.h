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
#pragma once

#ifndef __ARCHIVER_UTILS_HEADER_INCLUDED__
#define __ARCHIVER_UTILS_HEADER_INCLUDED__

#include <windows.h>
#include <strsafe.h>
#include <iostream>
#include <fstream>
#include <direct.h>

#include "HuffmanTree.h"
#include "Trie.h"

#pragma comment(lib, "User32.lib")

class ArchiverUtils
{
private:

	enum FileType { FILE = 0, DIRECTORY = 1 };

	static void compress(const char* source, const char* destination, const char* originalPath, std::ofstream& os);

	static void compressFiles(const char* source, const char* destination, const char* originalPath, std::ofstream& os);
	static void compressDirectories(const char* source, const char* destination, const char* originalPath, std::ofstream& os);

	static void decompress(const char* source, const char* destination, const char* originalPath, std::ifstream& is);

	static void decompressFile(char* fileName, const char* destination, std::ifstream& is);
	static void decompressDirectory(char* directoryName, const char* source, const char* originalPath, std::ifstream& is);

	static void listAllFiles(std::ifstream& is, std::ostream& os);

public:
	
	/// Compressing the source into the destionation in one archive
	/// This implementation also keep the structure of the source.
	static void compress(const char* source, const char* destination)
	{
		char* sourceCpy = new char[1024];
		strcpy(sourceCpy, source);
		std::ofstream os(destination, std::ios_base::binary);
		compress(source, destination, sourceCpy, os);
		delete[] sourceCpy;
		os.close();
	}

	/// Decompress the souce into the destination. Souce must be a valid compressed archive
	/// The original structure of the directory will be restored.
	static void decompress(const char* source, const char* destination)
	{
		_mkdir(destination);
		char* destinationCpy = new char[1024];
		strcpy(destinationCpy, destination);
		std::ifstream is(source, std::ios_base::binary);
		decompress(source, destination, destinationCpy, is);
		delete[] destinationCpy;
		is.close();
	}

	/// List all the files and directories of an valid archive to the outputstream.
	/// Source is parametur must be a valid path to already compressed archive.
	static void listAllFiles(const char* source, std::ostream& os)
	{
		std::ifstream is(source, std::ios_base::binary);
		listAllFiles(is, os);
		is.close();
	}
};

#endif