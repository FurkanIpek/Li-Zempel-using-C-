/***************************************************************
 *       Compresses any txt file using LZW algorithm           *
 *                                                             *
 *         Created by: Mehmet Furkan İpek                      *
 ***************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include "Compressor.h"
#include "Decompressor.h"
#include <iostream>
#include <string>

int main ()
{
	std::string file = "compin.txt";
	/* An example run */
	Compressor compressor(file);
	// compressed files will have a .fz extension
	Decompressor decompressor("compin.fz");

	compressor.compress();
	decompressor.decompress();

	if ( decompressor.wasClearlyDecompressed() )
		std::cout << "Successfully compressed & decompressed!" ;

	return 0;
}