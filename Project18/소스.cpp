#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZEE 10






int SIZE = 5;
// mem �� �޸�, page �� ����� ������
int num = 0;
int LRU(int* mem, int page) {
	int found = 0;
	//printf("\n������ : %d\n", page);
	for (int i = SIZEE -1; i >=0 ; i--) {
		if (mem[i] == -1) {	//mem �ʱⰪ -1
			//printf("%d �޸𸮿� ����\n", page);
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
		if (mem[i] == page) {//�޸𸮿� �̹�����  HIT 
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
		if (Memory[i] == -1) {	//mem �ʱⰪ -1   // �� �޸𸮺���� ���� ��
			for (int j = 0; j < i; j++) {
				if (Memory[j] == page) {
					printf(" HIT \n");
					found = 10;
					break;
				}
			}
			if (found == 10) break;
			printf("%d �޸𸮿� ����\n", page);
			int j;
			for (j = i; j >= 0; j--) {
				if (Memory[j] != -1) break;
			}
			Memory[j + 1] = page;
			found = 2;
			break;
		}
		if (Memory[i] == page) {//�޸𸮿� �̹�����  HIT 
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
	int mem[SIZEE];		// ���� ������ ����ϴ� �迭
	int Memory[SIZEE];

	int page;


	for (int i = 0; i < SIZEE; i++) {
		mem[i] = -1;
		Memory[i] = -1;
	}

	for (int i = 0; i < 100; i++) {
		page = rand() % 20 + 1;
		printf("\n ���� ������ : %d\n", page);// 0~10 ������ ������ ������ ����
		
		fillMemory(Memory, mem, page);
		LRU(mem, page);
		printf(" ����ߴ� ���� \t\t ");
		printMem(mem);
		printf(" ���� �޸� ����\t ");
		printMem(Memory);
	}
}

