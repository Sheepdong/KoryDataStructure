#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS_
#define MAX_NAME 10
#define MAX_VERTICES 20
#define FALSE 0
#define TRUE 1


typedef struct Node {
	int vertex;
	char name[MAX_NAME];
	struct Node* link;
} Node;
Node* adjlist[MAX_VERTICES];

typedef struct check {
	int num;
	char name[MAX_NAME];
}check;
check visited_[MAX_VERTICES];
short int visited[MAX_VERTICES];

int Token(char* s) {
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (!strcmp(visited_[i].name, s))
			return i;
		else continue;
	}
	return -1;
}

void making_edge(char* s, char* t) {
	int u = Token(s); int v = Token(t);
	Node* node1 = (Node*)malloc(sizeof(Node));
	Node* node2 = (Node*)malloc(sizeof(Node));
	if (adjlist[u]->link != NULL) {
		node1->vertex = v;
		node1->link = NULL;
		adjlist[u]->link = node1;
	}
	else {
		node1->vertex = v;
		node1->link = adjlist[u]->link;
		adjlist[u]->link = node1;
	}
	if (adjlist[v]->link != NULL) {
		node2->vertex = u;
		node2->link = NULL;
		adjlist[v]->link = node2;
	}
	else {
		node2->vertex = u;
		node2->link = adjlist[v]->link;
		adjlist[v]->link = node2;
	}
}

void print_adjlist(int n) {
	for (int i = 0; i < n; i++) {
		Node* cur = adjlist[i];
		printf("���� %d�� ��������Ʈ", i);
		while (cur != NULL) {
			printf("->%s", cur->name);
			cur = cur->link;
		}
		printf("\n");
	}
}

int main() {
	int num = 0;
	char name[MAX_NAME];
	char string[MAX_NAME];
	char string_[MAX_NAME];
	for (int i = 0; i < MAX_VERTICES; i++) {
		adjlist[i] = (Node*)malloc(sizeof(Node));
		adjlist[i]->link = NULL;
	}
	printf("���� �� ��� �� ���񽺿� ���� ���� ȯ���մϴ�.\n");
	printf("���� ���� �Է��� �ּ���.\n");
	scanf("%d", &num);
	printf("���� �̸��� �Է��� �ּ���\n");
	for (int i = 0; i < num; i++) {
		scanf("%s", name);
		strcpy(adjlist[i]->name, name);
		strcpy(visited_[i].name, name);
		visited[i] = FALSE;
	}
	printf("���� �� ���� ���� ��Ȳ�� �Է��ϼ���.\n");
	while (1) {
		scanf("%s-%s", string, string_);
		if (string[0] == '.' && string[1] == '\0') {
			break;
		}
		if (Token(string) == -1 || Token(string_) == -1) {
			printf("���� �̸��� �߸� �ԷµǾ����ϴ�.");
			continue;
		}
		making_edge(string, string_);
	}
	print_adjlist(num);
	return 0;
}
