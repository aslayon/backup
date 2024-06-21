#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 500
char data[max];
char Label[10][100];
int Label_loc[10] = { -1, };
int Label_n = 0;
char symbol[10][100];
int symbol_loc[10] = { -1, };
int symbol_n = 0;
int line_word[max] = { -1, };






int is_cmd(char* string) {
    char* cmd[] = { "MOV","ADD","SUB","AND","OR","INC","DEC","CMP","JMP","JA","JB","JE", "INT" };
    int flag = 0;
    for (int i = 0; i < 13; i++) {
        if (strcmp(cmd[i], string) == 0) {
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
        if (strcmp(string, R16[i]) == 0) { return 1; }

    }
    for (int i = 0; i < 8; i++) {
        if (strcmp(string, R8[i]) == 0) { return 2; }
    }

    return 0;
}



int is_Label_or_symbol(char* string) {



    for (int i = 0; i < Label_n; i++) {
        if (strcmp(string, Label[i]) == 0) return 1;
    }
    for (int i = 0; i < symbol_n; i++) {
        if (strcmp(string, symbol[i]) == 0) return 2;
    }

    return 0;
}



void first_read() {
    FILE* fp;
    if (fopen_s(&fp, "Assembly.txt", "r") != 0) {
        printf("파일 열기 실패");
        return;
    }
    printf("시작");
    int MAC_loc = 0;
    int MAC_count_line = 0;
    int MAC_count = 0;

    int line = 0;

    char buff[max];
    int MAC_flag = 0;

    int count = 0;
    int s_flag = 0;
    int linecount = 0;
    while (!feof(fp)) {
        count = 0;
        line++;
        int flag = 0;
        int s_flag = 0;
        char tmp[100];
        char MAC_tmp[100];
        char words[10][100] = {"",};
        int a = 0;
        int secflag = 0;
        char* str = fgets(buff, sizeof(buff), fp);
        int main_start_flag = 0;

        if (str == NULL)break;
        for (int i = 0; str[i] != '\0'; i++) {

            if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\r' && str[i] != '.' && str[i] != ',' && str[i] != ':' && flag == 0) {
                int cmpct = 0;
                count++;
                flag = 1;
                for (int j = i; str[j] != ' ' && str[j] != '\n' && str[j] != '\t' && str[j] != '\r' && str[j] != '.' && str[j] != ',' && str[j] != ':'; j++) {
                    tmp[cmpct] = str[j];
                    cmpct++;
                }
                tmp[cmpct] = '\0';
                if (count == 1) {
                    if (is_cmd(tmp) == 0 && is_r_OR_num(tmp) == 0) {
                        s_flag = 1;
                    }
                    else s_flag = 0;
                    if (strcmp(tmp, "MAIN") == 0 && main_start_flag == 0) {
                        main_start_flag = 1;
                    }
                    if (strcmp(tmp, "MAIN") == 0 && main_start_flag == 1) {
                        main_start_flag = 0;
                    }
                }
                if (s_flag == 1 && count == 2) {

                    if (strcmp(tmp, "DB") == 0 || strcmp(tmp, "DW") == 0) {

                        strcpy(symbol[symbol_n++], MAC_tmp);
                       
                        s_flag = 0;
                    }
                    else {
                        int dupl_flag = 0;
                        for (int k = 0; k < Label_n; k++) {
                            if (strcmp(MAC_tmp, Label[k]) == 0) {
                                dupl_flag = 1;
                            }
                        }
                        if (dupl_flag == 1) {}
                        else {
                            strcpy(Label[Label_n++], MAC_tmp);
                           
                        }
                        s_flag = 0;
                    }
                }

                strcpy(MAC_tmp,tmp);
                strcpy(words[a++], MAC_tmp);

            }
            if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || str[i] == '.' || str[i] == ',' || str[i] == ':') {
                flag = 0;
            }
        }
        int k = 0;
        for (int i = 0; i < count; i++) {
            printf("%s\n", words[i]);
        }
        printf("\n");
        if (main_start_flag == 1) {
           
            if (strcmp(words[k + 0], "ASSUME") == 0) continue;
            if (is_cmd(words[0]) == 0) k = k + 1;
            int head = is_r_OR_num(words[k + 1]);
            int tail = is_r_OR_num(words[k + 2]);
            if (strcmp(words[k + 0], "MOV") == 0) {
                if (strcmp(words[k + 1], "AX") == 0 && strcmp(words[k + 2], "CS") == 0) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 1 && tail == 1) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 1 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (head == 1 && tail == 0) {
                    if (strcmp(words[k + 1], "AX") == 0) {
                        line_word[linecount++] = 3;
                        continue;
                    }
                    line_word[linecount++] = 4;
                    continue;
                }
                if (head == 0 && tail == 1) {
                    if (strcmp(words[k + 1], "AX") == 0) {
                        line_word[linecount++] = 3;
                        continue;
                    }
                    line_word[linecount++] = 4;
                    continue;

                }
                if (head == 2 && tail == 2) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 2 && tail == 3) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 2 && tail == 0) {

                    line_word[linecount++] = 4;
                    continue;
                }
                if (head == 0 && tail == 1) {

                    line_word[linecount++] = 4;
                    continue;
                }

            }
            if (strcmp(words[k + 0], "ADD") == 0) {
                if (head == 1 && tail == 1) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 1 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (head == 1 && tail == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }
                if (head == 0 && tail == 1) {
                    line_word[linecount++] = 4;
                    continue;
                }

                if (head == 2 && tail == 2) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 2 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (head == 2 && tail == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }
                if (head == 0 && tail == 2) {
                    line_word[linecount++] = 4;
                    continue;
                }
            }
            if (strcmp(words[k + 0], "SUB") == 0) {
                if (head == 1 && tail == 1) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 1 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (head == 1 && tail == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }
                if (head == 0 && tail == 1) {
                    line_word[linecount++] = 4;
                    continue;
                }

                if (head == 2 && tail == 2) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 2 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (head == 2 && tail == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }
                if (head == 0 && tail == 2) {
                    line_word[linecount++] = 4;
                    continue;
                }
            }
            if (strcmp(words[k + 0], "AND") == 0) {
                if (head == 1 && tail == 1) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 1 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (head == 1 && tail == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }
                if (head == 0 && tail == 1) {
                    line_word[linecount++] = 4;
                    continue;
                }

                if (head == 2 && tail == 2) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 2 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (head == 2 && tail == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }
                if (head == 0 && tail == 2) {
                    line_word[linecount++] = 4;
                    continue;
                }
            }
            if (strcmp(words[k + 0], "OR") == 0) {
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 1) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 0 && tail == 1) {
                    line_word[linecount++] = 4;
                    continue;
                }

                if (is_r_OR_num(words[k + 1]) == 2 && tail == 2) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 2 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 2 && tail == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 0 && tail == 2) {
                    line_word[linecount++] = 4;
                    continue;
                }
            }
            if (strcmp(words[k + 0], "INC") == 0) {
                if (is_r_OR_num(words[k + 1]) == 1) {
                    line_word[linecount++] = 1;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }

                if (is_r_OR_num(words[k + 1]) == 2) {
                    line_word[linecount++] = 2;
                    continue;
                }

            }

            if (strcmp(words[k + 0], "DEC") == 0) {
                if (is_r_OR_num(words[k + 1]) == 1) {
                    line_word[linecount++] = 1;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }

                if (is_r_OR_num(words[k + 1]) == 2) {
                    line_word[linecount++] = 2;
                    continue;
                }

            }

            if (strcmp(words[k + 0], "CMP") == 0) {
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 1) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }


                if (is_r_OR_num(words[k + 1]) == 2 && tail == 2) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 2 && tail == 3) {
                    line_word[linecount++] = 3;
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 2 && tail == 0) {
                    line_word[linecount++] = 4;
                    continue;
                }
            }
            if (strcmp(words[k + 0], "JMP") == 0) {
                line_word[linecount++] = 2;
                continue;
            }
            if (strcmp(words[k + 0], "JA") == 0) {
                line_word[linecount++] = 2;
                continue;
            }
            if (strcmp(words[k + 0], "JE") == 0) {
                line_word[linecount++] = 2;
                continue;
            }
            if (strcmp(words[k + 0], "JB") == 0) {
                line_word[linecount++] = 2;
                continue;
            }
        }
    }
    fclose(fp);



    printf("라벨들");
    for (int i = 0; i < Label_n; i++) {
        printf(" %s", Label[i]);
    }
    printf("\n심볼들 ");
    for (int i = 0; i < symbol_n; i++) {
        printf(" %s", symbol[i]);
    }
    for (int i = 0; i < linecount; i++) {
        printf(" %d\n", line_word[i]);
    }
    printf("\n");
}
void read() {
    FILE* fp;
    if (fopen_s(&fp, "Assembly.txt", "r") != 0) {
        printf("파일 읽기 실패");
        return;
    }
    int line = 0;
    char* str;
    char buff[max];
    char tmp[100];
    int words_count[50] = { 0, };
    int flag_2 = 0;
    while (!feof(fp)) {
        str = fgets(buff, sizeof(buff), fp);
        if (str == NULL)break;
        printf("\n\n%s\n", str);
        int count = 0;
        int flag = 0;
        int cmpct = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\r' && str[i] != '.' && str[i] != ',' && str[i] != ':' && flag == 0) {
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
                    printf("[Opcd], ");

                }

                if (is_r_OR_num(tmp) == 1) {
                    flag_2 = 1;
                    printf("[Reg16], ");

                }
                else if (is_r_OR_num(tmp) == 2) {
                    flag_2 = 1;
                    printf("[Reg08], ");

                }
                else if (is_r_OR_num(tmp) == 3) {
                    flag_2 = 1;
                    printf("[NUMb], ");

                }
                if (is_Label_or_symbol(tmp) == 1) {
                    printf("[Labl], ");
                    flag_2 = 1;
                }
                else if (is_Label_or_symbol(tmp) == 2) {
                    printf("[Symb], ");
                    flag_2 = 1;
                }
                if (flag_2 == 0) {
                    if (strcmp(tmp, "SEGMENT") == 0) {
                        printf("[Direc], ");
                    }

                    else printf("[Numb], ");
                }
                flag = 1;

            }
            if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || str[i] == '.' || str[i] == ',' || str[i] == ':') {
                flag = 0;
            }
        }
        words_count[line] = count;

        words_count[line++] = -1;
    }



}

int main() {
    first_read();

    return 0;
}
