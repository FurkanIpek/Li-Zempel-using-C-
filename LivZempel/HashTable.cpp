#include "HashTable.h"

HashTable::HashTable ()
{
	full = false;

	for (int i = 0; i < 256; i++)//first 255 = ascii table
	{
		HashArray[i].key  = std::string(1, (unsigned char)i);
		HashArray[i].code = i;
		HashArray[i].info = ACTIVE;
	}
}

void HashTable::Insert (int codeWord, std::string var)
{
	int hash = Hash(var);

	if (IsExist(var) == false && !full)//if string "var" is not on the list or list is not full
	{
		if (HashArray[hash].info != ACTIVE)
		{
			HashArray[hash].key  = var;
			HashArray[hash].code = codeWord;
			HashArray[hash].info = ACTIVE;
		}
		else
			LinearProb(var, hash, codeWord);
	}
}

bool HashTable::IsExist (std::string searchToken) const
{
	int    hash    = Hash(searchToken),
		startPoint = hash;

	do
	{
		if (HashArray[hash].key == searchToken)
			return true;

		hash++;
		hash = hash % 4096;
	} 
	while (HashArray[hash].info != EMPTY && hash != startPoint);

	return false;
}

bool HashTable::IsExist (int code) const
{
	if (code > 4095 || code < 0)//Guard against faulty input
		return false;

	return HashArray[code].info == ACTIVE;
}

int HashTable::Encode (std::string key)
{
	int    hash    = Hash(key),
		startPoint = hash;

	do
	{
		if (HashArray[hash].key == key)
			return HashArray[hash].code;

		hash++;
		hash = hash % 4096;
	} 
	while (HashArray[hash].info != EMPTY && hash != startPoint);

	return -1;//search was unsuccessful - revise your code
}

std::string HashTable::Decode (int code)
{
	if (code > 4095 || code < 0)//Guard against faulty input
		return "";

	return HashArray[code].key;
}

int HashTable::Hash (std::string var) const
{
	int length = var.length();
	int hash = 0;

	for (int i = 0; i < length; i++)
		hash += (int)((unsigned char)var.at(i));

	hash = (hash % 256) * pow(2, length-1);

	if ( hash > 4095 )
		hash = hash % 4096;

	if ( hash < 256 && length > 1 )//first 255 is for ascii table, so linear prob will eventually reach 256
		hash = 256;//do not bother to wait probing, directly go to the 256

	return hash;
}

void HashTable::LinearProb (std::string var, int& hash, int codeWord)
{
	int start = hash;
	
	while (HashArray[++hash].info == ACTIVE && hash % 4096 != start);//find an available slot on array

	if (hash != start)
	{
		HashArray[hash].key  = var;
		HashArray[hash].code = codeWord;
		HashArray[hash].info = ACTIVE;
	}
	else
		full = true;//Nowhere to put "var" to the table!
}