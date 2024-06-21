#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS 
#define max 5000
char data[max];




void read() {
	FILE* fp;
	
	if (fopen_s(&fp, "d.txt", "r") != 0) { printf("파일 읽기 실패"); }

	fread(data,sizeof(char),sizeof(data),fp);
	fclose(fp);
	printf("%s",data);
}

int charc() {
	int count = 0;
	for (int i = 0; data[i] !='\0'; i++) {
		if (data[i] != ' ' && data[i] != '\n' && data[i] != '\t' && data[i] != '\r') {
			count++;
		}
	}
	return count;
}

int wordc() {
	int count = 0;
	int flag = 0;
	for (int i = 0; data[i] != '\0'; i++) {
		if (data[i] != ' ' && data[i] != '\n' && data[i] != '\t' && data[i] != '\r' && flag!=1) {
			count++;
			flag = 1;
		}
		if (data[i] == ' ' || data[i] == '\n' || data[i] == '\t' || data[i] == '\r' || flag != 1) {
			flag = 0;
		}
	}
	return count;
}


int numc() {
	int count = 0;
	for (int i = 0; data[i] != '\0'; i++) {
		if (data[i]>='0' && data[i]<='9') {
			count++;
		}
	}
	return count;
}

int main() {
	read();
	printf("\n글자 수 :%d\n단어 수 :%d\n숫자 수:%d", charc(), wordc(),numc());
}