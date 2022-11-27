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
    int points;
    int goals;
    int goal_aginet;
}soccer_team;

void calcliotin(char team[4], int own_score, int enemy_score, soccer_team *all_teams);

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


    for (int j = 0; j < LENTHOFTXT; ++j) {
        for (int k =0; k < 12; ++k) {
            if (strcmp(matches[j].team_one, teams[k].teamName) != 0
            && teams[k].teamName[0] == '\000'){
                strncpy(teams[k].teamName, matches[j].team_one, 4);
                break;
            }else if (strcmp(matches[j].team_one, teams[k].teamName) == 0){
                break;
            }
        }
    }


    for (int j = 0; j < LENTHOFTXT; ++j) {
       calcliotin(matches[j].team_one, matches[j].soceone, matches[j].socetwo, teams);
       calcliotin(matches[j].team_two, matches[j].socetwo, matches[j].soceone, teams);
    }

    for (int j = 0; j < 12; ++j) {
        printf("Hold navnet: %s, Hold points: %d, hold mål scoret: %d, mål der er scoret på dette hold %d", teams[j].teamName, teams[j].points, teams[j].goals, teams[j].goal_aginet);
        printf("\n");
    }
}

void calcliotin(char team[4], int own_score, int enemy_score, soccer_team *all_teams){
    int i = 0;
    for (i; i < 12; ++i) {
        if (strcmp(team, all_teams[i].teamName) == 0){
            //printf("yoooo det virker %s - %s\n", team, all_teams[i].teamName);
            break;
        }
    }
    int point = own_score - enemy_score;
    if (point == 0){
        all_teams[i].points += 1;
    } else if(point > 0){
        all_teams[i].points += 3;
    }
    all_teams[i].goals += own_score;
    all_teams[i].goal_aginet += enemy_score;
}
