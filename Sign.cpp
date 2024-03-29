#include <iostream>
#include <fstream>
#include <locale>
#include "RSA.h"


using namespace std;

ifstream filein("message.txt");
ofstream fileout("message_out.txt");

bigint MurmurHash2(char* key, unsigned int len)
{
	const unsigned int m = 0x5bd1e995;
	const unsigned int seed = 0;
	const int r = 24;

	unsigned int h = seed ^ len;

	const unsigned char* data = (const unsigned char*)key;
	unsigned int k = 0;

	while (len >= 4)
	{
		k = data[0];
		k |= data[1] << 8;
		k |= data[2] << 16;
		k |= data[3] << 24;

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		data += 4;
		len -= 4;
	}

	switch (len)
	{
	case 3:
		h ^= data[2] << 16;
	case 2:
		h ^= data[1] << 8;
	case 1:
		h ^= data[0];
		h *= m;
	};

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}


int main()
{
	setlocale(LC_ALL, "");
	string message;
	filein >> message;
	cout << message << endl;
	bigint hash = MurmurHash2((char*)message.c_str(), message.size());
	cout << hash << endl;
	Keys _keys = calculateRSAKeys();
	bigint s = cryptData(hash, _keys._private);
	cout << s << endl;


}