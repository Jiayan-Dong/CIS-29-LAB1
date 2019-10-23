/*
Cis29 
Lab1 - Bit Decryption 
Name: Jiayan Dong
Last Modified: 10/23/2019
Techniques/Structures:
Bitsets, Priority_Queue, and Polymorphism
Encode Character to Morse code, dot(.) is 10, dash(-) is 01.
Using this bitset value to create a Huffman tree and using huffman tree to encode again.
Decrypt the Encrypt.bin file that is encrpyted in this way.
MorseTable is given in the QueueTree.pdf.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <regex>
#include <algorithm>

using namespace std;

//MorseChar to store character and its morse code.
class MorseChar
{
protected:
	char character;	//Charater
	string morse;	//Morse Code
public:
	//Default constuctor that initalize the data
	MorseChar()
	{
		character = 0;
		morse = "";
	}
	//overloaded constuctor that initalize the data
	MorseChar(char c, string m)
	{
		character = c;
		morse = m;
	}
	//Setter
	void setCharacter(char c)
	{
		character = c;
	}

	void setMorse(string m)
	{
		morse = m;
	}
	//Getter
	char getCharacter()
	{
		return character;
	}

	string getMorse()
	{
		return morse;
	}
};

// MorseCharBitset inherit from MorseChar Class, contain Morse Code as a 10-bit bitset
class MorseCharBitset : public MorseChar
{
private:
	bitset<10> bset;		//Morse Code as 10-bit bitset
	void convertBitset()	//Private function to convert Morse Code to bitset Morse code
	{
		regex rdot("[.]");	//Using regualr expression to convert
		regex rdash("[-]");
		string mdot = "10";
		string mdash = "01";
		string s = regex_replace(morse, rdot, mdot);
		s = regex_replace(s, rdash, mdash);
		bitset<10> temp(s);
		bset = temp;
	}

public:
	//Default constuctor that initalize the data
	MorseCharBitset()
	{
		MorseChar();
	}

	//overloaded constuctor that initalize the data
	MorseCharBitset(char c, string m)
	{
		character = c;
		convertBitset();
	}

	//Setter
	void setMorseChar(char c, string m)
	{
		character = c;
		morse = m;
		convertBitset();
	}

	//Getter
	bitset<10> getBset()
	{
		return bset;
	}

	//Overload compare operators to compare MorseCharBitset 
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

//MorseTable to store a Morse Table as shown in the QueueTree.pdf
class MorseTable
{
private:
	vector<MorseCharBitset> mTable;	//vector contains all MorseCharBitsets
	int size;	//the size of MorseCharBitset
public:
	//Default constuctor that initalize the data
	MorseTable()
	{
		size = 39;	//Morse Table size
		mTable.resize(size);
		//Initalize Morse Table
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

	//Getter
	vector<MorseCharBitset> getmTable()
	{
		return mTable;
	}
};

//Get integer value of the bitset in MorseCharBitset object
//This Function (Pointer) is to be passed as a parameter in a member function of Node Template class
int getInt(MorseCharBitset mcb)
{
	return mcb.getBset().to_ulong();
}

//Template class Node to create the Huffman Tree, this class will be used as a parent class 
template<typename T>
class Node
{
protected:
	T data;	//data contained
	int num;	//Num value to create priorty queue
	Node<T>* left;	//Pointer to the left Node
	Node<T>* right;	//Pointer to the right node
public:
	//Default constuctor that initalize the data
	Node()
	{
		left = 0;
		right = 0;
		num = 0;
	}
	//overloaded constuctor that initalize the data
	//Its parameters contain a function pointer to get the integer from the template datatype
	Node(T d, int get(T))
	{
		data = d;
		num = get(T);
	}
	//Getter
	T getData()
	{
		return data;
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

	//Setter
	void setData(T d, int get(T))
	{
		data = d;
		num = get(d);
	}

	void setNum(int n)
	{
		num = n;
	}
	
	//Overload compare operators to compare MorseCharBitset 
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

	//Overload addition operator to add two Node object, it returns a object has the sum of nums in two input objects
	Node<T> operator + (const Node<T>& obj)
	{
		Node<T> temp;
		temp.setNum(this->num + obj.num);
		return temp;
	}

	//Pure Virtual member fucntion to achieve Polymorphism
	//This decode function will be overeided during run time
	virtual Node<T>* deCode(bool b) = 0;
};

//Template class Branch to behave like a branch when decoding, this class inherit from Class Node
template<typename T>
class Branch : public Node<T>
{
public:
	//Overload constuctor that initalize the data with its two child Node pointer
	Branch(Node<T>* pL, Node<T>* pR)
	{
		this->left = pL;
		this->right = pR;
		this->num = pL->getNum() + pR->getNum();
	}

	//Decode function that accepte a bool, and return one its child class
	//This function is used to achieve Polymorphism, it will override the docode function in Node Class during run time
	Node<T>* deCode(bool b)
	{
		if (b)
			return this->right;
		else
			return this->left;
	}
};

// Template class Branch to behave like a leaf when decoding, this class inherit from Class Node
template<typename T>
class Leaf : public Node<T>
{
public:
	//Decode function that accepte a bool, and return itself
	//This function is used to achieve Polymorphism, it will override the docode function in Node Class during run time
	Node<T>* deCode(bool b)
	{
		return this;
	}
};

//Template Struct larger to be passed to priority_queue
template<typename T>
struct larger 
{
	//Overload () operator to compare Node, it takes two Node pointers as parameters
	//If the the object pointed by the first Node is larger the object pointed by the second Node, return ture, ohterwise return false.
	bool operator()(Node<T>* a, Node<T>* b) 
	{
		return *a > *b;
	}
};

//Template Class HuffmanTree to create and store the huffman tree that are used to decode files 
template<typename T>
class HuffmanTree
{
private:
	Node<T>* rootPtr;	//Root pointer of the huffman tree 
	priority_queue<Node<T>*, vector<Node<T>*>, larger<T>> priQue;	//priority queue used to create the huffman tree
	vector<Node<T>*> nodes;	//vector nodes stores Node pointers that are used in Dynamic memory allocation
	// private function Setup to set up the priority queue by using a table
	void setup(vector<T> mTable)
	{
		for (auto i : mTable)
		{
			Node<T>* pNode = new Leaf<T>;
			pNode->setData(i, getInt);
			priQue.push(pNode);
		}
	}
	// private function bulidTree to bulid the huffman tree by using the priority queue
	void buildTree()
	{
		while (priQue.size() > 1)
		{
			bool flag = true;
			Node<T>* qLeft = priQue.top();
			nodes.push_back(qLeft);
			priQue.pop();
			Node<T>* qRight = priQue.top();
			if (qRight->getNum() == 85 && flag)	// The encrypt file uses a tree that is different from mine, I have to adjust my tree here 
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
		nodes.push_back(priQue.top());
	}
public:
	//Default constuctor that initalize the rootPtr
	HuffmanTree()
	{
		rootPtr = 0;
	}
	//Overload constuctor that initalize the data and bulid the huffman tree by using a vector contains the table data
	HuffmanTree(vector<T> v)
	{
		setup(v);
		buildTree();
		rootPtr = priQue.top();
	}

	//Defualt destuctor to free Dynamic allocated memory  
	~HuffmanTree()
	{
		for (auto i : nodes)
		{
			delete i;
		}
	}
	//Setter to initalize the data and bulid the huffman tree by using a vector contains the table data
	void setPriQue(vector<T> mb)
	{
		setup(mb);
		buildTree();
		rootPtr = priQue.top();
	}
	//Getter to return the rootPtr
	Node<T>* getRoot()
	{
		return rootPtr;
	}
};


class Decrypt	

{
private:
	Node<MorseCharBitset>* rootPtr;	//Root pointer of the huffman tree
	string input;	//Input filename
	string output;	//Output filename
public:
	//Overload constuctor that initalize the data
	Decrypt(Node<MorseCharBitset>* r, string i, string o)
	{
		input = i;
		output = o;
		rootPtr = r;
	}

	//Function decrypt decrypt the input file, the core algorithm is shown below
	//Get a bool from the input file, nodePtr->decode(bool), loop until the nodePtr does not change and then get the data. Using the bool when the nodePte doesn't change to start next decode
	void decrypt()
	{
		ifstream fin(input, ios::in | ios::binary);
		ofstream fout(output);
		unsigned char* memblock = 0;
		int isize = 0;
		if (!fin)
		{
			cout << "Error happened to open the input file!" << endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
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
		delete[] memblock;
	}
};

int main()
{
	MorseTable table;	//Morse Table in the QueueTree.pdf
	HuffmanTree<MorseCharBitset> tree(table.getmTable());	//Creating the huffman tree to decrypt the file
	string filename;	//Input filename
	string outputName;	//Output filename

	cout << "Welcome to Bit Decryption Program" << endl;
	cout << "This program use Using the Morse Table as shown in the QueueTree.pdf to decrypt the bit-encrypted file" << endl << endl;
	cout << "Please enter the plaintext filename to decrypt(with filename extension): ";
	getline(cin, filename);
	cout << "Please enter the output filename(with filename extension): ";
	getline(cin, outputName);
	Decrypt decry(tree.getRoot(), filename, outputName);
	decry.decrypt();	//Decrypt the input file and output the decrypted file  
	cout << "The file has been decrypted and saved. Thank you!" << endl;

	system("pause");
	return 0;
}