#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 500
char data[max];

int is_cmd(char* string ) {
    char* cmd[] = { "MOV","PUSH","POP","XCHG","IN","OUT","XLAT","LEA","LDS","LES","SAHF","LAHF","PUSHIF","POPF","ADD","SBB","DEC","NEG","CMP","ADC","INC","AAA","DAA","SUB","MUL","AAM","DIV","NOT","SHR","SAR","AND","TEST","OR","XOR","REP","CALL","JMP","RET","JE","JZ","JL","JNGE","JB","JNAE","JBE","JBA","JP","JPE","JO","JS","JNE","JNZ","JNL","JGE","JNLE","JG","JNB","JAE","JNBE","JA","JNP","JPO","JNO","JNS","LOOP","LOOPZ","LOOPE","LOOPNZ","LOOPNE","JCXZX","INT","INTO","IRET","CLC","CMC","CLI","CLD","HLT","LOCK","STC","NOP","STD","STI","WAIT","ESC"};
    int flag = 0;
        for (int i = 0; i < 82; i++) {
            if (strcmp(cmd[i], string) == 0) {
                flag = 1;
                break;
            }
        }
    
    return flag;
}

int is_pcmd(char* string) {
    int flag = 0;
    char* pcmd[] = { "SEGMENT","END","PROC","ENDP","ASSUME", "DB","DW","DD","DQ","DT","=","EVEN","PAGE","TITLE" };
   
        for (int i = 0; i < 14; i++) {
            if (strcmp(pcmd[i], string) == 0) {
                flag = 1;
                break;
            }
        }
    
    return flag;
}

int is_num(char* string) {
    if (string[0] >= '0' && string[0] <= '9') {
        return 1;
    }
    return 0;
}

int is_r_OR_num(char* string) {
    char* R16[] = { "AX","BX","CX","DX","CS","IP","SS","SP","BP","SI","DI","DS","ES" };
    char* R8[] = { "AH","AL","BH","BL","CH","CL","DH","DL" };
   
        if (is_num(string) == 1) return 3;
        for (int i = 0; i < 13; i++) { 
            if (strcmp(string, R16[i]) == 0) return 1;
        }
        for (int i = 0; i < 8; i++) {
            if (strcmp(string, R8[i]) == 0) return 2;
        }
    
    return 0;
}

void read() {
    FILE* fp;
    if (fopen_s(&fp, "prog1.asm", "r") != 0) {
        printf("파일 읽기 실패");
        return;
    }
    int line = 0;
    char* str;
    char buff[max];
    char tmp[100];
    int words_count[20] = { 0, };
    int flag_2 = 0;
    char* string;
    while (!feof(fp)) {
        str = fgets(buff, sizeof(buff), fp);
        printf("\n\n%s\n", str);
        int count = 0;
        int flag = 0;
        int cmpct = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\r' && str[i] != '.' && str[i] != ',' && str[i] != ':' && flag ==0) {
                count++;
                flag = 1;
                cmpct = 0;
                for (int j = i; str[j] != ' ' && str[j] != '\n' && str[j] != '\t' && str[j] != '\r' && str[j] != '.' && str[j] != ',' && str[j] != ':'; j++) {
                    tmp[cmpct] = str[j];
                    cmpct++;
                }
                tmp[cmpct] = '\0';
                flag_2 = 0;
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

            }
            if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || str[i] == '.' || str[i] == ',' || str[i] == ':') {
                flag = 0;
            }
        }
        words_count[line] = count;
        line++;
    }
       
        
       
    }

int main() {
    read(); // 함수를 호출하는 부분이 누락되었습니다.
    return 0;
}
