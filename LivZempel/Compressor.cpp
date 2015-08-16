#include "Compressor.h"
#include <exception>
#include <fstream>//ifstream and ofstream
#include <sstream>//istringstream

/* HELPER FUNCTIONS */

const std::string getFileName (const std::string fileIn)
{
	int indexOfDot = fileIn.rfind('.');

	if ( indexOfDot == std::string::npos )
		return fileIn;
	return fileIn.substr(0, fileIn.rfind('.')) + ".fz";
}

/* MEMBER FUNCTIONS */

Compressor::Compressor() { fileIn = ""; }

Compressor::Compressor(std::string fileIn): fileIn(fileIn) {}

void Compressor::setFileIn (std::string fileIn)
{ 
	this->fileIn = fileIn; 
}

std::string Compressor::getFileIn () 
{
	return fileIn;
}

void Compressor::compress ()
{
	if ( getFileIn() == "" )
		throw new std::exception("Specify a file name to compress!");

	fileOut = getFileName(fileIn);

	std::ifstream read;
	std::ofstream write(fileOut);

	read.open(fileIn.c_str());

	if ( !read.fail() && !write.fail() )
		compress(read, write);

	read.close();
	write.close();
}

void Compressor::compress (std::ifstream& read, std::ofstream& write)
{
	std::string p = "";//p -> previousCodeWord
	int codeWord = 256;
	char c;//c -> currentCodeWord
	int lineCount = 0;

	read.get(c);
	p = c;//read the first character, record it to the p

	while ( !read.eof() )
	{	
		//read the rest of the characters and do the LZW thing!
		read.get(c);

		if (hashTable.IsExist(p + std::string(1, c)))
			p = p + std::string(1, c);
		else
		{
			std::string word = p + std::string(1, c);
				
			write << hashTable.Encode(p) << ' ' ;

			if (codeWord < 4096)//If dictionary gets full, just use the existing codes
			{
				hashTable.Insert(codeWord, word);
				codeWord++;
			}
			p = std::string(1, c);
		}
	}
}