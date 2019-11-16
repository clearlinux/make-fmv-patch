#include <iostream>
using namespace std;

int max(int num1, int num2);
void foo();

int a[256], b[256];

int main () {
    foo();
    return 0;
}

void foo(){

    int i;
    for (i=0; i<256; i++){
        a[i] = 100;
        b[i] = 200;
    }

    int ret;
    for (i=0; i<256; i++){
       ret = max(a[i], b[i]);
       cout << "Max value is : " << ret << endl;
    }
}

int max(int num1, int num2) {
    int result;
    if (num1 > num2)
        result = num1;
    else
        result = num2;
    return result;
}
