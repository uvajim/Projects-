#ifndef NODE_H
#define  NODE_H

#include <string>
#include <iostream>

using namespace std; 

class Node{

private:

	string board;
	Node* previous;
	int move;

public:
	Node ();

	Node(string state, Node *prev, int n);

	Node* getPrev();

	string getState();

	int getMove();


};

#endif