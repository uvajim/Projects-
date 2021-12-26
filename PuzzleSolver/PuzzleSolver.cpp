#include <string>
#include <iostream>
#include <queue>
#include <unordered_map>
#include "node.h"
using namespace std; 

unordered_map<string, bool> visited; 
int zeroPos; 
queue<vector<Node*> > q1;
string match = "123456780";
vector<Node*> v;

void printPath(Node *n);


/**
 * @author Jim Liang 
 * 
 * @date Dec 1, 2021
 * 
 * @brief this function when called will permutate all possible combinations of the given board. N
 * 		  no paramters are taken. 
 * 
 * @return will return true if the goal state is not found or if more possible permuations are found.
 * 
 * 
 * 
 * @todo -make function work with a vector (done)
 * 		 -check if the string has already been visited (done)
 *       -replace queue functions with vector functions (done)
 */
bool getNeighbors(){
	vector<Node*> vec = q1.front();
	q1.pop();
	v.clear();
	for (Node *node: vec){
		if (node->getState() == match) return false;
		string s = node->getState();
		string tempString = s;
		int zeroPos = s.find("0");
		string temp = "";
	if (visited[s] == 0){
		//move up
		if (zeroPos - 3 > -1){
			temp = s.at(zeroPos - 3);
			tempString.replace(zeroPos, 1, temp);
			tempString.replace(zeroPos -3, 1,"0");
			if (tempString == match) {
				Node *n = new Node(tempString, node, 1);
				printPath(n);
				return false;
			}
			if (visited[tempString] == false) {
				Node *n = new Node(tempString, node, 1);
				v.push_back(n);
			}
		}
		//reset the board
		tempString = s;
		//move down
		if(zeroPos + 3 < 9){
			temp = s.at(zeroPos + 3);
			tempString.replace(zeroPos, 1, temp);
			tempString.replace(zeroPos + 3, 1, "0");
			if (tempString == match) {
				Node *n = new Node(tempString, node, 2);
				printPath(n);
				return false;
			}
			if (visited[tempString] == false) {
				Node *n = new Node(tempString, node,2);
				v.push_back(n); 
			}
		}

		//reset the board
		tempString = s;
		if(zeroPos%3 != 0){
			//move left
			temp = s.at(zeroPos -1);
			tempString.replace(zeroPos, 1, temp);
			tempString.replace(zeroPos - 1 , 1, "0");
			if (tempString == match) {
				Node *n = new Node(tempString, node,3);
				printPath(n);
				return false;
			}
			if (visited[tempString] == false) {
				Node *n = new Node(tempString, node, 3);
				v.push_back(n);
			}
		}

		//reset the board
		tempString = s;
		if( (zeroPos+1) % 3 != 0){
			//move right
			temp = s.at(zeroPos + 1);
			tempString.replace(zeroPos, 1, temp);
			tempString.replace(zeroPos  + 1 , 1, "0");
			if (tempString == match) {
				Node *n = new Node(tempString, node, 4);
				printPath(n);
				return false;
			}
			if (visited[tempString] == false) {
				Node *n = new Node(tempString, node, 4);
				v.push_back(n);
			}

			}
		visited[s] = true;
		}
	}
	q1.push(v);
	return true;
}


/**
 * @brief checks if the given board is solvable or not. (if it has an even amount of inversions)
 * 
 * @param s the string that represents the board to be checked; a string
 * 
 * @return a false if it is solvable, true if it is not
 *
 * @note used the explanation from https://math.stackexchange.com/questions/293527/how-to-check-if-a-8-puzzle-is-solvable
 *       not the YouTube video provided, sorry!
 */
bool notSolvable(string s){
	int inversions = 0;
	for(int i = 0; i < 9; i++){
		for(int j = i+ 1; j < 9; j++){
			if ((s.at(i) > s.at(j)) && s.at(i) != 48 && s.at(j) != 48) inversions++;
		}
	}
	return inversions % 2;
}

void printPath(Node *n){
	if (n->getPrev() ==  NULL) return;

	printPath(n->getPrev());
	cout<<endl;

	int step = n->getMove();

	if (step == 1){
		cout<< "Move down"<<"\n";
	}
	if (step == 2){
		cout<< "Move up" << "\n";
	}

	if (step == 3){
		cout<<"Move right" <<"\n";
	}

	if (step == 4){
		cout<<"Move left" <<"\n";
	}

	string s = n->getState();
	int counter = 0;

	for(char c: s){
		cout<< c<< " ";

		counter++;

		if(counter == 3 || counter == 6 || counter == 9){
			cout<<endl;
		}


	}

	cout<<endl;
}

/**
 * @brief the main method, does not take in any command line parameters
 * 		  takes in each row of the board line by line. Uses a zero to represent a hole
 * 
 * @return a 0 for no error, a nonnegative integer elsewise
 * 
 */
int main(){

  	
  string a;
  string b;
  string c;
  string start = "";
  int moves = 0;

  cout << "Enter puzzle: \n";
  cout<<"3 Numbers per row! \n";
  getline(cin, a);
  getline(cin, b);
  getline(cin, c);

  for (char c: a){
  	if(!isspace(c)) start += c;
  }
  for (char c: b){
  	if(!isspace(c)) start += c;
  }
  for (char e: c){
  	if(!isspace(e)) start += e;
  }


	
	vector<Node*> starting;
	Node *starter = new Node(start, NULL, 0);
	starting.push_back(starter);

	q1.push(starting);

	//make a queue of vectors

if(!notSolvable(start)){
	while(getNeighbors() == true){
		//getNeighbors();
		moves++;
	}
	moves++;
	cout<<moves<<endl;
}
else{
	cout<<"IMPOSSIBLE"<<endl;
	
}
return 0;


}