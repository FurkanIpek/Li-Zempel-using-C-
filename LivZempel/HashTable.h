#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

class HashTable
{

enum EntryType {ACTIVE, EMPTY, DELETED};

public:
	HashTable ();
	void Insert (int, std::string);
	bool IsExist (std::string) const;
	bool IsExist (int) const;
	int Encode (std::string);
	std::string Decode (int);
	bool IsFull () { return full; }

private:
	struct HashEntry
	{
		std::string key;
		int code;
		EntryType info;

		HashEntry () { key = ""; code = -1; info = EMPTY; }
	};

	HashEntry HashArray [4096];
	bool full;

	int Hash (std::string) const;
	void LinearProb(std::string, int&, int);

};

#endif // HASHTABLE_H