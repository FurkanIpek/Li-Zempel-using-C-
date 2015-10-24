#include "Decompressor.h"
#include <exception>
#include <fstream>//ifstream and ofstream
#include <sstream>//istringstream

/* HELPER FUNCTIONS */

bool IsExist (std::string *memory, int index)
{
	return memory[index] != "" ? true : false;
}

const std::string processFileName (const std::string fileIn)
{
	int indexOfDot = fileIn.rfind('.');

	if ( indexOfDot == std::string::npos )
		return fileIn;
	// file extensions are fixed as txt. there is no point to mess with extensions
	// purpose of this project is to compress/decompress txt files. new is added to
	// compare old and new files to check whether compression was successfull
	return fileIn.substr(0, fileIn.rfind('.')) + ".new.txt";
}

/* MEMBER FUNCTIONS */

Decompressor::Decompressor() { fileIn = ""; }

Decompressor::Decompressor(std::string fileIn): fileIn(fileIn) {}

void Decompressor::setFileIn (std::string fileIn)
{ 
	this->fileIn = fileIn; 
}

std::string Decompressor::getFileIn () 
{
	return fileIn;
}

bool Decompressor::wasClearlyDecompressed ()
{
	return clearDecompression;
}

bool Decompressor::decompress()
{
	if ( getFileIn() == "" )
		throw new std::exception("Specify a file name to decompress from!");
	fileOut = processFileName(fileIn);
	initDecompression();
}

void Decompressor::initDecompression ()
{
	std::ifstream read;
	std::ofstream write(fileOut);

	read.open(fileIn.c_str());

	if ( !read.fail() && !write.fail() )
	{
		std::string memory[4096];

		for (int i = 0; i < 256; i++)//first 255 = ascii table
			memory[i]  = std::string(1, (unsigned char)i);

		for (int i = 256; i < 4095; i++)
			memory[i] = "";

		decompress(read, write, memory);
	}
	read.close();
	write.close();
}

void Decompressor::decompress (std::ifstream& read, std::ofstream& write, std::string* memory)
{
	int OLD;
	unsigned char c;

	if ( (read >> OLD) && OLD >= 0 && OLD <= 255 )
	{
		write << memory[OLD] ;
		c = (char)OLD;
		livZempel(read, write, memory, c);
	}
	else
		throw new std::exception("This file cannot be decompressed by Ziv-Lempel");
}

void Decompressor::livZempel (std::ifstream& read, std::ofstream& write, std::string* memory, unsigned char& c)
{
	std::string line, original, word;
	int OLD, NEW, codeWord = 256;
	OLD = (int) c; 

	while ( !read.eof() )
	{
		if ( !(read >> NEW) )
		{
			read.clear();
			read.ignore();
			clearDecompression = false;
			continue; // if input was not an integer, ignore and continue
		}

		if ( IsExist(memory, NEW) )
			original = memory[NEW];
		else
			original = memory[OLD] + std::string(1,c);

		write << original ;

		c = original.at(0);

		if ( codeWord < 4096 )
		{
			word = memory[OLD] + std::string(1,c);
			memory[codeWord++] = word;
		}
		OLD = NEW;
	}
}