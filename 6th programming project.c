#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS_
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 20
#define MAX_NAME 10

typedef struct check {
	int num;
	char name[MAX_NAME];
}check;
check visited_[MAX_VERTICES];
short int visited[MAX_VERTICES];

typedef struct Node {
	int vertex;
	char name[MAX_NAME];
	struct Node* link;
} Node;

typedef struct Graph {
	int n;
	struct Node* adj_list[MAX_VERTICES];
} Graph;

typedef struct treenode {
	int key;
	struct treenode* leftchild;
	struct treenode* rightchild;
} treenode;

int Token(Graph* g, char* s) {
	for (int i = 0; i < g->n; i++) {
		if (visited_[i].name == s)
			return i;
	}
	return 0;
}

void init(Graph* g) {
	int v = 0;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

void making_vertex(Graph* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		printf("overflow\n");
		return;
	}
	g->n++;
}

void making_edge(Graph* g, char* s, char* t) {
	Node* node;
	node = (Node*)malloc(sizeof(Node));
	int u = Token(g, s);
	int v = Token(g, t);
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void dfs(Graph* g, int v) {
	Node* w;
	visited[v] = TRUE;
	printf("%5d", v);
	for (w = g->adj_list[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(g, w->vertex);
	}
}

char string_[MAX_NAME];

int main() {
	Graph* graph;
	graph = (Graph*)malloc(sizeof(Graph));
	init(graph);
	int num = 0;
	char name[MAX_NAME];
	char string[MAX_NAME];
	char string_[MAX_NAME];
	printf("���� �� ��� �� ���񽺿� ���� ���� ȯ���մϴ�.\n");
	printf("���� ���� �Է��� �ּ���.\n");
	scanf("%d", &num);
	printf("���� �̸��� �Է��� �ּ���\n");
	for (int i = 0; i < num; i++) {
		scanf("%s ", name);
		strcpy(visited_[i].name, name);
	}
	printf("���� �� ���� ���� ��Ȳ�� �Է��ϼ���.\n");
	while (1) {
		scanf("%s-%s\n", string, string_);
		if (string[0] == '.' && string[1] == '\0') {
			break;
		}
		if (Token(graph, string) || Token(graph, string_)) {
			printf("���� �̸��� �߸� �ԷµǾ����ϴ�.");
			continue;
		}
		making_edge(graph, string, string_);
	}
}
