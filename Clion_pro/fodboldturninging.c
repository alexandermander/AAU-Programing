#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENTHOFTXT 102
#define HOLD 12

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


int cmpfunc (const void * a, const void * b) {

    soccer_team *valueOne = (soccer_team *)a;
    soccer_team *valueTow = (soccer_team *)b;

    return ( valueTow->points - valueOne->points );
}

void findTeamNams(soccer_team *teams, MATCH *matches);
void readFileInStruckMatch(FILE *myfile, MATCH *matches);
void calculatornationOfScore(char team[4], int own_score, int enemy_score, soccer_team *all_teams);
int main(void){
    MATCH matches[102];
    FILE *file = fopen("kampe-2022-2023.txt", "r");
    if (file == NULL){
        exit(EXIT_FAILURE);
    }

    readFileInStruckMatch(file, matches);
    fclose(file);

    soccer_team teams[HOLD] = {0};

    findTeamNams(teams, matches);


    for (int j = 0; j < LENTHOFTXT; ++j) {
        calculatornationOfScore(matches[j].team_one, matches[j].soceone, matches[j].socetwo, teams);
        calculatornationOfScore(matches[j].team_two, matches[j].socetwo, matches[j].soceone, teams);
    }

    qsort(teams, HOLD, sizeof(soccer_team), cmpfunc);


    printf("Hold navnet, Hold points,  hold mål  -  mål scoret på\n");

    for (int j = 0; j < 12; ++j) {
        if (teams[j].teamName[2] == '\000' || teams[j].points < 10){
            printf(" ");
        }
        printf("   %s:         %d:               %d - %d",teams[j].teamName, teams[j].points, teams[j].goals, teams[j].goal_aginet);
        printf("\n");
    }
}


void readFileInStruckMatch(FILE *myfile, MATCH *matches){
    int i = 0;
    while (!feof(myfile)){
        fscanf(myfile, "%s %s %lf %s - %s %d - %d %d",
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

}

void findTeamNams(soccer_team *teams, MATCH *matches){


    for (int j = 0; j < LENTHOFTXT; ++j) {
        for (int k =0; k < 12; ++k) {
            if (strcmp(matches[j].team_one, teams[k].teamName) == 0){
                break;
            }else if (strcmp(matches[j].team_one, teams[k].teamName) != 0
                      && teams[k].teamName[0] == '\000')
            {
                strncpy(teams[k].teamName, matches[j].team_one, 4);
                break;
            }
        }
    }

}


void calculatornationOfScore(char team[4], int own_score, int enemy_score, soccer_team *all_teams){
    int i = 0;
    for (i; i < 12; ++i) {
        if (strcmp(team, all_teams[i].teamName) == 0){
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
