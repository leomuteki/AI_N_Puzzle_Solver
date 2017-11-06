#ifndef _PROBLEM_
#define _PROBLEM_

#include "Node.h"

using namespace std;

class Node;

void recalculateString(Node *node);

class Problem {
public:
	int INITIAL_STATE[PUZZLE_WIDTH][PUZZLE_WIDTH];
	bool GOAL_TEST(int testState[PUZZLE_WIDTH][PUZZLE_WIDTH]) {
		for (int i = 0; i < PUZZLE_WIDTH; ++i) {
			for (int j = 0; j < PUZZLE_WIDTH; ++j) {
				if (testState[i][j] != GOAL_STATE[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	Problem(string inputNums) {
		string dummy0 = "";
		int dummy1 = 0, dummy2 = 0;
		stringToMatrix(inputNums, INITIAL_STATE, dummy0, dummy1, dummy2);
	}

	vector<Node*> operators(Node *node, Problem *prob) {
		vector<Node*> expandedNodes;
		// Try moving blank space left
		if (node->spaceColumn != 0) {
			Node *curNode = new Node(node->STATE, node->depth() + 1);
			// Swap space location with the tile on the left
			int temp = curNode->STATE[curNode->spaceRow][curNode->spaceColumn - 1];
			curNode->STATE[curNode->spaceRow][curNode->spaceColumn - 1] = 0;
			curNode->STATE[curNode->spaceRow][curNode->spaceColumn] = temp;
			curNode->spaceColumn--;
			recalculateString(curNode);
			curNode->calculateHeuristics();
			expandedNodes.push_back(curNode);
			curNode = 0;
		}
		// Try moving blank space right
		if (node->spaceColumn != (PUZZLE_WIDTH - 1)) {
			Node *curNode = new Node(node->STATE, node->depth() + 1);
			// Swap space location with the tile on the right
			int temp = curNode->STATE[curNode->spaceRow][curNode->spaceColumn + 1];
			curNode->STATE[curNode->spaceRow][curNode->spaceColumn + 1] = 0;
			curNode->STATE[curNode->spaceRow][curNode->spaceColumn] = temp;
			curNode->spaceColumn++;
			recalculateString(curNode);
			curNode->calculateHeuristics();
			expandedNodes.push_back(curNode);
			curNode = 0;
		}
		// Try moving blank space up
		if (node->spaceRow != 0) {
			Node *curNode = new Node(node->STATE, node->depth() + 1);
			// Swap space location with the tile above
			int temp = curNode->STATE[curNode->spaceRow - 1][curNode->spaceColumn];
			curNode->STATE[curNode->spaceRow - 1][curNode->spaceColumn] = 0;
			curNode->STATE[curNode->spaceRow][curNode->spaceColumn] = temp;
			curNode->spaceRow--;
			recalculateString(curNode);
			curNode->calculateHeuristics();
			expandedNodes.push_back(curNode);
			curNode = 0;
		}
		// Try moving blank space down
		if (node->spaceRow != (PUZZLE_WIDTH - 1)) {
			Node *curNode = new Node(node->STATE, node->depth() + 1);
			// Swap space location with the tile below
			int temp = curNode->STATE[curNode->spaceRow + 1][curNode->spaceColumn];
			curNode->STATE[curNode->spaceRow + 1][curNode->spaceColumn] = 0;
			curNode->STATE[curNode->spaceRow][curNode->spaceColumn] = temp;
			curNode->spaceRow++;
			recalculateString(curNode);
			curNode->calculateHeuristics();
			expandedNodes.push_back(curNode);
			curNode = 0;
		}
		return expandedNodes;
	}

}; // End class Problem

void recalculateString(Node *node) {
	string outNums = "";
	for (int i = 0; i < PUZZLE_WIDTH; ++i) {
		for (int j = 0; j < PUZZLE_WIDTH; ++j) {
			outNums += node->STATE[i][j] + '0';
		}
	}
	node->stringNums = outNums;
}

#endif // !_PROBLEM_
