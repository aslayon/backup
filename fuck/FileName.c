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
int symbol_elnum[10] = { -1, };
int symbol_stat[10] = { -1, };
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
    if (string[0] == '[') return 4;
    return 0;
}



int is_Label_or_symbol(char* string) {



    for (int i = 0; i < Label_n; i++) {
        if (strcmp(string, Label[i]) == 0) return i;
    }
    for (int i = 0; i < symbol_n; i++) {
        if (strcmp(string, symbol[i]) == 0) return i;
    }

    return -1;
}

int rtn_r_wd(char* string) {
    if (strcmp(string, "AX") == 0) {
        return 0;
    }
    if (strcmp(string, "BX") == 0) {
        return 3;
    }
    if (strcmp(string, "CX") == 0) {
        return 1;
    }
    if (strcmp(string, "DX") == 0) {
        return 2;
    }
    if (strcmp(string, "SI") == 0) {
        return 6;
    }
    if (strcmp(string, "DI") == 0) {
        return 7;
    }
}

int rtn_r_bt(char* string) {
    if (strcmp(string, "AH") == 0) {
        return 4;
    }
    if (strcmp(string, "BH") == 0) {
        return 7;
    }
    if (strcmp(string, "CH") == 0) {
        return 5;
    }
    if (strcmp(string, "DH") == 0) {
        return 6;
    }
    if (strcmp(string, "AL") == 0) {
        return 0;
    }
    if (strcmp(string, "BL") == 0) {
        return 3;
    }
    if (strcmp(string, "CL") == 0) {
        return 1;
    }
    if (strcmp(string, "DL") == 0) {
        return 2;
    }
}

int rtn_sl_loc(char* string) {
    for (int i = 0; i < symbol_n; i++) {
        if (strcmp(string, symbol[i]) == 0) {
            return symbol_loc[i];
        }
    }
    for (int i = 0; i < Label_n; i++) {
        if (strcmp(string, Label[i]) == 0) {
            return Label_loc[i];
        }
    }
}
int rtn_symbol_bcd(char* string) {
    if (strcmp(string, "AX") == 0 || strcmp(string, "AL") == 0) {
        return 6;
    }
    if (strcmp(string, "BX") == 0 || strcmp(string, "BL") == 0) {
        return 30;
    }
    if (strcmp(string, "CX") == 0 || strcmp(string, "CL") == 0) {
        return 14;
    }
    if (strcmp(string, "DX") == 0 || strcmp(string, "DL") == 0) {
        return 22;
    }
    if (strcmp(string, "DI") == 0) {
        return 62;
    }
    if (strcmp(string, "SI") == 0) {
        return 54;
    }
    if (strcmp(string, "AH") == 0) {
        return 38;
    }
    if (strcmp(string, "BH") == 0) {
        return 62;
    }if (strcmp(string, "CH") == 0) {
        return 46;
    }
    if (strcmp(string, "DH") == 0) {
        return 54;
    }
}


void first_read() {
    FILE* fp;
    if (fopen_s(&fp, "Assembly.txt", "r") != 0) {
        printf("파일 열기 실패");
        return;
    }
    int MAC_loc = 0;
    int MAC_count_line = 0;
    int MAC_count = 0;
    int flaglinecounter = 0;
    int line = 0;

    char buff[max];
    int MAC_flag = 0;

    int count = 0;
    int s_flag = 0;
    int linecount = 0;
    int main_start_flag = 0;
    while (!feof(fp)) {
        int db = 0;
        int dw = 0;
        int datnum = 0;
        count = 0;
        line++;
        int flag = 0;
        int s_flag = 0;
        char tmp[100];
        char MAC_tmp[100];
        char words[10][100] = { "", };
        int a = 0;
        int secflag = 0;
        char* str = fgets(buff, sizeof(buff), fp);
        printf(" %s\n", str);
        if (main_start_flag == 1) {
            flaglinecounter++;
        }
        printf("%d 번째 줄\n", flaglinecounter);
        if (str == NULL)break;
        for (int i = 0; str[i] != '\0'; i++) {

            if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\r' && str[i] != '.' && str[i] != ',' && str[i] != ':' && flag == 0) {
                if (db == 1) {
                    datnum++;
                }
                if (dw == 1) {
                    datnum++;
                }
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

                    if (strcmp(tmp, "ENDS") == 0 && main_start_flag == 1) {
                        printf("끝\n");
                        main_start_flag = 0;
                    }
                    if (strcmp(tmp, "MAIN") == 0 && main_start_flag == 0) {
                        printf("시작\n");
                        main_start_flag = 1;
                    }
                    if (main_start_flag == 1) {
                        if (strcmp(tmp, "MAIN") == 0 || strcmp(tmp, "ASSUME") == 0)
                            flaglinecounter--;
                    }
                }
                if (s_flag == 1 && count == 2) {

                    if (strcmp(tmp, "DB") == 0 || strcmp(tmp, "DW") == 0) {
                        if (strcmp(tmp, "DB") == 0) {
                            db = 1;
                        }
                        if (strcmp(tmp, "DW") == 0) {
                            dw = 1;
                        }
                        strcpy(symbol[symbol_n], MAC_tmp);
                        symbol_loc[symbol_n++] = flaglinecounter;
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

                            strcpy(Label[Label_n], MAC_tmp);
                            Label_loc[Label_n++] = flaglinecounter;
                        }
                        s_flag = 0;
                    }
                }

                strcpy(MAC_tmp, tmp);
                strcpy(words[a++], MAC_tmp);

            }
            if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || str[i] == '.' || str[i] == ',' || str[i] == ':') {
                flag = 0;
            }
        }
        if (dw == 1) {
            symbol_elnum[symbol_n - 1] = datnum * 2;
            symbol_stat[symbol_n - 1] = 2;
        }
        if (db == 1) {
            symbol_elnum[symbol_n - 1] = datnum * 1;
            symbol_stat[symbol_n - 1] = 1;
        }
        int k = 0;


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
                if (strcmp(words[k + 1], "DS") == 0 && strcmp(words[k + 2], "AX") == 0) {
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
                if (head == 1 && tail == 4) {
                    line_word[linecount++] = 2;
                    continue;
                }
                if (head == 4 && tail == 1) {
                    line_word[linecount++] = 2;
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
                    if (strcmp(words[k + 1], "AL") == 0) {
                        line_word[linecount++] = 3;
                        continue;
                    }
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
                    if (strcmp(words[k + 1], "AL") == 0) {
                        line_word[linecount++] = 2;
                        continue;
                    }
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
                    if (strcmp(words[k + 1], "AL") == 0) {
                        line_word[linecount++] = 2;
                        continue;
                    }
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
                    if (strcmp(words[k + 1], "AL") == 0) {
                        line_word[linecount++] = 2;
                        continue;
                    }
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
                    if (strcmp(words[k + 1], "AL") == 0) {
                        line_word[linecount++] = 2;
                        continue;
                    }
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
                    if (strcmp(words[k + 1], "AL") == 0) {
                        line_word[linecount++] = 2;
                        continue;
                    }
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
    printf("라벨들\n");
    for (int i = 0; i < Label_n; i++) {
        printf(" %s", Label[i]);
        printf(" %02x", Label_loc[i]);
        printf("\n");
    }
    printf("\n심볼들\n ");
    for (int i = 0; i < symbol_n; i++) {
        printf(" %s", symbol[i]);
        printf(" %d", symbol_loc[i]);
        printf(" %d", symbol_elnum[i]);
        printf("\n");
    }
    int locct = 0;
    printf("\n");

    for (int i = 0; i < Label_n; i++) {
        if (strcmp(Label[i], "MAIN") == 0 || strcmp(Label[i], "ASSUME") == 0)continue;
        printf("%s 의 주소는 ", Label[i]);
        for (int j = 0; j < Label_loc[i]; j++) {
            locct += line_word[j];

        }

        printf("%02x\n", locct);
        Label_loc[i] = locct;
        locct = 0;
    }

    for (int i = 0; i < symbol_n; i++) {
        printf("%s 의 주소는 ", symbol[i]);
        for (int j = 0; j < symbol_loc[i]; j++) {
            locct += line_word[j];

        }
        if (i != 0) {
            for (int j = 0; j < i; j++) {
                locct += symbol_elnum[j];
            }
        }
        printf("%x\n", locct);
        symbol_loc[i] = locct;
        locct = 0;
    }

    printf("\n");
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
    int main_start_flag = 0;
    int line = 0;
    char* str;
    char buff[max];
    char tmp[100];
    int flag_2 = 0;
    int print_flag = 0;
    int linecount = 0;
    while (!feof(fp)) {
        str = fgets(buff, sizeof(buff), fp);

        if (str == NULL)break;
        if (main_start_flag == 1) {
            linecount++;
        }
        int count = 0;
        int flag = 0;
        int cmpct = 0;
        char words[10][100] = { "", };
        int a = 0;
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
                if (count == 1) {

                    if (strcmp(tmp, "ENDS") == 0 && main_start_flag == 1) {

                        main_start_flag = 0;
                    }
                    if (strcmp(tmp, "MAIN") == 0 && main_start_flag == 0) {

                        main_start_flag = 1;
                    }
                }


                strcpy(words[a++], tmp);
            }
            if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || str[i] == '.' || str[i] == ',' || str[i] == ':') {
                flag = 0;
            }
        }

        int k = 0;
        int ln = 0;
        if (linecount > 1) {
            for (int i = -1; i < linecount - 1; i++) {
                if (linecount - 1 == 0)break;
                ln += line_word[i - 1];

            }
        }

        if (main_start_flag == 1) {

            if (strcmp(words[k + 0], "ASSUME") == 0) continue;
            if (is_cmd(words[0]) == 0) k = k + 1;
            int head = is_r_OR_num(words[k + 1]);


            int tail = is_r_OR_num(words[k + 2]);


            if (strcmp(words[k + 0], "MOV") == 0) {
                if (strcmp(words[k + 1], "AX") == 0 && strcmp(words[k + 2], "CS") == 0) {


                    printf("\n%04x\t8C\tC8\n", ln);

                    continue;
                }
                if (strcmp(words[k + 1], "DS") == 0 && strcmp(words[k + 2], "AX") == 0) {


                    printf("\n%04x\t82\tD8\n", ln);

                    continue;
                }
                if (head == 1 && tail == 1) {



                    printf("\n%04x\t%02x\t%02x\n", ln, 139, 192 + (8 * rtn_r_wd(words[k + 1])) + rtn_r_wd(words[k + 2]));

                    continue;
                }
                if (head == 1 && tail == 3) {



                    if (strcmp(words[k + 1], "AX") == 0) {

                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 184, words[k + 2], 0);
                    }
                    if (strcmp(words[k + 1], "BX") == 0) {

                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 187, words[k + 2], 0);
                    }
                    if (strcmp(words[k + 1], "CX") == 0) {

                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 185, words[k + 2], 0);
                    }
                    if (strcmp(words[k + 1], "DX") == 0) {

                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 186, words[k + 2], 0);
                    }
                    if (strcmp(words[k + 1], "DI") == 0) {

                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 191, words[k + 2], 0);
                    }
                    if (strcmp(words[k + 1], "SI") == 0) {

                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 190, words[k + 2], 0);
                    }


                    continue;
                }
                if (head == 1 && tail == 4) {


                    printf("\n%04x\t%02x\t%02x\n", ln, 139, (8 * rtn_r_wd(words[k + 1])) + rtn_r_wd(words[k + 2]));
                    //대괄호 내부값을 어떻게 처리할지.?
                    continue;
                }
                if (head == 4 && tail == 1) {


                    printf("\n%04x\t%02x\t%02x\n", ln, 89, (8 * rtn_r_wd(words[k + 1])) + rtn_r_wd(words[k + 2]));

                    continue;
                }                                                                                                       //마찬가지 대괄호 내부
                if (head == 1 && tail == 0) {

                    if (strcmp(words[k + 1], "AX") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\n", ln, 161, rtn_sl_loc(words[k + 2]), 0);
                        continue;
                    }
                    else {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 139, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                        continue;
                    }


                    continue;
                }
                if (head == 0 && tail == 1) {


                    if (strcmp(words[k + 1], "AX") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\n", ln, 163, rtn_sl_loc(words[k + 2]), 0);
                        continue;
                    }
                    else {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 137, rtn_symbol_bcd(words[k + 2]), rtn_sl_loc(words[k + 1]), 0);
                        continue;
                    }

                }
                if (head == 2 && tail == 2) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 138, 192 + (8 * rtn_r_bt(words[k + 1])) + rtn_r_bt(words[k + 2]));
                    continue;
                }
                if (head == 2 && tail == 3) {
                    if (strcmp(words[k + 1], "AH") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 180, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BH") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 183, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CH") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 181, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DH") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 182, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "AL") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 176, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BL") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 179, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CL") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 177, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DL") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 178, words[k + 2]);
                    }
                    continue;
                }
                if (head == 2 && tail == 0) {
                    if (strcmp(words[k + 1], "AH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 138, 38, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "BH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 138, 62, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "CH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 138, 46, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "DH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 138, 54, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "AL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\n", ln, 160, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "BL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 138, 30, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "CL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 138, 14, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "DL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 138, 22, rtn_sl_loc(words[k + 2]), 0);
                    }

                    continue;
                }
                if (head == 0 && tail == 1) {
                    if (strcmp(words[k + 1], "AH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 136, 38, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "BH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 136, 62, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "CH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 136, 46, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "DH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 136, 54, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "AL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\n", ln, 162, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "BL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 136, 30, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "CL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 136, 14, rtn_sl_loc(words[k + 2]), 0);
                    }
                    if (strcmp(words[k + 1], "DL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 136, 22, rtn_sl_loc(words[k + 2]), 0);
                    }

                    continue;
                }

            }
            if (strcmp(words[k + 0], "ADD") == 0) {
                if (head == 1 && tail == 1) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 03, 192 + (8 * rtn_r_wd(words[k + 1])) + rtn_r_wd(words[k + 2]));
                    continue;
                }
                if (head == 1 && tail == 3) {
                    if (strcmp(words[k + 1], "AX") == 0) {
                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 5, words[k + 2], 0);

                    }
                    if (strcmp(words[k + 1], "BX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 195, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 193, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 194, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DI") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 199, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "SI") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 198, words[k + 2]);
                    }
                    continue;
                }
                if (head == 1 && tail == 0) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 3, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                    continue;
                }
                if (head == 0 && tail == 1) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 1, rtn_symbol_bcd(words[k + 2]), rtn_sl_loc(words[k + 1]), 0);
                    continue;
                }

                if (head == 2 && tail == 2) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 03, 192 + (8 * rtn_r_bt(words[k + 1])) + rtn_r_bt(words[k + 2]));
                    continue;
                }
                if (head == 2 && tail == 3) {
                    if (strcmp(words[k + 1], "AH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 80, 196, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 80, 199, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 80, 197, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 80, 198, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "AL") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 04, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 195, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 193, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 194, words[k + 2]);
                    }
                    continue;
                }
                if (head == 2 && tail == 0) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 02, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                    continue;
                }
                if (head == 0 && tail == 2) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 00, rtn_symbol_bcd(words[k + 2]), rtn_sl_loc(words[k + 1]), 0);
                    continue;
                }
            }
            if (strcmp(words[k + 0], "SUB") == 0) {
                if (head == 1 && tail == 1) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 43, 192 + (8 * rtn_r_wd(words[k + 1])) + rtn_r_wd(words[k + 2]));
                    continue;
                }
                if (head == 1 && tail == 3) {
                    if (strcmp(words[k + 1], "AX") == 0) {
                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 45, words[k + 2], 0);
                    }
                    if (strcmp(words[k + 1], "BX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 235, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 233, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 234, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DI") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 239, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "SI") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 238, words[k + 2]);
                    }
                    continue;
                }
                if (head == 1 && tail == 0) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 43, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                    continue;
                }
                if (head == 0 && tail == 1) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 41, rtn_symbol_bcd(words[k + 2]), rtn_sl_loc(words[k + 1]), 0);
                    continue;
                }

                if (head == 2 && tail == 2) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 42, 192 + (8 * rtn_r_bt(words[k + 1])) + rtn_r_bt(words[k + 2]));
                    continue;
                }
                if (head == 2 && tail == 3) {
                    if (strcmp(words[k + 1], "AH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 80, 236, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 80, 239, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 80, 237, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 80, 238, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "AL") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 44, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 235, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 233, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 234, words[k + 2]);
                    }
                    continue;
                }
                if (head == 2 && tail == 0) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 42, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                    continue;
                }
                if (head == 0 && tail == 2) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 40, rtn_symbol_bcd(words[k + 2]), rtn_sl_loc(words[k + 1]), 0);
                    continue;
                }
            }
            if (strcmp(words[k + 0], "AND") == 0) {
                if (head == 1 && tail == 1) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 35, 192 + (8 * rtn_r_wd(words[k + 1])) + rtn_r_wd(words[k + 2]));
                    continue;
                }
                if (head == 1 && tail == 3) {
                    if (strcmp(words[k + 1], "AX") == 0) {
                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 37, words[k + 2], 0);
                    }
                    if (strcmp(words[k + 1], "BX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 227, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 225, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 226, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DI") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 231, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "SI") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 230, words[k + 2]);
                    }

                    continue;
                }
                if (head == 1 && tail == 0) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 35, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                    continue;
                }
                if (head == 0 && tail == 1) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 33, rtn_symbol_bcd(words[k + 2]), rtn_sl_loc(words[k + 1]), 0);
                    continue;
                }

                if (head == 2 && tail == 2) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 34, 192 + (8 * rtn_r_bt(words[k + 1])) + rtn_r_bt(words[k + 2]));
                    continue;
                }
                if (head == 2 && tail == 3) {
                    if (strcmp(words[k + 1], "AH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 228, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 231, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 229, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 230, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "AL") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 36, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 227, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 225, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 226, words[k + 2]);
                    }
                    continue;
                }
                if (head == 2 && tail == 0) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 34, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                    continue;
                }
                if (head == 0 && tail == 2) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 32, rtn_symbol_bcd(words[k + 2]), rtn_sl_loc(words[k + 1]), 0);
                    continue;
                }
            }
            if (strcmp(words[k + 0], "OR") == 0) {
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 1) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 11, 192 + (8 * rtn_r_wd(words[k + 1])) + rtn_r_wd(words[k + 2]));
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 3) {

                    if (strcmp(words[k + 1], "AX") == 0) {
                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 13, words[k + 2], 0);
                    }
                    if (strcmp(words[k + 1], "BX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 203, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 201, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 202, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DI") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 207, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "SI") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 206, words[k + 2]);
                    }

                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 0) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 11, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 0 && tail == 1) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 9, rtn_symbol_bcd(words[k + 2]), rtn_sl_loc(words[k + 1]), 0);
                    continue;
                }

                if (is_r_OR_num(words[k + 1]) == 2 && tail == 2) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 10, 192 + (8 * rtn_r_bt(words[k + 1])) + rtn_r_bt(words[k + 2]));
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 2 && tail == 3) {
                    if (strcmp(words[k + 1], "AH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 204, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 207, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 205, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 206, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "AL") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 12, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 203, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 201, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 202, words[k + 2]);
                    }
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 2 && tail == 0) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 10, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 0 && tail == 2) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 8, rtn_symbol_bcd(words[k + 2]), rtn_sl_loc(words[k + 1]), 0);
                    continue;
                }
            }
            if (strcmp(words[k + 0], "INC") == 0) {
                if (is_r_OR_num(words[k + 1]) == 1) {

                    if (strcmp(words[k + 1], "AX") == 0) {

                        printf("\n%04x\t%02x\n", ln, 64);
                    }
                    if (strcmp(words[k + 1], "BX") == 0) {

                        printf("\n%04x\t%02x\n", ln, 67);
                    }
                    if (strcmp(words[k + 1], "CX") == 0) {

                        printf("\n%04x\t%02x\n", ln, 65);
                    }
                    if (strcmp(words[k + 1], "DX") == 0) {

                        printf("\n%04x\t%02x\n", ln, 66);
                    }
                    if (strcmp(words[k + 1], "DI") == 0) {

                        printf("\n%04x\t%02x\n", ln, 71);
                    }
                    if (strcmp(words[k + 1], "SI") == 0) {

                        printf("\n%04x\t%02x\n", ln, 70);
                    }

                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 0) {
                    for (int i = 0; i < symbol_n; i++) {
                        if (strcmp(symbol[i], words[k + 1]) == 0) {
                            if (symbol_stat[i] == 2) {
                                printf("\n%04x\t%02x\t%02x\t%02x\t%02x", ln, 255, 6, rtn_sl_loc(words[k + 1]), 0);
                            }
                            else printf("\n%04x\t%02x\t%02x\t%02x\t%02x", ln, 254, 6, rtn_sl_loc(words[k + 1]), 0);
                        }
                        break;
                    }
                    continue;
                }

                if (is_r_OR_num(words[k + 1]) == 2) {
                    if (strcmp(words[k + 1], "AH") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 196);
                    }
                    if (strcmp(words[k + 1], "BH") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 199);
                    }
                    if (strcmp(words[k + 1], "CH") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 197);
                    }
                    if (strcmp(words[k + 1], "DH") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 198);
                    }
                    if (strcmp(words[k + 1], "AL") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 192);
                    }
                    if (strcmp(words[k + 1], "BL") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 195);
                    }
                    if (strcmp(words[k + 1], "CL") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 193);
                    }
                    if (strcmp(words[k + 1], "DL") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 194);
                    }

                    continue;
                }

            }

            if (strcmp(words[k + 0], "DEC") == 0) {
                if (is_r_OR_num(words[k + 1]) == 1) {

                    if (strcmp(words[k + 1], "AX") == 0) {

                        printf("\n%04x\t%02x\n", ln, 72);
                    }
                    if (strcmp(words[k + 1], "BX") == 0) {

                        printf("\n%04x\t%02x\n", ln, 75);
                    }
                    if (strcmp(words[k + 1], "CX") == 0) {

                        printf("\n%04x\t%02x\n", ln, 73);
                    }
                    if (strcmp(words[k + 1], "DX") == 0) {

                        printf("\n%04x\t%02x\n", ln, 74);
                    }
                    if (strcmp(words[k + 1], "DI") == 0) {

                        printf("\n%04x\t%02x\n", ln, 79);
                    }
                    if (strcmp(words[k + 1], "SI") == 0) {

                        printf("\n%04x\t%02x\n", ln, 78);
                    }
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 0) {

                    for (int i = 0; i < symbol_n; i++) {
                        if (strcmp(symbol[i], words[k + 1]) == 0) {
                            if (symbol_stat[i] == 2) {
                                printf("\n%04x\t%02x\t%02x\t%02x\t%02x", ln, 255, 14, rtn_sl_loc(words[k + 1]), 0);
                            }
                            else printf("\n%04x\t%02x\t%02x\t%02x\t%02x", ln, 254, 14, rtn_sl_loc(words[k + 1]), 0);
                            break;
                        }
                    }

                    continue;
                }

                if (is_r_OR_num(words[k + 1]) == 2) {
                    if (strcmp(words[k + 1], "AH") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 204);
                    }
                    if (strcmp(words[k + 1], "BH") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 207);
                    }
                    if (strcmp(words[k + 1], "CH") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 205);
                    }
                    if (strcmp(words[k + 1], "DH") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 206);
                    }
                    if (strcmp(words[k + 1], "AL") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 200);
                    }
                    if (strcmp(words[k + 1], "BL") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 203);
                    }
                    if (strcmp(words[k + 1], "CL") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 201);
                    }
                    if (strcmp(words[k + 1], "DL") == 0) {

                        printf("\n%04x\t%02x\t%02x\n", ln, 254, 202);
                    }
                    continue;
                }

            }

            if (strcmp(words[k + 0], "CMP") == 0) {
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 1) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 59, 192 + (8 * rtn_r_wd(words[k + 1])) + rtn_r_wd(words[k + 2]));
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 3) {
                    if (strcmp(words[k + 1], "AX") == 0) {
                        printf("\n%04x\t%02x\t%02s\t%02x\n", ln, 61, words[k + 2], 0);

                    }
                    if (strcmp(words[k + 1], "BX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 251, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 249, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DX") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 250, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DI") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 255, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "SI") == 0) {
                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 131, 254, words[k + 2]);
                    }
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 1 && tail == 0) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 59, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                    continue;
                }


                if (is_r_OR_num(words[k + 1]) == 2 && tail == 2) {
                    printf("\n%04x\t%02x\t%02x\n", ln, 58, 192 + (8 * rtn_r_bt(words[k + 1])) + rtn_r_bt(words[k + 2]));
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 2 && tail == 3) {
                    if (strcmp(words[k + 1], "AH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 252, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 255, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 253, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DH") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 254, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "AL") == 0) {

                        printf("\n%04x\t%02x\t%02s\n", ln, 60, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "BL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 251, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "CL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 249, words[k + 2]);
                    }
                    if (strcmp(words[k + 1], "DL") == 0) {

                        printf("\n%04x\t%02x\t%02x\t%02s\n", ln, 128, 250, words[k + 2]);
                    }
                    continue;
                }
                if (is_r_OR_num(words[k + 1]) == 2 && tail == 0) {
                    printf("\n%04x\t%02x\t%02x\t%02x\t%02x\n", ln, 58, rtn_symbol_bcd(words[k + 1]), rtn_sl_loc(words[k + 2]), 0);
                    continue;
                }
            }
            if (strcmp(words[k + 0], "JMP") == 0) {
                printf("\n%04x\t%02x\t%02x\n", ln, 235, rtn_sl_loc(words[k + 1]));
                continue;
            }
            if (strcmp(words[k + 0], "JA") == 0) {
                printf("\n%04x\t%02x\t%02x\n", ln, 119, rtn_sl_loc(words[k + 1]));
                continue;
            }
            if (strcmp(words[k + 0], "JE") == 0) {
                printf("\n%04x\t%02x\t%02x\n", ln, 116, rtn_sl_loc(words[k + 1]));
                continue;
            }
            if (strcmp(words[k + 0], "JB") == 0) {
                printf("\n%04x\t%02x\t%02x\n", ln, 114, rtn_sl_loc(words[k + 1]));
                continue;
            }
        }
        line++;
    }



}

int main() {
    first_read();
    read();
    return 0;
}
