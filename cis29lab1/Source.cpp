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

	char getCharacter()
	{
		return character;
	}

	string getMorse()
	{
		return morse;
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
		s = regex_replace(s, rdash, mdash);
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
		return data;
	}

	void setData(T d, int get(T))
	{
		data = d;
		num = get(d);
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

	bool operator > (const Node<T>& obj)
	{
		return this->num > obj.num;
	}

	bool operator == (const Node<T>& obj)
	{
		return this->num == obj.num;
	}

	bool operator < (const Node<T>& obj)
	{
		return this->num < obj.num;
	}

	Node<T> operator + (const Node<T>& obj)
	{
		Node<T> temp;
		temp.setNum(this->num + obj.num);
		return temp;
	}

	virtual Node<T>* deCode(bool b)
	{
		return NULL;
	}
};

template<typename T>
class Branch : public Node<T>
{
public:
	Branch(Node<T>* pL, Node<T>* pR)
	{
		this->left = pL;
		this->right = pR;
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
struct larger 
{
	bool operator()(Node<T>* a, Node<T>* b) 
	{
		return *a > *b;
	}
};


template<typename T>
class HuffmanTree
{
private:
	Node<T>* rootPtr;
	priority_queue<Node<T>*, vector<Node<T>*>, larger<T>> priQue;
	vector<Node<T>*> nodes;
	void setup(vector<T> mTable)
	{
		for (auto i : mTable)
		{
			Node<T>* pNode = new Leaf<T>;
			pNode->setData(i, getInt);
			priQue.push(pNode);
		}
	}

	void buildTree()
	{
		while (priQue.size() > 1)
		{
			bool flag = true;
			Node<T>* qLeft = priQue.top();
			nodes.push_back(qLeft);
			priQue.pop();
			Node<T>* qRight = priQue.top();
			if (qRight->getNum() == 85 && flag)
			{
				priQue.pop();
				priQue.push(qRight);
				qRight = priQue.top();
				flag = false;
			}
			nodes.push_back(qRight);
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

	HuffmanTree(vector<T> mb)
	{
		setup(mb);
		buildTree();
		rootPtr = priQue.top();
	}

	void setPriQue(vector<T> mb)
	{
		setup(mb);
		buildTree();
		rootPtr = priQue.top();
	}

	Node<T>* getRoot()
	{
		return rootPtr;
	}
};


class Decrypt	//Get a bool from the input file, nodePtr->decode(bool), loop until the nodePtr does not change and then get the data.
				//Using the bool when the nodePte doesn't change to start next decode
{
private:
	Node<MorseCharBitset>* rootPtr;
	string input;
	string output;
public:
	Decrypt(Node<MorseCharBitset>* r, string i, string o)
	{
		input = i;
		output = o;
		rootPtr = r;
	}

	void de()
	{
		ifstream fin(input, ios::in | ios::binary);
		ofstream fout(output);
		unsigned char* memblock = 0;
		int isize = 0;
		if (fin.is_open())
		{
			fin.seekg(0, ios::end);
			streampos size;
			size = fin.tellg();
			isize = size;
			memblock = new unsigned char[size];
			fin.seekg(0, ios::beg);
			fin.read((char*)memblock, size);
		}
		Node<MorseCharBitset>* nP1 = rootPtr;
		Node<MorseCharBitset>* nP2 = rootPtr;
		for (int i = 0; i < isize; i++)
		{
			bitset<8> bset(memblock[i]);
			for (int j = 7; j >=0; j--)
			{
				bool b = bset[j];
				nP2 = nP1->deCode(b);
				if (nP2 != nP1)
					nP1 = nP2;
				else
				{
					fout << nP1->getData().getCharacter();
					j++;
					nP1 = rootPtr;
					nP2 = rootPtr;
				}
			}
		}
		
	}
};

int main()
{
	MorseTable table;
	HuffmanTree<MorseCharBitset> tree(table.getmTable());
	Decrypt decry(tree.getRoot(), "Encrypt.bin", "Output.txt");
	decry.de();
	cout << "Hello world" << endl;
	return 0;
}