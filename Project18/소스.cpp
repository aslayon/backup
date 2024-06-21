#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZEE 10






int SIZE = 5;
// mem 은 메모리, page 는 적재될 페이지
int num = 0;
int LRU(int* mem, int page) {
	int found = 0;
	//printf("\n페이지 : %d\n", page);
	for (int i = SIZEE -1; i >=0 ; i--) {
		if (mem[i] == -1) {	//mem 초기값 -1
			//printf("%d 메모리에 적재\n", page);
			for (int j = 0; j < i; j++) {
				if (mem[j] == page) {
					found = 10;
					break;
				}
			}
			if (found == 10) break;

			int j;
			for (j = i; j >= 0; j--) {
				if (mem[j] != -1) break;
			}
			mem[j+1] = page;
			found = 2;
			break;
		}
		if (mem[i] == page) {//메모리에 이미적재  HIT 
			//printf(" HIT \n", page);
			for (int j = i; j <= SIZEE - 2; j++) {
				mem[j] = mem[j + 1];
			}
			mem[SIZEE - 1] = page;
			found = 1;
			break;
		}
		
	}
	if (found == 0) {
		//printf(" MISS \n", page);
		for (int i = 0; i <= SIZEE - 2; i++) {
			mem[i] = mem[i + 1];
		}
		mem[SIZEE - 1] = page;
	}
	return found;
}

void printMem(int* mem) {
	printf(" [");
	for (int i = 0; i < SIZEE; i++) {
		printf(" %d ", mem[i]);
	}
	printf("]\n");
}
void fillMemory(int* Memory , int * mem,int page) {
	int found = 0;
	for (int i = SIZEE - 1; i >= 0; i--) {
		if (Memory[i] == -1) {	//mem 초기값 -1   // 빈 메모리블록이 있을 때
			for (int j = 0; j < i; j++) {
				if (Memory[j] == page) {
					printf(" HIT \n");
					found = 10;
					break;
				}
			}
			if (found == 10) break;
			printf("%d 메모리에 적재\n", page);
			int j;
			for (j = i; j >= 0; j--) {
				if (Memory[j] != -1) break;
			}
			Memory[j + 1] = page;
			found = 2;
			break;
		}
		if (Memory[i] == page) {//메모리에 이미적재  HIT 
			found = 1;
			printf(" HIT \n");
			break;
		}

	}
	if (found == 0) { // MISS
		printf(" MISS \n");
		for (int i = 0; i < SIZEE; i++) {
			for (int j = 0; j < SIZEE; j++) {
				if (Memory[j] == mem[i]) {
					found = 3;
					Memory[j] = page;
					break;
				}

			}
			if (found == 3) break;
		}	
	}
}

int main() {
	int mem[SIZEE];		// 사용된 순서를 기억하는 배열
	int Memory[SIZEE];

	int page;


	for (int i = 0; i < SIZEE; i++) {
		mem[i] = -1;
		Memory[i] = -1;
	}

	for (int i = 0; i < 100; i++) {
		page = rand() % 20 + 1;
		printf("\n 접근 페이지 : %d\n", page);// 0~10 사이의 랜덤한 페이지 생성
		
		fillMemory(Memory, mem, page);
		LRU(mem, page);
		printf(" 사용했던 순서 \t\t ");
		printMem(mem);
		printf(" 현재 메모리 내부\t ");
		printMem(Memory);
	}
}

