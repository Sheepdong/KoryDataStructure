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
	int u = Token(s); int v = Token(t); /*index�� �����ϴ� �� ���ϹǷ� token�Լ��� �̿��� index�� �ٲ��ش�.*/
	Node* node1 = (Node*)malloc(sizeof(Node));
	Node* node2 = (Node*)malloc(sizeof(Node));
	node1->vertex = v;
	node1->link = g[u];
	g[u] = node1;
	node2->vertex = u;
	node2->link = g[v];
	g[v] = node2;/*���Ḯ��Ʈ ����*/
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
	if (n == num) { /*dfs�� ������ ������ visited[i]�� �ִ� 1�� ������ �þ�Ƿ� �̸� �̿��� ���Ἲ�� Ȯ���Ѵ�.*/
		printf("�������� ���� ���� ��ȹ�Դϴ�.\n");
		return 0;
	}
	return -1;
}

void matching(int num) {
	for (int i = 0; i < MAX_VERTICES; i++) { visited[i] = FALSE; } /* dfs(0)�� �����ϰ� ���� visited �迭�� 1�� �κ��� ����Ƿ� 0���� �ʱ�ȭ*/
	int k = 0;
	printf("��ü ���õ��� �������� ���մϴ�.\n");
	for (int i = 0; i < num; i++) {
		if (k == i) { /*������� �ʴ� ��쿡 ���ؼ� �ϹǷ� dfs(0)�� �����ϰ� ���� visited[i]�� 1�� �ƴ� �κ��� ������ �����Ѵ�.*/
			connected[k] = TRUE;
			printf("(");
			dfs_print(k);
			printf(")");
		}
		for (int j = 0; j < num; j++) {
			if (!visited[j]) { /*visited[i]�� 1�� �ƴ� k�� ã�� ���� �۾�*/
				k = j;
				break;
			}
		}
	}
	printf("�� �и��˴ϴ�.\n");
}

int search(Node** g, char* s, char* t) {
	int u = Token(s);
	int v = Token(t);
	Node* cur = g[u]->link; /*�����͸� �����̸� �ߺ����� �ƴ��� Ȯ��*/
	while (cur != NULL) {
		if (cur->vertex == v) return v;
		cur = cur->link;
	}
	return -1;
}

void recommending(int num) {
	int l = 0; int r = 0; /*�ʱ�ȭ*/
	printf("������ ���θ� ��õ�մϴ�.\n");
	for (int i = 0; i < num; i++) {
		l = 0; r = -1; /*������ �� ��µ��� �ʰ� �ϱ� ����*/
		if (connected[i] == TRUE) {
			l = i; /*dfs�� ������ �� connected[k]�� TRUE���� �־����Ƿ� k������ ������Ѿ���*/
			for (int j = i + 1; j < num; j++) {
				if (connected[j] == TRUE) {
					r = j;
					break;
				}
			}
			if (l >= 0 && r >= 0) /*index�� �����Ƿ� check�� ����ü���� �̸��� ã�Ƽ� ������ش�*/
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
		printf("���� �� ��� �� ���񽺿� ���� ���� ȯ���մϴ�.\n");
		printf("���� ���� �Է��� �ּ���.\n");
		scanf("%d", &num);
		if (num == 0) {
			printf("���񽺸� �����մϴ�.\n");
			break;
		}
		printf("���� �̸��� �Է��� �ּ���\n");
		for (int i = 0; i < num; i++) {
			scanf("%s", name);
			strcpy(adjlist[i]->name, name);
			strcpy(visited_[i].name, name);
			adjlist[i]->vertex = Token(name);
			visited[i] = FALSE;
			connected[i] = FALSE; 
		}
		printf("���� �� ���� ���� ��Ȳ�� �Է��ϼ���.\n");
		while (1) {
			scanf("%s", token); /*string-string_ ���·� �Է� �����Ƿ� �̸� ��ū���� �ɰ��ش�*/
			if (token[0] == '.' && token[1] == '\0') break;
			char* ptr = strtok(token, BAR);
			strcpy(string, ptr);
			ptr = strtok(NULL, BAR);
			strcpy(string_, ptr);
			ptr = strtok(NULL, BAR);
			if (Token(string) == -1 || Token(string_) == -1) { /*�߸� �Է� ���� �� ���� ó��*/
				printf("���� �̸��� �߸� �ԷµǾ����ϴ�.\n");
				continue;
			}
			making_edge(adjlist, string, string_);
			if (search(adjlist, string, string_) != -1) { /* �Ȱ��� ������ �Է����� �� ���� ó��*/
				printf("�ߺ��� �����Դϴ�.\n");
				continue;
			}
		}
		if (dfs(0, num) == -1) { /* dfs(0)�� �����Ͽ� ���Ἲ Ȯ��*/
			matching(num);
			recommending(num);
		}
		printf("-------------------\n");
		init(); /*�ʱ�ȭ �۾�*/
	}
	return 0;
}