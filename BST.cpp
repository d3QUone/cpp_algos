#include <iostream>

/// simple trees ///

struct CNode {
	int key;
	CNode* Left;
	CNode* Right;
};


void visit(CNode* n) {
	std::cout << n -> key;
}


void TReverse(CNode* n) {
	if (n == 0) {
		return;
	}

}


int Height(CNode* n) {
	if (n == 0) {
		return 0;
	} else {
		return std::max(Height(n -> Left), Height(n -> Right)) + 1;
	}
} 

/// balanced trees ///

struct CTreapNone {
	int Priority;
	int Key;
	CTreapNone* Left;
	CTreapNone* Right;

	CTreapNone(int key, int priority): Key(key), Priority(priority) {};
};


void Split(CTreapNone* node, int k, CTreapNone*& left, CTreapNone*& right) {
	if (node == 0) {
		left = 0;
		right = 0;
		return;
	}

	if (node -> Key < key) {
		CTreapNone* tempLeft = 0;
		CTreapNone* tempRight = 0;
		Split(node -> Right, key, tempLeft, tempRight);
		right = tempRight;
		left = node;
		left -> Right = tempLeft;
	} else {
		Split(node -> Left, key, left, node->Left);
		right = node -> Right;
	}
}


CTreapNone* Merge(CTreapNone* left, CTreapNone* right) {
	if (left == 0 || right == 0) {
		return left == 0 ? right : left;
	}

	if (left -> Priority > right -> Priority) {
		// root = left
	} else {
		// root = right
	}
}


int main() {
	std::cout << "check\n";
	return 0;
}
