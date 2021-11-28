//Alex Lee alee23@bu.edu
//Collaborators : Dabin Jang djang12@bu.edu

//*************** Trie Class and Node Class ***************//
class Node {

	public:
		bool isWord;
		unordered_map <char,Node*> children;
		Node ()
		{
			this->isWord = false;
		}
		unordered_map <char, Node*> returnChildren( ){
			return this->children;
		}

		void appendLetter(char letter)
		{
			Node* newNode = new Node();
			this->children.insert({letter, newNode});
		}

};

class Trie {
	public:
		Node* root;

		//constructor: only make a root node, which will always be null aka '\0'
		Trie ()
		{
			this-> root = new Node();	
		}

		void insertWord(string word)
		{
			Node* current = this->root;
			int wordLength = word.length();
			char letter;
			char x;
			for (int i = 0; i < wordLength ; i++)
			{
				letter = word[i];
				x = letter;
				if ((int)x>=65 && (int)x<=90){
					letter = letter + ' ';
				}
				cout << endl << letter << endl; 
				if(current->children.find(letter) == current->children.end() ){current->appendLetter(letter);
				current = (current->children)[letter];}
			}
			current->isWord = true;
		}

		bool searchWord(string word){
			Node* current = this->root;
			int wordLength = word.length();
			char letter;
			char x;
			for (int i = 0; i < wordLength ; i++)
			{
				letter = word[i];
				x = letter;
				if ((int)x>=65 && (int)x<=90){
					letter = letter + ' ';
				}
				if(current->children.find(letter) == current->children.end()) 
					return false;
				else 
					current = (current->children)[letter];
			}
			if (current->isWord == true) return true;
			else
				return false;
		}
};