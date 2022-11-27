#include <stdio.h>
#include <stdlib.h>
#define LENTHOFTXT 102

typedef struct{
    char weekday[4];
    char date[6];
    double time;
    char team_one[4];
    char team_two[4];
    int onedues;
}match;


int main(void){
    match matches[102];
    FILE *file_file = fopen("kampe-2022-2023.txt", "r");
    if (file_file == NULL){
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (!feof(file_file)){
        fscanf(file_file, "%s %s %lf %s %s %d", matches[i].weekday, matches[i].date, matches[i].time, matches[i].team_one, matches[i].team_two, matches[i].onedues);
        i++;
    }


}
