#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 10

void rtn() {
	FILE* fp = 0;
	fopen_s(&fp, "data.txt", "r");
	if (fp == NULL) {
		printf("�б� ����");
		return;
	}
	int cnt = 0, flag =0;
	char in[max][50] = { 0, };
	char a[50];
	while (fscanf(fp, "%s", a) != EOF) {
		strcpy(in[cnt], a);
		cnt++;
	}
	printf("�о�� ������\n");
	for (int i = 0; i < max; i++) {
		printf("%s ", in[i]);
	}
	fclose(fp);
	while (1) {            //��� �ݺ�
		flag = 0;
		printf("\nã�� �ܾ� �Է�\n");
		scanf("%s", a);
		for (int t = 0; t < 10; t++) {
			cnt = 0;
			for (int j = 0; j < strlen(in[t]); j++) {
				if (in[t][j] == a[j]) {
					cnt++;
				}
			}
			if (cnt == strlen(in[t])) {
				printf("%s�� %d ��°�� �ֽ��ϴ�\n", in[t], t + 1);
				for (int i = strlen(in[t]); i >= 0; i--) {
					printf("%c", in[t][i]);
					flag = 1;
				}
			}
		}
		if (strcmp(a, "0") == 0) { printf("����"); break; }
		if (flag == 0) printf("�ش� �ܾ� ����\n");
	}
	return 0;
}

int main() {
	rtn();

}