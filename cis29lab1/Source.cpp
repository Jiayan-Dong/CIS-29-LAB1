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
#include <regex>
#include <algorithm>

using namespace std;

class MorseChar
{
protected:
	char character;
	string morse;
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

	void setCharacter(char c)
	{
		character = c;
	}

	void setMorse(string m)
	{
		morse = m;
	}
};

class MorseCharBitset : public MorseChar
{
private:
	bitset<10> bset;
	void convertBitset()
	{
		regex rdot("[.]");
		regex rdash("[-]");
		string mdot = "10";
		string mdash = "01";
		string s = regex_replace(morse, rdot, mdot);
		s = regex_replace(s, rdash, mdot);
		bitset<10> temp(s);
		bset = temp;
	}

public:
	MorseCharBitset()
	{
		MorseChar();
	}

	MorseCharBitset(char c, string m)
	{
		MorseChar(c, m);
		convertBitset();
	}

	void setMorseChar(char c, string m)
	{
		character = c;
		morse = m;
		convertBitset();
	}

	bitset<10> getBset()
	{
		return bset;
	}

	bool operator < (const MorseCharBitset &mcb)
	{
		return this->bset.to_ulong() < mcb.bset.to_ulong();
	}

	bool operator == (const MorseCharBitset& mcb)
	{
		return this->bset.to_ulong() == mcb.bset.to_ulong();
	}

	bool operator > (const MorseCharBitset& mcb)
	{
		return this->bset.to_ulong() > mcb.bset.to_ulong();
	}
};

class MorseTable
{
private:
	vector<MorseCharBitset> mTable;
	int size;
public:
	MorseTable()
	{
		size = 39;	//Morse Table size
		mTable.resize(size);

		mTable[0].setMorseChar(' ', "..--");
		mTable[1].setMorseChar(',', "----");
		mTable[2].setMorseChar('.', "---.");
		mTable[3].setMorseChar('0', "-----");
		mTable[4].setMorseChar('1', ".----");
		mTable[5].setMorseChar('2', "..---");
		mTable[6].setMorseChar('3', "...--");
		mTable[7].setMorseChar('4', "....-");
		mTable[8].setMorseChar('5', ".....");
		mTable[9].setMorseChar('6', "-....");
		mTable[10].setMorseChar('7', "--...");
		mTable[11].setMorseChar('8', "---..");
		mTable[12].setMorseChar('9', "----.");
		mTable[13].setMorseChar('A', ".-");
		mTable[14].setMorseChar('B', "-...");
		mTable[15].setMorseChar('C', "-.-.");
		mTable[16].setMorseChar('D', "-..");
		mTable[17].setMorseChar('E', ".");
		mTable[18].setMorseChar('F', "..-.");
		mTable[19].setMorseChar('G', "--.");
		mTable[20].setMorseChar('H', "....");
		mTable[21].setMorseChar('I', "..");
		mTable[22].setMorseChar('J', ".---");
		mTable[23].setMorseChar('K', "-.-");
		mTable[24].setMorseChar('L', ".-..");
		mTable[25].setMorseChar('M', "--");
		mTable[26].setMorseChar('N', "-.");
		mTable[27].setMorseChar('O', "---");
		mTable[28].setMorseChar('P', ".--.");
		mTable[29].setMorseChar('Q', "--.-");
		mTable[30].setMorseChar('R', ".-.");
		mTable[31].setMorseChar('S', "...");
		mTable[32].setMorseChar('T', "-");
		mTable[33].setMorseChar('U', "..-");
		mTable[34].setMorseChar('V', "...-");
		mTable[35].setMorseChar('W', ".--");
		mTable[36].setMorseChar('X', "-..-");
		mTable[37].setMorseChar('Y', "-.--");
		mTable[38].setMorseChar('Z', "--..");
	}

	vector<MorseCharBitset> getmTable()
	{
		return mTable;
	}
};

int getInt(MorseCharBitset mcb)
{
	return mcb.getBset().to_ulong();
}

template<typename T>
class Node
{
protected:
	T data;
	int num;
	Node<T>* left;
	Node<T>* right;
public:
	Node()
	{
		left = 0;
		right = 0;
		num = 0;
	}

	Node(T d, int get(T))
	{
		data = d;
		num = get(T);
	}

	T getData()
	{
		return T;
	}

	void setData(T d, int get(T))
	{
		data = d;
		num = get(T);
	}

	void setNum(int n)
	{
		num = n;
	}

	int getNum()
	{
		return num;
	}

	Node<T>* getLeft()
	{
		return left;
	}

	Node<T>* getRight()
	{
		return right;
	}

	bool operator > (const Node& obj)
	{
		return this->num > obj.num;
	}

	bool operator == (const Node& obj)
	{
		return this->num == obj.num;
	}

	bool operator < (const Node& obj)
	{
		return this->num < obj.num;
	}

	Node<T> operator + (const Node& obj)
	{
		Node<T> temp;
		temp.setNum(this->num + obj.num);
		return temp;
	}

	virtual Node<T>* deCode(bool b)
	{

	}
};

template<typename T>
class Branch : public Node<T>
{
public:
	Branch(Node<T>* pL, Node<T>* pR)
	{
		left = pL;
		right = pR;
		this->num = pL->getNum() + pR->getNum();
	}
	
	Node<T>* deCode(bool b)
	{
		if (b)
			return this->right;
		else
			return this->left;
	}
};

template<typename T>
class Leaf : public Node<T>
{
public:
	Node<T>* deCode(bool b)
	{
		return this;
	}
};



template<typename T>
class HuffmanTree
{
private:
	Node<T>* rootPtr;
	priority_queue<Node<T>, vector<Node<T>>, greater<Node<T>>> priQue;
	void setup(vector<MorseCharBitset> mTable)
	{
		for (auto i : mTable)
		{
			Node<T>* pNode = new Leaf<T>(i, getInt);
			priQue.push(*pNode);
		}
	}

	void buildTree()
	{
		Node<T>* qLeft;
		Node<T>* qRight;
		while (priQue.size() > 1)
		{
			qLeft = &priQue.top();
			priQue.pop();
			qRight = &priQue.top();
			priQue.pop();
			Node<T>* pNode = new Branch<T>(qLeft, qRight);
			priQue.push(pNode);
		}
	}
public:
	HuffmanTree()
	{
		rootPtr = 0;
	}

	HuffmanTree(vector<MorseCharBitset> mb)
	{
		rootPtr = 0;
		setup(mb);
	}

	void setPriQue(vector<MorseCharBitset> mb)
	{
		setup(mb);
	}

};


class Decrypt	//Get a bool from the input file, nodePtr->decode(bool), loop until the nodePtr does not change and then get the data.
				//Using the bool when the nodePte doesn't change to start next decode
{

};

int main()
{
	MorseTable table;
	HuffmanTree<MorseCharBitset*> tree(table.getmTable());
	cout << "Hello world" << endl;
	return 0;
}