#include<stdlib.h>
#include<string.h>


int main() {
    char cmd[10];
    char somevalue;
    strcpy(cmd,"dir");
    system(cmd);
    return 0;
}