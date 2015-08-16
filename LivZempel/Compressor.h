#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "HashTable.h"
#include <string>

class Compressor {

public:
	Compressor();
	Compressor(std::string fileIn);

	void setFileIn(const std::string fileIn);
	std::string getFileIn();

	void compress();

private:
	HashTable hashTable;
	std::string fileIn;
	std::string fileOut;

	void compress(std::ifstream&, std::ofstream&);
};

#endif // COMPRESSOR_H