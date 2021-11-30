#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS_
#define MAX_NAME 10
#define MAX_VERTICES 20
#define FALSE 0
#define TRUE 1
#define BAR "-"
static int n = 0;

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
short int connected[MAX_VERTICES];

void init() {
	for (int i = 0; i < MAX_VERTICES; i++) {
		visited[i] = FALSE;
		connected[i] = FALSE;
		strcpy(visited_[i].name, " ");
	}
}

int Token(char* s) {
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (!strcmp(visited_[i].name, s))
			return i;
		else continue;
	}
	return -1;
}

void making_edge(Node** g, char* s, char* t) {
	int u = Token(s); int v = Token(t); /*index로 접근하는 게 편하므로 token함수를 이용해 index로 바꿔준다.*/
	Node* node1 = (Node*)malloc(sizeof(Node));
	Node* node2 = (Node*)malloc(sizeof(Node));
	node1->vertex = v;
	node1->link = g[u];
	g[u] = node1;
	node2->vertex = u;
	node2->link = g[v];
	g[v] = node2;/*연결리스트 연결*/
}

void dfs_print(int v) {
	Node* w;
	visited[v] = TRUE;
	printf("%s ", visited_[v].name);
	for (w = adjlist[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs_print(w->vertex);
	}
}


int dfs(int v, int num) {
	Node* w;
	visited[v] = TRUE;
	n++;
	for (w = adjlist[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(w->vertex, num);
	}
	if (n == num) { /*dfs를 수행할 때마다 visited[i]에 있는 1의 개수가 늘어나므로 이를 이용해 연결성을 확인한다.*/
		printf("성공적인 도로 구축 계획입니다.\n");
		return 0;
	}
	return -1;
}

void matching(int num) {
	for (int i = 0; i < MAX_VERTICES; i++) { visited[i] = FALSE; } /* dfs(0)을 수행하고 나면 visited 배열에 1인 부분이 생기므로 0으로 초기화*/
	int k = 0;
	printf("전체 도시들을 연결하지 못합니다.\n");
	for (int i = 0; i < num; i++) {
		if (k == i) { /*연결되지 않는 경우에 대해서 하므로 dfs(0)을 수행하고 나면 visited[i]가 1이 아닌 부분이 무조건 존재한다.*/
			connected[k] = TRUE;
			printf("(");
			dfs_print(k);
			printf(")");
		}
		for (int j = 0; j < num; j++) {
			if (!visited[j]) { /*visited[i]가 1이 아닌 k를 찾기 위한 작업*/
				k = j;
				break;
			}
		}
	}
	printf("로 분리됩니다.\n");
}

int search(Node** g, char* s, char* t) {
	int u = Token(s);
	int v = Token(t);
	Node* cur = g[u]->link; /*포인터를 움직이며 중복인지 아닌지 확인*/
	while (cur != NULL) {
		if (cur->vertex == v) return v;
		cur = cur->link;
	}
	return -1;
}

void recommending(int num) {
	int l = 0; int r = 0; /*초기화*/
	printf("다음의 도로를 추천합니다.\n");
	for (int i = 0; i < num; i++) {
		l = 0; r = -1; /*음수일 때 출력되지 않게 하기 위함*/
		if (connected[i] == TRUE) {
			l = i; /*dfs를 수행할 때 connected[k]에 TRUE값을 주었으므로 k값들을 연결시켜야함*/
			for (int j = i + 1; j < num; j++) {
				if (connected[j] == TRUE) {
					r = j;
					break;
				}
			}
			if (l >= 0 && r >= 0) /*index로 줬으므로 check형 구조체에서 이름을 찾아서 출력해준다*/
				printf("%s-%s\n", visited_[l].name, visited_[r].name);
		}
	}
}

int main() {
	int num = 0;
	char name[MAX_NAME];
	char token[2 * MAX_NAME + 1];
	char string[MAX_NAME] = "";
	char string_[MAX_NAME] = "";
	while (1) {
		for (int i = 0; i < MAX_VERTICES; i++) {
			adjlist[i] = (Node*)malloc(sizeof(Node));
			adjlist[i]->link = NULL;
		}
		printf("도시 간 경로 평가 서비스에 오신 것을 환영합니다.\n");
		printf("도시 수를 입력해 주세요.\n");
		scanf("%d", &num);
		if (num == 0) {
			printf("서비스를 종료합니다.\n");
			break;
		}
		printf("도시 이름을 입력해 주세요\n");
		for (int i = 0; i < num; i++) {
			scanf("%s", name);
			strcpy(adjlist[i]->name, name);
			strcpy(visited_[i].name, name);
			adjlist[i]->vertex = Token(name);
			visited[i] = FALSE;
			connected[i] = FALSE; 
		}
		printf("도시 간 도로 구축 상황을 입력하세요.\n");
		while (1) {
			scanf("%s", token); /*string-string_ 형태로 입력 받으므로 이를 토큰으로 쪼개준다*/
			if (token[0] == '.' && token[1] == '\0') break;
			char* ptr = strtok(token, BAR);
			strcpy(string, ptr);
			ptr = strtok(NULL, BAR);
			strcpy(string_, ptr);
			ptr = strtok(NULL, BAR);
			if (Token(string) == -1 || Token(string_) == -1) { /*잘못 입력 했을 때 오류 처리*/
				printf("도시 이름이 잘못 입력되었습니다.\n");
				continue;
			}
			making_edge(adjlist, string, string_);
			if (search(adjlist, string, string_) != -1) { /* 똑같은 정보를 입력했을 때 오류 처리*/
				printf("중복된 정보입니다.\n");
				continue;
			}
		}
		if (dfs(0, num) == -1) { /* dfs(0)을 수행하여 연결성 확인*/
			matching(num);
			recommending(num);
		}
		printf("-------------------\n");
		init(); /*초기화 작업*/
	}
	return 0;
}