#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max 5000
char data[max];
char words[max][100];
int words_count = 0; // 단어 개수를 나타내는 변수를 메인 함수에서 선언

void read() {
    FILE* fp;

    if (fopen_s(&fp, "d.txt", "r") != 0) {
        printf("파일 읽기 실패");
        return;
    }

    fread(data, sizeof(char), sizeof(data), fp);
    fclose(fp);
    printf("%s", data);
}

void word() {
    int col = 1, count = 0, flag = 0, cmpct = 0;
    char tmp[100];

    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] != ' ' && data[i] != '\n' && data[i] != '\t' && data[i] != '\r' && flag != 1) {
            count++;
            flag = 1;
            cmpct = 0;
            for (int j = i; data[j] != ' ' && data[j] != '\n' && data[j] != '\t' && data[j] != '\r' && data[j] != '.' && data[j] != ','; j++) {
                tmp[cmpct] = data[j];
                cmpct++;
            }
            tmp[cmpct] = '\0';
            strcpy(words[words_count++], tmp);
        }
        if (data[i] == ' ' || data[i] == '\n' || data[i] == '\t' || data[i] == '\r' || flag != 1) {
            flag = 0;
        }
    }
}

void sort() {
    int min = 0;
    char tmp[100];
    for (int i = 0; i < words_count; i++) {
        min = i;
        for (int j = i+1; j < words_count; j++) {
            if (strcmp(words[j], words[min]) < 0) {
                min = j;
            }
        }
        if (min != i) {
            strcpy(tmp, words[i]);
            strcpy(words[i], words[min]);
            strcpy(words[min], tmp);
        }
   }
}

int search(char* string) {
    int left = 0;
    int right = words_count;
    int cmpct = 0;
    int low=-1, high = -1;
    while (left <= right) {
        int middle = (left + right) / 2;
        int cmp = strcmp(string, words[middle]);

        if (cmp == 0) {
            low = high = middle;

            while (1) {
                if (strcmp(string, words[low]) == 0) {
                    low --;
                }
                else break;
            }
            while (1) {
                if (strcmp(string, words[high]) == 0) {
                    high ++;
                }
                else break;
            }
            for (int i = low+1; i < high; i++) {
                printf("%d 번째\n", i);
            }
            return middle; // 단어를 찾았을 때의 인덱스 반환
        }
        else if (cmp < 0) {
            right = middle - 1; // 중간 값보다 작으면 왼쪽 부분 탐색
        }
        else {
            left = middle + 1; // 중간 값보다 크면 오른쪽 부분 탐색
        }
    }
    return -1;
}
/*int search(char* string) {

    for (int i = 0; string[i]; i++) {
        string[i] = tolower(string[i]);
    }

    int left = 0;
    int right = words_count - 1;

    while (left <= right) {
        int middle = (left + right) / 2;
        char lowerWord[100]; 
        strcpy(lowerWord, words[middle]);

        // 배열 내 단어를 소문자로 변환
        for (int i = 0; lowerWord[i]; i++) {
            lowerWord[i] = tolower(lowerWord[i]);
        }

        int cmp = strcmp(string, lowerWord);

        if (cmp == 0) {
            return middle; // 단어를 찾았을 때의 인덱스 반환
        }
        else if (cmp < 0) {
            right = middle - 1; // 중간 값보다 작으면 왼쪽 부분 탐색
        }
        else {
            left = middle + 1; // 중간 값보다 크면 오른쪽 부분 탐색
        }
    }

    return -1; // 단어를 찾지 못했을 때 -1 반환
}
*/
int main() {
    read();
    word();
   
    sort();
    for (int i = 0; i < words_count; i++) {
        printf("%d. %s\n", i, words[i]);
    }
    printf("\n");
    printf("\n찾을 단어 입력: ");
    char a[max];
    scanf("%s", a);
    printf("\n");
    int b = search(a);
    if (b == -1) {
        printf("%s 는 없습니다.", a);
    }
    return 0;
}
