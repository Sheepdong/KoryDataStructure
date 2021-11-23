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

#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 20
#define MAX_NAME 10

typedef struct Node {
	char* vertex;
	Node* link;
} Node;

typedef struct Graphtype {
	char s;
	Node* adj_list[MAX_VERTICES];
} Graphtype;

short int visited[MAX_VERTICES];
Node* graph[MAX_VERTICES];

typedef struct treenode {
	int key;
	treenode* leftchild;
	treenode* rightchild;
} treenode;

void init(Graphtype* g) {
	int v = 0;
	g->n = "";
	for (v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

void making_vertex(Graphtype* g, char* s) {

}
void dfs(int v) {
	Node* w;
	visited[v] = TRUE;
	printf("%5d", v);
	for (w = graph[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}

char string_[MAX_NAME];

int main() {
	int num = 0;
	char string[MAX_NAME];
	printf("도시 간 경로 평가 서비스에 오신 것을 환영합니다.\n");
	printf("도시 수를 입력해 주세요.\n");
	scanf("%d", num);
	printf("도시 이름을 입력해 주세요\n");
	for (int i = 0; i < num; i++) {
		scanf("%s", string);


	}

}
