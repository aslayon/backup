#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <CoreWindow.h>




#define MAX_VERTICES 400
typedef struct arrver {
	int row_ver;
	int col_ver;		//정점 좌표를 저장할 용도
}arrver;
typedef struct GraphType {
	int n;	// 정점의 개수
	arrver a[MAX_VERTICES];
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v, arrver item)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->a[g->n] = item;				///////////////////////해당 과정을통해 좌표도 저장
	g->n++;

}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
// 인접 행렬 출력 함수
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
//random 함수
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
//파일에서 읽어오기
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

void maze_ver(GraphType* p) {//이차원 행렬 -> 정점 만들기
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

void maze_ed(GraphType* p) {    //만든 정점들을 이어주는 함수 //
	if (p->a[0].col_ver != 0 || p->a[0].row_ver != 0) {
		printf("\n");
		printf("(0,0)이 벽으로 생성됨\n ERROR\n");
		printf("따라서 (%d, %d) 에서 시작\n", p->a[0].col_ver, p->a[0].row_ver);
	}
	for (int i = 0; i < p->n; i++) {
		int col_tmp = p->a[i].col_ver;
		int row_tmp = p->a[i].row_ver;
		for (int j = i + 1; j < p->n; j++) {
			if (p->a[j].col_ver == col_tmp + 1 && p->a[j].row_ver == row_tmp) {
				insert_edge(p, i, j);
			}
			if (p->a[j].col_ver == col_tmp && p->a[j].row_ver == row_tmp + 1) {   //순환하면서 현재 위치보다 한칸 오른쪽, 한칸 아래 있을때 엣지를 추가한다.
				insert_edge(p, i, j);
			}

		}


	}
}
//이후 해당 그래프로 깊이 우선 탐색을 수행하면 된다.

// 인접 행렬로 표현된 그래프에 대한 깊이 우선 탐색
int visited[MAX_VERTICES];

#define TRUE 1
#define FALSE 0
int flag = 0;

void cur(short x, short y)		//화면의 원하는 x, y좌표로 보냄
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void dfs_mat(GraphType* g, int v, int row_end, int col_end)
{
	if (flag == 1)return;
	int w;
	COORD pos = { 0,25 };
	visited[v] = TRUE; // 정점 v의 방문 표시
	visual[g->a[v].row_ver][g->a[v].col_ver] = 64;		//64가 아스키코드로 @임
	printf("\n");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	Sleep(300);							/// 이동을 식별하기 위한 3초
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

	if (g->a[v].col_ver == col_end - 1 && g->a[v].row_ver == row_end - 1) {	// 20 20 에 도달했을 때
		printf("END");
		flag = 1;
		return;
	}
	for (w = 0; w < g->n; w++) {// 인접 정점 탐색

		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w, row_end, col_end); //정점 w에서 DFS 새로 시작
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
	printf(" 시작 : \n");
	dfs_mat(g, 0, 20, 20);
}