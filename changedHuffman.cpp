// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Huffman coding tree example program.
// First, read from the data file a set of strings and associated
// frequencies. These are placed onto a list of (single node) Huffman trees.
// Next, build a single Huffman coding tree for the set.  The strings and
// their codes are then output, with CodeTable storing the coding for
// each input string. Next, read commands to "encode" or "decode" strings,
// providing the appropriate output.

// Sample input files are supplied with this distribution, they are
// named "*.huff".

// This implementation uses a standard "tree in control" design.
// This shows up mostly in the encode/decode functions.
// In contrast, see huffman1 which implements a composite design.

#include "book.h"
#include "PriorityQueue__HuffTreeIntMin.cpp"
#include "Object__HuffTreeInt.cpp"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>

// Include definition for heaps
// We will use them to keep track of the forest of huffman trees during the
// building operation
#include "heap.h"

#define MAXCODELEN 20       // Max length of a huffman code
#define CODETABLELEN 100    // Maximum number of codes storable

// CodeTable maps objects to their associated codes.
template <typename E>
class CodeTable {
private:
  E* obs;     // Objects
  char** codes;  // Associated code values
  int currsize;  // Current number of objects in table
  int maxsize;   // Max objects permitted in table
public:
  CodeTable(int size) {
    obs = new E[size];
    codes = new char*[size];
    for (int i = 0; i<size; i++) {
      codes[i] = new char[MAXCODELEN+1];
      for(int j=0; j<=MAXCODELEN; j++)
        codes[i][j] = '-';
	codes[i][MAXCODELEN] = '\0';
      }
    maxsize = size;  currsize = 0;
  }

  void addobject(E& obj) {
    Assert(currsize < maxsize, "CodeTable is full!");
    obs[currsize++] = obj;
  }

  char* getcode(E obj) {
    for (int i=0; i<currsize; i++)
      if(obj == obs[i]) return codes[i];
    return NULL;
  }
};  

#include "huffnode.h"

template <typename E>
ostream& operator << (ostream& s, HuffNode<E>* z)
{
  if (z->isLeaf())
    return s << ((LeafNode<E>*)z)->val();
  else
    return s << z->weight();
}

#include "hufftree.h"

// Overload for the HuffTree << operator
template <typename E>
ostream& operator << (ostream& s, HuffTree<E>* z)
  { return s << z->weight(); }

// Read the list of frequencies, make the forest, and set the
// list of entries into the code table.
PriorityQueue__HuffTreeIntMin<char> read_freqs(CodeTable<char>* ct, FILE* fp)
{ // Read a list of strings and frequencies from standard input,
	// building a list of Huffman coding tree nodes
	char buff[100];
	char buff2[100];
	char *ptr;
	char *ptr2;
	int freq;
	size_t length;

	Assert(fgets(buff, 99, fp) != NULL,   // Read number of chars
		   "Couldn't read character count");
	ptr = buff;
	Assert(isdigit(*ptr) != 0, "Must be a digit here.");
	int count = atoi(ptr);
	
	Object__HuffTreeInt<char>* objectArray = new Object__HuffTreeInt<char>[count];
	PriorityQueue__HuffTreeIntMin<char> forest = PriorityQueue__HuffTreeIntMin<char>(objectArray, 0, count);
	
	for (int i=0; i<count; i++) { // Read in the frequencies
		Assert(fgets(buff, 99, fp) != NULL, "Ran out of codes too early");  // Read the next entry
		
		// process the entry, creating a new HuffTree
		for(ptr=buff; *ptr==' '; ptr++);  // Read first word
		Assert(*ptr == '"', "First char was not a quote mark.");
		
		for (ptr2=buff2,ptr++; *ptr!='"'; ptr++)
		  *ptr2++ = *ptr;
		*ptr2 = '\0'; // End of string
		
		for (ptr++; *ptr==' '; ptr++);
		Assert(isdigit(*ptr) != 0, "Must be a digit here.");
		freq = atoi(ptr);
		length = strlen(buff2);
		ct->addobject(buff2[0]);
		forest.enqueue(Object__HuffTreeInt<char>(new HuffTree<char>(buff2[0], freq), freq));
	}
	return forest;
}

// Build a Huffman tree from a collection of frequencies
HuffTree<char>* buildHuff(PriorityQueue__HuffTreeIntMin<char> forest) {
	
	HuffTree<char> *temp1, *temp2, *temp3 = NULL;
	while (forest.size() > 1) {
		temp1 = forest.dequeue().getID();   // Pull first two trees
		temp2 = forest.dequeue().getID();   //   off the list
		temp3 = new HuffTree<char>(temp1, temp2);
		forest.enqueue(Object__HuffTreeInt<char>(temp3,temp3->weight()));  // Put the new tree back on list
		delete temp1;        // Must delete the remnants
		delete temp2;        //   of the trees we created
	}
	return temp3;
}


void decode(HuffTree<char>* theTree, char* code, char& msg, int& cnt) {
  HuffNode<char>* currnode = theTree->root();
  while (!currnode->isLeaf()) {
    cnt++;
    if (code[cnt-1] == '0') currnode = ((IntlNode<char>*)currnode)->left();
    else if (code[cnt-1] == '1') currnode = ((IntlNode<char>*)currnode)->right();
	else Assert(false, "Bad code character");
  }
  msg = ((LeafNode<char>*)currnode)->val();
}

void buildcode(HuffNode<char>* root, int totalWeight, CodeTable<char>* ct, char* prefix, int level, double& total, double& entropy) {
	if (root->isLeaf()) {
		cout << ((LeafNode<char>*)root)->val() << "\t" << prefix << "\n";
		strcpy(ct->getcode(((LeafNode<char>*)root)->val()), prefix);
		total += level * root->weight();
		entropy -= log2(float(root->weight())/totalWeight)*(float(root->weight())/totalWeight);
	}
	else {
		prefix[level] = '0';
		prefix[level+1] = '\0';
		buildcode(((IntlNode<char>*)root)->left(), totalWeight, ct, prefix, level+1, total, entropy);
		prefix[level] = '1';
		prefix[level+1] = '\0';
		buildcode(((IntlNode<char>*)root)->right(), totalWeight, ct, prefix, level+1, total, entropy);
		prefix[level] = '\0';
	}
}


void do_commands(HuffTree<char>* theTree,
                 CodeTable<char>* theTable, FILE *fp)
{
  int currchar;
  char buff[80];

  while (fgets(buff, 99, fp)) {
    if (strncmp(buff, "decode", 6) == 0) {
      for (currchar=0; buff[currchar] != '"'; currchar++);
      cout << "Decode " << &buff[currchar++];
      while (buff[currchar] != '"') {
        int cnt = 0;
        char msg;
        decode(theTree, &buff[currchar], msg, cnt);
        cout << msg << endl;
	currchar += cnt;
      }
    }
    else if(strncmp(buff, "encode", 6) == 0) {
      for (currchar=0; buff[currchar] != '"'; currchar++);
      cout << "Encode " << &buff[currchar++];
      for(; buff[currchar] != '"' ; currchar++) // Assume codes are characters.  Should generalize this.
        if (buff[currchar] == ' ') cout << ' ';
        else cout << theTable->getcode(buff[currchar]);
    }
    cout << "\n";
  }
}


// Driver for testing Huffman tree code
int main(int argc, char** argv) {
	// This will be the eventual Huffman tree
	HuffTree<char>* theTree;
	CodeTable<char>* theTable = new CodeTable<char>(CODETABLELEN);
	// Working storage for the tree traversal that builds the code table
	char prefix[MAXCODELEN+1];
	// total is used to calculate the average code length
	double total = 0;
	double entropy = 0;
	FILE *fp;  // The file pointer

	// Check command line parameter for frequency file
	Assert(argc == 2, "Usage: huffman <frequency file>");
	Assert((fp = fopen(argv[1], "rt")) != NULL, "No such file");

	// Now, read in the list of frequencies, and initialize the
	//   forest of Huffman trees.
	cout << "Read frequencies\n";
	PriorityQueue__HuffTreeIntMin<char> forest = read_freqs(theTable, fp);

	//  forest->print();

	// Now, build the tree.
	cout << "Build the tree\n";
	theTree = buildHuff(forest);

	// Now, output the tree, which also creates the code table.
	cout << "Output the tree\n";
	buildcode(theTree->root(), theTree->root()->weight(), theTable, prefix, 0, total, entropy);
	cout << "Average code length is:\t\t" << total/(double)theTree->weight() << " bits\n";
	cout << "Entropy of code is:\t\t\t" << entropy << " Sh\n";

	// Finally, do the encode/decode commands to test the system.
	do_commands(theTree, theTable, fp);
	fclose(fp);
	return 0;
}
