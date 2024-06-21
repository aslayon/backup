#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 5000
char data[max];

void read(char *string) {
    FILE* fp;
    if (fopen_s(&fp, "d.txt", "r") != 0) {
        printf("파일 읽기 실패");
        return;
    }
    int line = 1, ct = 0;
    char* str;
    char buff[max];
    while (!feof(fp)) {
        str = fgets(buff, sizeof(buff), fp);
      
            int count = 0;
            int flag = 0;
            for (int i = 0; str[i] != '\0'; i++) {
                if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\r' && flag != 1) {
                    count++;
                    flag = 1;
                    ct = 0;
                    for (int j = i; str[j] != ' ' && str[j] != '\n' && str[j] != '\t' && str[j] != '\r'; j++) {
                        if (str[j] == string[ct]) {
                            ct++;
                        }
                        else break;
                    }
                    if (ct == strlen(string)) {
                        printf("(%d,%d),", line, count);
                    }
                }
                if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || flag != 1) {
                    flag = 0;
                }
            }
            line++;
    }
    fclose(fp);
}

tmp[cmpct] = '\0';
if (is_cmd(tmp) == 1) {
    flag_2 = 1;
    printf("cmd, ");

}
if (is_pcmd(tmp) == 1) {
    flag_2 = 1;
    printf("pcmd, ");

}
if (is_r_OR_num(tmp) == 1) {
    flag_2 = 1;
    printf("R16, ");

}
else if (is_r_OR_num(tmp) == 2) {
    flag_2 = 1;
    printf("R8, ");

}
else if (is_r_OR_num(tmp) == 3) {
    flag_2 = 1;
    printf("NUM, ");

}
if (flag_2 == 0) printf("SYMBOL, ");
count++;
flag = 1;

int main() {
    
    printf("\n찾을 단어 입력: ");
    char a[max];
    scanf("%s", a);
    printf("\n");
    read(a);
    return 0;
}
