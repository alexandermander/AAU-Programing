// Alexander Sumczynski, CCT


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENTHOFTXT 102
#define HOLD 12
//her definere vi vores MATCH struct
typedef struct{
    char weekday[4];
    char date[6];
    double time;
    char team_one[4];
    char team_two[4];
    int soceone,socetwo,audinc;
}MATCH;

//her definere vi vores soccer_team struct
typedef struct{
    char teamName[4];
    int points;
    int goals;
    int goal_aginet;
}soccer_team;

//compair funkton bliver brugt med qsort for at sortere arrayet team
int cmpfunc (const void * a, const void * b) {

    soccer_team *valueOne = (soccer_team *)a;
    soccer_team *valueTow = (soccer_team *)b;

    return ( valueTow->points - valueOne->points );
}

//funktions prototyper
void findTeamNames(soccer_team *teams, MATCH *matches);
void readFileInStruckMatch(FILE *myfile, MATCH *matches);
void calculatornationOfScore(char team[4], int own_score, int enemy_score, soccer_team *all_teams);


int main(void){
    //matches bliver defineret til at indbære LENTHOFTXT pladser for hver match i txt filen som et aarry
    MATCH matches[LENTHOFTXT];
    //file opner filien kampe-2022-2023.txt i read mode
    FILE *file = fopen("kampe-2022-2023.txt", "r");

    //hvis fillen er NULL luk programet
    if (file == NULL){
        exit(EXIT_FAILURE);
    }
    //her kalder vi funktionen readFileInStruckMatch og pointer til file og matches
    readFileInStruckMatch(file, matches);
    fclose(file);

    //soccer_team definere til at inbære HOLD pladser(12), hver element i arrayet er lig '0'
    soccer_team teams[HOLD] = {0};
    /*funktionen findTeamNames bruger vi til at finde alle de hold som er med i txt-filen
       dette er i stedet for at bruge associativt array*/
    findTeamNames(teams, matches);

    //denne løgge går igennem hele matches arrayet
    for (int j = 0; j < LENTHOFTXT; ++j) {
        //funktionen calculatornationOfScore regner ud og lægger de rette værdier på de forskellige teams
        calculatornationOfScore(matches[j].team_one, matches[j].soceone, matches[j].socetwo, teams);
        calculatornationOfScore(matches[j].team_two, matches[j].socetwo, matches[j].soceone, teams);
    }
    //qsort sotere vores hold efter højeste point
    qsort(teams, HOLD, sizeof(soccer_team), cmpfunc);

    //her printer vi resultaterne efter qsort
    printf("Hold navnet, Hold points,  hold mål  -  mål mod hold\n");

    for (int j = 0; j < 12; ++j) {
        if (teams[j].teamName[2] == '\000' || teams[j].points < 10){
            printf(" ");
        }
        printf("   %s:          %d:              %d - %d",teams[j].teamName, teams[j].points, teams[j].goals, teams[j].goal_aginet);
        printf("\n");
    }

    printf("Ergo %s har flest point: %d", teams[0].teamName, teams[0].points);


    return EXIT_SUCCESS;
}

//denne funktion læser hver linje in txt filen "kampe-2022-2023.txt" og sætter det ind i structen matches
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

void findTeamNames(soccer_team *teams, MATCH *matches){

    //her går vi igennem hver linje i vores struct matches
    for (int j = 0; j < LENTHOFTXT; ++j) {
        //dette for løkke tjekker om der er plads til et team
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
    for (i; i < HOLD; ++i) {
        //hvis det nuværende team navn er lig all_teams så break
        if (strcmp(team, all_teams[i].teamName) == 0){
            break;
        }
    }
    //her regner vi de forskllige points og score ud
    int point = own_score - enemy_score;
    if (point == 0){
        all_teams[i].points += 1;
    } else if(point > 0){
        all_teams[i].points += 3;
    }
    all_teams[i].goals += own_score;
    all_teams[i].goal_aginet += enemy_score;
}
