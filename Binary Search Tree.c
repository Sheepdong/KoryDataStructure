#include <stdio.h>

typedef struct Node* treepointer;

typedef struct element {
	int key;
};

typedef struct Node {
	element key;
	treepointer leftchild;
	treepointer rightchild;
}Node;

element* search(treepointer root, int k) {
	if (!root) return NULL;
	if (k == root->data.key) return &(root->data);
	if (k < root->data.key)
		return search(root->leftchild, k);
	return search(root->rightchild, k);
}

element* iterSearch(treepointer tree, int k) {
	while (tree) {
		if (k == tree->data.key) return &(tree->data);
		if (k < tree->data.key)
			tree = tree->leftchild;
		else
			tree = tree->rightchild;
	}
	return NULL;
}

void insert(treepointer* node, int k) {
	treepointer ptr, temp = modifiedSearch(*node, k); /* 없다면 없다고 결정지은 마지막 parent node의 주소값을 가져옴*/
	if (temp || !(*node)) /* 이 리스트가 empty일때*/ {
		MALLOC(ptr, sizeof(*ptr));
		ptr->data.key = k;
		ptr->leftchild = ptr->rightchild = NULL;
		if (*node) {
			if (k < temp->data.key) {
				temp->leftchild = ptr;
			}
			else {
				temp->rightchild = ptr;
			}
		}
		else {
			*node = ptr;
		}
	}
}

