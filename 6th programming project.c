#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 20
#define MAX_NAME 10
short int visited[MAX_VERTICES];
nodePointer graph[MAX_VERTICES];

typedef struct node* nodepointer;
typedef struct node {
	int vertex;
	nodepointer link;
};
nodepointer adjlists[MAX_VERTICES];

typedef struct treeNode* treepointer;
typedef struct treeNode {
	int key;
	treepointer leftchild;
	treepointer rightchild;
};

treepointer insert(treepointer node, int k) {
	if (node == NULL) return newNode(k);
	if (k < node->key)
		node->leftchild = insert(node->leftchild, k);
	else
		node->rightchild = insert(node->rightchild, k);
	return node;
}

void dfs(int v) {
	nodepointer w;
	visited[v] = TRUE;
	printf("%5d", v);
	for (w = graph[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}

void connected(void) {
	int i = 0;
	for (i = 0; i < n; i++) {
		if (!visited[i])
			dfs(i);
		printf("\n");
	}
}

