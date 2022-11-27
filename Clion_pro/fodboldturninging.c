#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENTHOFTXT 102

typedef struct{
    char weekday[4];
    char date[6];
    double time;
    char team_one[4];
    char team_two[4];
    int soceone,socetwo,audinc;
}MATCH;

typedef struct{
    char teamName[4];
    int score_aginet[11];
}soccer_team;



int main(void){
    MATCH matches[102];
    FILE *fin = fopen("kampe-2022-2023.txt", "r");
    if (fin == NULL){
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (!feof(fin)){
        fscanf(fin, "%s %s %lf %s - %s %d - %d %d",
               matches[i].weekday,
               matches[i].date,
               &matches[i].time,
               matches[i].team_one,
               matches[i].team_two,
               &matches[i].soceone,
               &matches[i].socetwo,
               &matches[i].audinc);





        i++;
    }
    fclose(fin);
    soccer_team teams[12] = {0};



    int k = 0;
    for (int j = 0; j < LENTHOFTXT; ++j) {
        matches[j].team_one;
        for (k; k < 12; ++k) {
            if (matches[j].team_one != teams[k].teamName){
                strncpy(teams[k].teamName, matches[j].team_one, 4);
                break;
            }
        }
    }
    for (int j = 0; j < 12; ++j) {
        printf("%s", matches[j].team_one);
        printf("\n");
    }
    printf("det virerike");
    return 0;
}
