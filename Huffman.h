//Huffman.h
#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

#ifndef Huffman_h
#define Huffman_h

using namespace std;

struct Node {
	string st;
	int fq;
	Node* l;
	Node* r;
};

Node* makeNode (string st, int fq, Node* l, Node* r);

struct greaterNode{
	bool operator() (Node* l, Node* r){
		if(l->fq == r->fq && l->st.length()==1 && r->st.length()==1 )
		{
			return *(l->st.c_str()) > *(r->st.c_str());
		}
		return l->fq > r->fq;
	}
};


class Huffman{
	
public:
	//variables for the Huffman Tree
	unordered_map <string, int> freq;
	priority_queue<Node*,vector<Node*>, greaterNode> pri_queue;
	Node* root;
	int num_of_characters;
	char* letters;
	unordered_map <char, string> codes;

	//constructor
	Huffman();

	//Huffman functions
	void buildHuffmanTree(char* , int* , int);
	void printCodes();
	std::string findCode(Node*, string, const char);
	void decodeText(const char *);
	std::string findDecodedletter(string);

};

#endif