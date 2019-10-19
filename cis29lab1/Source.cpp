/*
Cis29 Lab1
Name: Jiayan Dong
Last Modified: 10/13/2019
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <tuple>
#include <algorithm>
#include <regex>

using namespace std;
/*
class MorseChar
{
private:
	char character;
	string morse;
	bitset<10> bSet;
public:
	MorseChar()
	{
		character = 0;
		morse = "";
	}
	MorseChar(char c, string m)
	{
		character = c;
		morse = m;
	}
	void setMorseChar()
	{

	}
};
*/
class MorseTable
{
private:
	vector<tuple<char, string, bitset<10>>> mTable;
	int size;
	pair<char, string> dash;
	pair<char, string> dot;

	void setup()
	{
		regex rdash("-");
		regex rdot("/.");
		string s;
		for (int i = 0; i < 39; i++)
		{
			s = get<1>(mTable[i]);
			s = regex_replace(s, rdash, dash.second);
			s = regex_replace(s, rdot, dot.second);
			get<2>(mTable[i]) = bitset<10>(s);
		}
	}
public:
	MorseTable()
	{
		size = 39;	//Morse Table size
		mTable.resize(size);
		dash.first = '-';
		dash.second = "10"; //binary 01
		dot.first = '.';
		dot.second = "01"; //binary 10

		get<0>(mTable[0]) = ' ';	get<1>(mTable[0]) = "..--";
		get<0>(mTable[1]) = ',';	get<1>(mTable[0]) = "----";
		get<0>(mTable[2]) = '.';	get<1>(mTable[0]) = "---.";
		get<0>(mTable[3]) = '0';	get<1>(mTable[0]) = "-----";
		get<0>(mTable[4]) = '1';	get<1>(mTable[0]) = ".----";
		get<0>(mTable[5]) = '2';	get<1>(mTable[0]) = "..---";
		get<0>(mTable[6]) = '3';	get<1>(mTable[0]) = "...--";
		get<0>(mTable[7]) = '4';	get<1>(mTable[0]) = "....-";
		get<0>(mTable[8]) = '5';	get<1>(mTable[0]) = ".....";
		get<0>(mTable[9]) = '6';	get<1>(mTable[0]) = "-....";
		get<0>(mTable[10]) = '7';	get<1>(mTable[0]) = "--...";
		get<0>(mTable[11]) = '8';	get<1>(mTable[0]) = "---..";
		get<0>(mTable[12]) = '9';	get<1>(mTable[0]) = "----.";
		get<0>(mTable[13]) = 'A';	get<1>(mTable[0]) = ".-";
		get<0>(mTable[14]) = 'B';	get<1>(mTable[0]) = "-...";
		get<0>(mTable[15]) = 'C';	get<1>(mTable[0]) = "-.-.";
		get<0>(mTable[16]) = 'D';	get<1>(mTable[0]) = "-..";
		get<0>(mTable[17]) = 'E';	get<1>(mTable[0]) = ".";
		get<0>(mTable[18]) = 'F';	get<1>(mTable[0]) = "..-.";
		get<0>(mTable[19]) = 'G';	get<1>(mTable[0]) = "--.";
		get<0>(mTable[20]) = 'H';	get<1>(mTable[0]) = "....";
		get<0>(mTable[21]) = 'I';	get<1>(mTable[0]) = "..";
		get<0>(mTable[22]) = 'J';	get<1>(mTable[0]) = ".---";
		get<0>(mTable[23]) = 'K';	get<1>(mTable[0]) = "-.-";
		get<0>(mTable[24]) = 'L';	get<1>(mTable[0]) = ".-..";
		get<0>(mTable[25]) = 'M';	get<1>(mTable[0]) = "--";
		get<0>(mTable[26]) = 'N';	get<1>(mTable[0]) = "-.";
		get<0>(mTable[27]) = 'O';	get<1>(mTable[0]) = "---";
		get<0>(mTable[28]) = 'P';	get<1>(mTable[0]) = ".--.";
		get<0>(mTable[29]) = 'Q';	get<1>(mTable[0]) = "--.-";
		get<0>(mTable[30]) = 'R';	get<1>(mTable[0]) = ".-.";
		get<0>(mTable[31]) = 'S';	get<1>(mTable[0]) = "...";
		get<0>(mTable[32]) = 'T';	get<1>(mTable[0]) = "-";
		get<0>(mTable[33]) = 'U';	get<1>(mTable[0]) = "..-";
		get<0>(mTable[34]) = 'V';	get<1>(mTable[0]) = "...-";
		get<0>(mTable[35]) = 'W';	get<1>(mTable[0]) = ".--";
		get<0>(mTable[36]) = 'X';	get<1>(mTable[0]) = "-..-";
		get<0>(mTable[37]) = 'Y';	get<1>(mTable[0]) = "-.--";
		get<0>(mTable[38]) = 'Z';	get<1>(mTable[0]) = "--..";

		setup();
	}

	int getSize()
	{
		return size;
	}

	vector<tuple<char, string, bitset<10>>> getmTable()
	{
		return mTable;
	}
};

template <typename T>
class HashTable
{
private:
	vector<T> table;
	int hash(int num) const
	{
		return num;
	}
	int count;
	int size;
public:
	HashTable()
	{
		count = 0;
		size = 682; //binary 1010101010 = decimal 682
		table.resize(682);
	}

	HashTable(int s)
	{
		count = 0;
		size = s;
		table.resize(s);
	}

	int getCount()
	{
		return count;
	}

	int getSize()
	{
		return size;
	}

	bool insert(T item, int get(T&))
	{
		int key = get(item);
		int hashValue = hash(key);
		if (table[hashValue] == NULL)
		{
			count++;
			return true;
		}
		else
			return false;
	}

	bool remove(T item, int get(T&))
	{
		int key = get(item);
		int hashValue = hash(key);
		if (table[hashValue] != NULL)
		{
			table[hashValue] = NULL;
			count--;
			return true;
		}
		else
			return false;
	}

	bool search(T item, T& returnvalue, int get(T&))
	{
		int key = get(item);
		int hashValue = hash(key);
		if (table[hashValue] != NULL)
		{
			returnvalue = table[hashValue];
			return true;
		}
		else
			return false;
	}

	bool quickSearch(int hash, T& returnvalue)
	{
		if (table[hash] != NULL)
		{
			returnvalue = table[hash];
			return true;
		}
		else
			return false;
	}
};

template <typename T>
class Node
{
private:
	T data;
	Node<T>* left;
	Node<T>* right;
public:
	Node()
	{

	}

	Node(T d)
	{
		data = d;
	}

	~Node()
	{

	}

	T getData()
	{
		return data;
	}

	void setData(T d)
	{
		data = d;
	}

	virtual Node* deCode() = 0;
};

template <typename T>
class Branch : public Node<T>
{
public:
	Node<T>* deCode(bool bin)
	{
		if (bin)
			return right;
		else
			return left;
	}
};

template <typename T>
class Leaf: public Node<T>
{
public:
	Node<T>* deCode(bool bin)
	{
		return this;
	}
};

class HuffmanTree
{
private:
	Node<int>* rootPtr;
	priority_queue<int, vector<int>, greater<int>> priQue;
public:
	HuffmanTree()
	{

	}

	~HuffmanTree()
	{

	}
	
	Node<int>* decode(bool)
	{

	}
};

class Decrypt	//Get a bool from the input file, nodePtr->decode(bool), loop until the nodePtr does not change and then get the data.
				//Using the bool when the nodePte doesn't change to start next decode
{

};

int main()
{
	int* a;
	cout << "Hello world" << endl;
	return 0;
}