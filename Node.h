#ifndef _NODE_
#define _NODE_

#include <string>
#include <math.h>

using namespace std;

const unsigned PUZZLE_WIDTH = 3;
int algorithm;
int GOAL_STATE[PUZZLE_WIDTH][PUZZLE_WIDTH] =
{
	{ 1, 2, 3 },
	{ 4, 5, 6 },
	{ 7, 8, 0 }
};

// Included public functions
void stringToMatrix(string nums, int matrix[PUZZLE_WIDTH][PUZZLE_WIDTH], string &stringNums, int &spaceRow, int &spaceColumn);
void printMatrix(int matrix[PUZZLE_WIDTH][PUZZLE_WIDTH]);

class Node {
public:
	int g = 0;
	int h = 0;
	int f;
	int spaceRow;
	int spaceColumn;
	int STATE[PUZZLE_WIDTH][PUZZLE_WIDTH];
	string stringNums;

	// Constructors
	Node(string inputNums, int depth) {
		stringToMatrix(inputNums, STATE, stringNums, spaceRow, spaceColumn);
		g = depth;
		calculateHeuristics();
	}

	Node(int copyState[PUZZLE_WIDTH][PUZZLE_WIDTH], int depth) {
		stringNums = "";
		for (int i = 0; i < PUZZLE_WIDTH; ++i) {
			for (int j = 0; j < PUZZLE_WIDTH; ++j) {
				STATE[i][j] = copyState[i][j];
				stringNums += STATE[i][j] + '0';
				if (STATE[i][j] == 0) {
					spaceRow = i;
					spaceColumn = j;
				}
			}
		}
		// Set g(n) value based on depth in the search tree
		g = depth;
		calculateHeuristics();
	}

	// Set heuristic values based on algorithm chosen
	void calculateHeuristics() {
		if (algorithm == 1) { // Uniform Cost Search1
			h = 0;
		}
		else if (algorithm == 2) { // A* with the Misplaced Tile heuristic
			h = 0;
			for (int i = 0; i < PUZZLE_WIDTH; ++i) {
				for (int j = 0; j < PUZZLE_WIDTH; ++j) {
					if (STATE[i][j] != GOAL_STATE[i][j]) {
						h++;
					}
				}
			}
		}
		else if (algorithm == 3) { // A* with the Manhattan Distance heuristic
			h = 0;
			for (int i = 0; i < PUZZLE_WIDTH; ++i) {
				for (int j = 0; j < PUZZLE_WIDTH; ++j) {
					if (STATE[i][j] != GOAL_STATE[i][j]) {
						bool found = false;
						int a = 0;
						while (!found && a < PUZZLE_WIDTH) {
							int b = 0;
							while (!found && b < PUZZLE_WIDTH) {
								if (STATE[i][j] == GOAL_STATE[a][b]) {
									found = true;
									h += abs(a - i) + abs(b - j);
								}
								b++;
							}
							a++;
						}
					}
				}
			}
		}

		f = g + h;
	}

	const int depth() {
		return g;
	}

}; // End class Node

void stringToMatrix(string nums, int matrix[PUZZLE_WIDTH][PUZZLE_WIDTH], string &stringNums, int &spaceRow, int &spaceColumn) {
	unsigned start = 0;
	unsigned end = 0;
	string outNums = "";
	while (end <= nums.length() && nums[end] != ' ') {
		end++;
	}
	for (int i = 0; i < PUZZLE_WIDTH; ++i) {
		for (int j = 0; j < PUZZLE_WIDTH; ++j) {
			if (start > nums.length())
				return;
			matrix[i][j] = stoi(nums.substr(start, end - start));
			// Save the space position in the node
			if (matrix[i][j] == 0) {
				spaceRow = i;
				spaceColumn = j;
			}
			if (matrix[i][j] < 0) {
				spaceRow = i;
				spaceColumn = j;
			}
			outNums += nums.substr(start, end - start);
			while (end <= nums.length() && nums[end] == ' ') {
				end++;
			}
			start = end;
			while (end <= nums.length() && nums[end] != ' ') {
				end++;
			}
		}
	}
	stringNums = outNums;
}

void printMatrix(int matrix[PUZZLE_WIDTH][PUZZLE_WIDTH]) {
	for (int i = 0; i < PUZZLE_WIDTH; ++i) {
		for (int j = 0; j < PUZZLE_WIDTH; ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

#endif // !_NODE_
