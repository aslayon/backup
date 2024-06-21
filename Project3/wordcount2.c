#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void change(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int main() {
    
    int a = 0;
    int b = 2;
    change(&a, &b);
    printf("%d %d", a, b);
    return 0;
}
