#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 10

void rtn() {
	FILE* fp = 0;
	fopen_s(&fp, "data.txt", "r");
	if (fp == NULL) {
		printf("읽기 오류");
		return;
	}
	int cnt = 0, flag =0;
	char in[max][50] = { 0, };
	char a[50];
	while (fscanf(fp, "%s", a) != EOF) {
		strcpy(in[cnt], a);
		cnt++;
	}
	printf("읽어온 데이터\n");
	for (int i = 0; i < max; i++) {
		printf("%s ", in[i]);
	}
	fclose(fp);
	while (1) {            //계속 반복
		flag = 0;
		printf("\n찾을 단어 입력\n");
		scanf("%s", a);
		for (int t = 0; t < 10; t++) {
			cnt = 0;
			for (int j = 0; j < strlen(in[t]); j++) {
				if (in[t][j] == a[j]) {
					cnt++;
				}
			}
			if (cnt == strlen(in[t])) {
				printf("%s는 %d 번째에 있습니다\n", in[t], t + 1);
				for (int i = strlen(in[t]); i >= 0; i--) {
					printf("%c", in[t][i]);
					flag = 1;
				}
			}
		}
		if (strcmp(a, "0") == 0) { printf("종료"); break; }
		if (flag == 0) printf("해당 단어 없음\n");
	}
	return 0;
}

int main() {
	rtn();

}