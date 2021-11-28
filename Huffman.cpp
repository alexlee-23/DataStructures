//Alex Lee alee23@bu.edu
//Collaborator Dabin Jang djang12@bu.edu

//references: 
//range based for loops-> https://www.tutorialspoint.com/how-to-use-range-based-for-loop-with-std-map
//         type inference (auto)-> https://www.geeksforgeeks.org/type-inference-in-c-auto-and-decltype/
//structs -> https://stackoverflow.com/questions/54585/when-should-you-use-a-class-vs-a-struct-in-c
//priority queue -> https://www.cplusplus.com/reference/queue/priority_queue/
//			comparaotr function for min heap priority queue -> https://stackoverflow.com/questions/5733254/how-can-i-create-my-own-comparator-for-a-map
//min heap--> https://www.geeksforgeeks.org/implement-min-heap-using-stl/

#include "Huffman.h"
#include <iomanip>
/*
#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
*/
using namespace std;


//Huffman Tree will be built with nodes therefore we must make a struct of Nodes
/////////////Each Node struct will have hold a character NUM(0 or 1), integer FREQ, and pointer to left and right
/*
struct Node {
	string st;
	int fq;
	Node* left;
	Node* right;
};
*/
/*
bool greaterNode::operator() (Node* l, Node* r){
	bool bigger = l->fq > r->fq;
	return bigger;
}
*/

Node* makeNode (string st, int fq, Node* l, Node* r)
{
	Node* newNode = new Node();

	newNode->st = st;
	newNode->fq = fq;
	newNode->l = l;
	newNode->r = r;

	return newNode;
}

//HUFFMAN CLASS FUNCTIONS BELOW
Huffman::Huffman(){
	unordered_map <string, int> freq;
	priority_queue<Node*,vector<Node*>, greaterNode> pri_queue;
	unordered_map <char, string> codes;
	this->root = nullptr;
	this->freq = freq;
	this->pri_queue = pri_queue;
	this->codes=codes ;
	this->num_of_characters=0;
	this->letters=nullptr;
}


void Huffman::buildHuffmanTree(char* letters, int* frequency , int size){
	int sum_freq;
	string characters;
	char temp;
	
	this->num_of_characters = size;
	this->letters = letters;

	for (int i=0; i < size ; i++)
	{
		std::string letter(1,letters[i]);
		this->freq[letter] = frequency[i];
		letter = "";
	}
	
	for (auto freq_pair : freq)
	{
		this->pri_queue.push(makeNode(freq_pair.first, freq_pair.second, nullptr, nullptr));
	}
	
	
	while (this->pri_queue.size() != 1)
	{

		Node* left = this->pri_queue.top(); 
		this->pri_queue.pop();
		Node* right = this->pri_queue.top(); 
		this->pri_queue.pop();
		Node* temp = this->pri_queue.top();

		if (temp->st.length() > right->st.length() && temp->fq == right->fq)
		{
			Node* putbacktemp;
			this->pri_queue.pop();
			putbacktemp = right;
			right = temp;
			temp = putbacktemp;
			this->pri_queue.push(temp);

		}
		

		sum_freq = left->fq + right->fq;

		characters = left->st + right->st;
		this->pri_queue.push(makeNode(characters,sum_freq,left,right));
		characters = "";

	}
	this->root = this->pri_queue.top();
}

void Huffman::printCodes(){
	Node* current = this->root;

	if (root == nullptr)
		cout << "No Huffman tree exists" << endl;
	else{
		for (int i = 0; i < this->num_of_characters; i++)
		{
			char code = this->letters[i];
			string huffcode = this->findCode(current,"",code);
			this->codes.insert(std::make_pair(code,huffcode));
			huffcode = "";
		}
	}
	cout<< setw(15)<< left <<"Huffman Code" << setw(15) << left <<"Code"<<endl;
	cout<< "_________________________________________________________"<<endl;
	for (auto pair : this->codes)
	{
		cout<< setw(15) <<pair.second << set(15) << pair.first<<endl; 
	}
}


std::string Huffman::findCode(Node* current, string huffcode, const char code){
	while (current->l !=nullptr && current->r !=nullptr){
		if (current->st.find(code) != std::string::npos){
			if (current->l->st.find(code) != std::string::npos){
				current = current->l;
				huffcode = huffcode+"0";
			}
			else if (current->r->st.find(code) != std::string::npos){
				current = current->r;
				huffcode = huffcode+"1";
			}
		}
		else
			break;
	}
	return huffcode;
}

void Huffman::decodeText(const char* file){
	std::ifstream myfile(file);
	string line;
	string decoded;

	cout<<"\n The decoded text is:  ";
	while (std::getline(myfile,line)){
		string decoded;
		decoded = findDecodedletter(line);
		cout << decoded << endl;
	}
	myfile.close();
}

std::string Huffman::findDecodedletter(string line){
	int sizeofword = line.length();
	int index = 0;
	Node* current;
	string decoded("");

	while (index<sizeofword){
		current = this->root;
		while (current->l !=nullptr && current->r !=nullptr){
			if (line[index] == '0'){
				current = current->l;
				index++;
			}
			else if (line[index] == '1'){
				current = current->r;
				index++;
			}
		}
		decoded = decoded + current->st;
	}
	return decoded;
}




