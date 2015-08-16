#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <string>

class Decompressor {

public:
	Decompressor();
	Decompressor(std::string fileIn);

	void setFileIn(const std::string fileIn);
	std::string getFileIn();

	bool wasClearlyDecompressed();

	bool decompress();

private:
	std::string fileIn;
	std::string fileOut;
	// will be set to false if decompressed file has non-integer words
	bool clearDecompression;

	void initDecompression();
	void decompress(std::ifstream&, std::ofstream&, std::string*);
	void livZempel(std::ifstream&, std::ofstream&, std::string*, unsigned char& c);
};

#endif // DECOMPRESSOR_H