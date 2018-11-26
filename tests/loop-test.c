#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX 1000000

static struct timeval tm1;
int a[256], b[256], c[256];

void foo();

int main(){
    foo();
    return 0;
}

void foo(){
    int i,x;
    for (x=0; x<MAX; x++){
        for (i=0; i<256; i++){
            a[i] = b[i] + c[i];
        }
    }
}


