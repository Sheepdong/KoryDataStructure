#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS_
#define MAX_NAME 10
#define MAX_VERTICES 20
#define FALSE 0
#define TRUE 1
#define BAR "-"


typedef struct Node {
	int vertex;
	char name[MAX_NAME];
	struct Node* link;
} Node;
Node* adjlist[MAX_VERTICES];

typedef struct check {
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
	node1->vertex = v;
	node1->link = adjlist[u];
	adjlist[u] = node1;
	node2->vertex = u;
	node2->link = adjlist[v];
	adjlist[v] = node2;
}

void print_adjlist(int n) {
	for (int i = 0; i < n; i++) {
		Node* cur = adjlist[i];
		printf("정점 %d의 인접리스트", i);
		while (cur != NULL) {
			printf("->%s", cur->vertex);
			cur = cur->link;
		}
		printf("\n");
	}
}

void dfs(int v) {
	Node* w;
	Node* cur;
	visited[v] = TRUE;
	printf("%5d", v);
	for (w = adjlist[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}

void matching() {

}


int main() {
	int num = 0;
	char name[MAX_NAME];
	char token[2 * MAX_NAME + 1];
	char string[MAX_NAME] = "";
	char string_[MAX_NAME] = "";
	check temp;

	for (int i = 0; i < MAX_VERTICES; i++) {
		adjlist[i] = (Node*)malloc(sizeof(Node));
		adjlist[i]->link = NULL;
	}
	printf("도시 간 경로 평가 서비스에 오신 것을 환영합니다.\n");
	printf("도시 수를 입력해 주세요.\n");
	scanf("%d", &num);
	printf("도시 이름을 입력해 주세요\n");
	for (int i = 0; i < num; i++) {
		scanf("%s", name);
		strcpy(adjlist[i]->name, name);
		strcpy(visited_[i].name, name);
		visited[i] = FALSE;
	}
	printf("도시 간 도로 구축 상황을 입력하세요.\n");
	while (1) {
		scanf("%s", token);
		if (token[0] == '.' && token[1] == '\0') {
			break;
		}
		char* ptr;
		ptr = strtok(token, BAR);
		strcpy(string, ptr);
		ptr = strtok(NULL, BAR);
		strcpy(string_, ptr);
		ptr = strtok(NULL, BAR);
		if (Token(string) == -1 || Token(string_) == -1) {
			printf("도시 이름이 잘못 입력되었습니다.\n");
			continue;
		}
		making_edge(string, string_);
	}
	print_adjlist(num);
	return 0;
}