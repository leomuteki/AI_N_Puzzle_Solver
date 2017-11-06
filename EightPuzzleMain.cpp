/*	Project:	CS 170 Project 1
*	Date:		11/05/17
*	Author:		Emmilio Segovia
*	References:
*				https://stackoverflow.com/questions/1541560/stl-priority-queue-on-custom-class
*				www.cplusplus.com/reference/unordered_set/unordered_set/find/
*/

#include <iostream>
#include <string>
#include <functional>
#include <queue>
#include <vector>
#include <unordered_set>
#include <exception>
#include <math.h>
#include "Problem.h"

using namespace std;

// Forward Declarationsstring &stringNums
class Problem;
class Node;
struct nodeCompare;

// Globals
typedef priority_queue<Node*, vector<Node*>, nodeCompare> PriorityQueue;
//const unsigned PUZZLE_WIDTH = 3;
unordered_set<string> alreadyVisited;

// Function Headers
Node* generalSearch(Problem *prob);
void stringToMatrix(string nums, int matrix[PUZZLE_WIDTH][PUZZLE_WIDTH], string &stringNums, int &spaceRow, int &spaceColumn);
void queueingFunction(PriorityQueue &nodes, Node *node, Problem *prob, int &expandedCount, int &queueSize, int &totalNodesExpanded);

// Structures and Classes
struct nodeCompare : public binary_function<Node*, Node*, bool>
{
	bool operator()(Node *lhs, Node *rhs) const
	{
		return (lhs->f > rhs->f);
	}
};

int main() {
	// Variables
	string input, inputNums = "";
	bool error = false;
	int customChoice;
	// Get input from user
	do {
		error = false;
		cout << "Welcome to Bertie Woosters 8-puzzle solver." << endl;
		cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
		cin >> input;
		try {
			stoi(input);
		}
		catch (exception& e) {
			error = true;
			cout << "Error: please enter 1 or 2" << endl;
		}
	} while (error || stoi(input) < 1 || stoi(input) > 2);
	customChoice = stoi(input);

	// Get starting state
	if (customChoice == 1) {
		//inputNums = "1 2 3 4 5 6 7 8 0";
		inputNums = "8 7 1 6 0 2 5 4 3";
		//inputNums = "1 2 3 4 5 0 7 8 6";
	}
	else {
		cin.ignore();
		cout << "Enter your puzzle, use a zero to represent the blank" << endl;
		cout << "Enter the first row, use space or tabs between numbers     ";
		getline(cin, input);
		inputNums += input + " ";
		cout << "Enter the second row, use space or tabs between numbers    ";
		getline(cin, input);
		inputNums += input + " ";
		cout << "Enter the third row, use space or tabs between numbers     ";;
		getline(cin, input);
		inputNums += input;
		cout << endl;
	}

	// Get input for algorithm choice
	do {
		error = false;
		cout << "Enter your choice for algorithm" << endl;
		cout << "1. Uniform Cost Search" << endl;
		cout << "2. A* with the Misplaced Tile heuristic." << endl;
		cout << "3. A* with the Manhattan distance heuristic." << endl;
		cin >> input;
		try {
			stoi(input);
		}
		catch (exception& e) {
			error = true;
			cout << "Error: please enter 1 through 3" << endl;
		}
	} while (error || stoi(input) < 1 || stoi(input) > 3);
	algorithm = stoi(input);

	Problem *eightPuzzle = new Problem(inputNums);

	generalSearch(eightPuzzle);

	return 0;
}

Node* generalSearch(Problem *prob) {
	// Statistics counters
	int expandedCount = 0;
	int queueSize = 0;
	int maxQueueSize = 0;
	int totalNodesExpanded = 0;

	// Make queue and initialize with initial state
	PriorityQueue nodes;
	Node *temp = new Node(prob->INITIAL_STATE, 0);
	nodes.push(temp);
	queueSize++;
	alreadyVisited.insert(temp->stringNums);
	temp = 0;

	while (1) {
		if (nodes.size() == 0) {
			cout << "Failure" << endl;
			return 0;
		}
		Node *node = nodes.top();
		nodes.pop();
		queueSize--;
		cout << "The best state to expand with a g(n) = " << node->depth();
		cout << " and h(n) = " << node->h << " is..." << endl;
		printMatrix(node->STATE);
		if (prob->GOAL_TEST(node->STATE)) {
			cout << "Goal!" << endl << endl;
			cout << "To solve this problem the search algorithm expanded a total of " << expandedCount << " nodes." << endl;
			cout << "The maximum number of nodes in the queue at any one time was " << totalNodesExpanded << endl;
			cout << "The depth of the goal node was " << node->depth() << endl;
			return node;
		}
		else {
			cout << "Expanding this node..." << endl;
			queueingFunction(nodes, node, prob, expandedCount, queueSize, totalNodesExpanded);
			delete node;
			node = 0;
			// Update max queue size
			if (queueSize > maxQueueSize) {
				maxQueueSize = queueSize;
			}
		}
	}
}
	
void queueingFunction(PriorityQueue &nodes, Node *node, Problem *prob, int &expandedCount, int &queueSize, int &totalNodesExpanded) {
	// Get new Nodes from operators
	vector<Node*> expandedNodes = prob->operators(node, prob);

	int size = expandedNodes.size();
	for (int i = 0; i < size; ++i) {
		unordered_set<string>::const_iterator found = alreadyVisited.find(expandedNodes.at(i)->stringNums);
		// If not already visitied, then add it to the list and queue
		if (found == alreadyVisited.end()) {
			// Not found
			alreadyVisited.insert(expandedNodes.at(i)->stringNums);
			// Insert new Nodes into the PriorityQueue
			nodes.push(expandedNodes.at(i));
			totalNodesExpanded++;
			expandedCount += expandedNodes.size();
			queueSize += expandedNodes.size();
		}
		// else Found
	}

}

/*cout << "PQ printout: " << endl;
int count = 1;
for (unordered_set<string>::const_iterator it = alreadyVisited.begin(); it != alreadyVisited.end(); ++it) {
cout << "NUMBER: " << count << endl;
string str = *it;
for (int i = 0; i < str.length(); ++i) {
cout << str.at(i) << " ";
if ((i + 1) % 3 == 0) {
cout << endl;
}
}
cout << endl;
count++;
}*/