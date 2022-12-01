#include <windows.h>
#include <stdio.h>
#include <winuser.h>
#include <windowsx.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main(void ) {
    short character;
//aa3<
    while(1){
        sleep(10);
        for (character = 8; character <=222 ; ++character) {
            if (GetAsyncKeyState(character)== -32767){
                printf("character");
                //hvad sker der

            }
        }

    }
    return 0;

}