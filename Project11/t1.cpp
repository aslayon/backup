#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <CoreWindow.h>




#define MAX_VERTICES 400
typedef struct arrver {
	int row_ver;
	int col_ver;		//���� ��ǥ�� ������ �뵵
}arrver;
typedef struct GraphType {
	int n;	// ������ ����
	arrver a[MAX_VERTICES];
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v, arrver item)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->a[g->n] = item;				///////////////////////�ش� ���������� ��ǥ�� ����
	g->n++;

}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
// ���� ��� ��� �Լ�
void print_adj_mat(GraphType* g)
{
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}




int maze[20][20];
int visual[20][20];
int row = 20;
int col = 20;
//random �Լ�
void random() {
	int a = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			maze[i][j] = rand() % 2;
		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}
//���Ͽ��� �о����
void filein() {
	FILE* fp = fopen("maze3.txt", "r");
	if (fp == NULL) {
		printf("maze read error");
		return;
	}
	int tmp = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(fp, "%d", &tmp);
			maze[i][j] = tmp;
			visual[i][j] = tmp;
		}
	}
	fclose(fp);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}

void maze_ver(GraphType* p) {//������ ��� -> ���� �����
	arrver a;
	int cnt = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (maze[i][j] == 1) {
				a.row_ver = i;
				a.col_ver = j;
				insert_vertex(p, cnt, a);
				cnt++;
			}
		}
	}
}

void maze_ed(GraphType* p) {    //���� �������� �̾��ִ� �Լ� //
	if (p->a[0].col_ver != 0 || p->a[0].row_ver != 0) {
		printf("\n");
		printf("(0,0)�� ������ ������\n ERROR\n");
		printf("���� (%d, %d) ���� ����\n", p->a[0].col_ver, p->a[0].row_ver);
	}
	for (int i = 0; i < p->n; i++) {
		int col_tmp = p->a[i].col_ver;
		int row_tmp = p->a[i].row_ver;
		for (int j = i + 1; j < p->n; j++) {
			if (p->a[j].col_ver == col_tmp + 1 && p->a[j].row_ver == row_tmp) {
				insert_edge(p, i, j);
			}
			if (p->a[j].col_ver == col_tmp && p->a[j].row_ver == row_tmp + 1) {   //��ȯ�ϸ鼭 ���� ��ġ���� ��ĭ ������, ��ĭ �Ʒ� ������ ������ �߰��Ѵ�.
				insert_edge(p, i, j);
			}

		}


	}
}
//���� �ش� �׷����� ���� �켱 Ž���� �����ϸ� �ȴ�.

// ���� ��ķ� ǥ���� �׷����� ���� ���� �켱 Ž��
int visited[MAX_VERTICES];

#define TRUE 1
#define FALSE 0
int flag = 0;

void cur(short x, short y)		//ȭ���� ���ϴ� x, y��ǥ�� ����
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void dfs_mat(GraphType* g, int v, int row_end, int col_end)
{
	if (flag == 1)return;
	int w;
	COORD pos = { 0,25 };
	visited[v] = TRUE; // ���� v�� �湮 ǥ��
	visual[g->a[v].row_ver][g->a[v].col_ver] = 64;		//64�� �ƽ�Ű�ڵ�� @��
	printf("\n");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	Sleep(300);							/// �̵��� �ĺ��ϱ� ���� 3��
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (visual[i][j] == 64) {
				printf("%c ", visual[i][j]);
			}
			else {
				printf("%d ", visual[i][j]);
			}
		}
		printf("\n");
	}

	if (g->a[v].col_ver == col_end - 1 && g->a[v].row_ver == row_end - 1) {	// 20 20 �� �������� ��
		printf("END");
		flag = 1;
		return;
	}
	for (w = 0; w < g->n; w++) {// ���� ���� Ž��

		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w, row_end, col_end); //���� w���� DFS ���� ����
	}
}


int main(void) {
	filein();
	//random();
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	maze_ver(g);
	maze_ed(g);
	printf(" ���� : \n");
	dfs_mat(g, 0, 20, 20);
}