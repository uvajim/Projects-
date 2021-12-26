#include "node.h"

using namespace std;

	Node::Node (){
		board = "";
		previous =  NULL;
		move = 0;
	}

	Node::Node(string state, Node* prev, int n){
		board = state;
		previous = prev;
		move = n;
	}
	
	Node* Node::getPrev(){
		return previous;
	}

	string Node::getState(){
		return board;
	}

	int Node::getMove(){
		return move; 
	}