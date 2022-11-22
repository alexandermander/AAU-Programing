//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIE_MAX_EYES 6
//#define N 25
#define YATZIGAMELENTH 15

void roll_multiple_dies(int *array, int N);
int alike(const int *dice, int *sum, int size, int N);
int pair_one(const int *dice, int *sum, int ishoue, int N);
int pair_two(const int *dice, int *sum, int N);
int three_alike(const int *dice, int *sum, int is_four, int N);
int small_large(const int *dice, int *sum, int stor, int N);
int yatzy(int *dice, int *sum, int N);
int house(const int *dice, int *sum, int N);
int chance(int *dice, int *sum, int N);

int main(void) {
    int sum_arry[YATZIGAMELENTH];
    char names[][17] = {"1-ere","2-ere","3-ere","4-ere","5-ere","6-ere","Et par","To par","Tre ens","Fire ens","Lille","Stor","Fuld hus","Chance","YATZY","TOTAL"};
    int N;
    do {
        printf("Yatzy with how many dies (a number less than 5 terminates) ");
        scanf(" %d", &N);
        printf("%d\n", N);


    int dice_array[N];


    int total_sum = 0;
    srand(time(NULL));  // Seeding the random number generator.
    for (int i = 0; i < YATZIGAMELENTH; ++i) {
        sum_arry[i] = 0;

        printf("%s", names[i]);
        roll_multiple_dies(dice_array, N);

        if (i<6) {
            printf(" -- %d", alike(dice_array, &sum_arry[i], i, N));
        }
        switch (i) {
            case 6:
                printf(" -- %d", pair_one(dice_array, &sum_arry[i], 0, N));
                break;
            case 7:
                printf(" -- %d", pair_two(dice_array, &sum_arry[i], N));
                break;
            case 8:
                printf(" -- %d", three_alike(dice_array, &sum_arry[i], 0, N));
                break;
            case 9:
                printf(" -- %d", three_alike(dice_array, &sum_arry[i], 1, N));
                break;
            case 10:
                printf(" -- %d", small_large(dice_array, &sum_arry[i], 0, N));
                break;
            case 11:
                printf(" -- %d", small_large(dice_array, &sum_arry[i], 1, N));
                break;
            case 12:
                printf(" -- %d", house(dice_array, &sum_arry[i], N));
                break;
            case 13:
                printf(" -- %d", chance(dice_array, &sum_arry[i], N));
                break;
            case 14:
                printf(" -- %d\n", yatzy(dice_array, &sum_arry[i], N));
                printf("\nScore board:");
                for (int j = 0; j < YATZIGAMELENTH; ++j) {
                    total_sum = total_sum + sum_arry[j];
                    if (j == 6 && total_sum > 63){
                        printf("\nBONUS : 50\n");
                        total_sum = total_sum + 50;
                    } else if(j == 6 && total_sum < 63)
                    {
                        printf("\nBONUS : 0\n");
                    }
                    printf("\n%s : %d ", names[j], sum_arry[j]);
                }
                printf("\nTOTAL : %d", total_sum);
                break;
        }
        printf("\n");


    }
    } while (N >= 5);
    return 0;
}

//her finder vi alle 1'ere til 6'ere
int alike(const int *dice, int *sum, int size, int N){
    int couter = 5;
    for (int i = 0; i < N; ++i) {
        if(dice[i] == size + 1 && couter != 0){
            couter--;
            *sum += size + 1;
        }
    }
    return *sum;
}

//her laver vi et int array som simulere et terning kast
void roll_multiple_dies(int *array, int N){
    for (int i = 0; i < N; ++i) {
        array[i] = (rand() % DIE_MAX_EYES) + 1;
        printf(" %d", array[i]);
    }
}
//denne funktion finder et par og er med til at finde fuld hus 
int pair_one(const int *dice, int *sum, int ishoue,int N)
{
    int myresult = 0;
    for (int j = 0; j < N; ++j)
    {
        for (int k = 0; k < N; ++k)
        {
            if (j != k && dice[j] == dice[k] && myresult < (dice[j] + dice[k]) && ishoue != dice[j] ){
                myresult = dice[j] + dice[k];
                *sum = myresult;
            }
        }
    }
    return *sum;
}
//her finder vi 2 par
int pair_two(const int *dice, int *sum, int N)
{
    int first_pair = pair_one(dice, sum, 0, N)/2;
    *sum = 0;
    if(first_pair == 0)return 0;
    int myresult = 0;
    for (int j = 0; j < N; ++j)
    {
        for (int k = 0; k < N; ++k)
        {
            if (j != k && dice[j] == dice[k] && myresult < (dice[j] + dice[k]) && first_pair != dice[k] ){
                myresult = dice[j] + dice[k];
                *sum = myresult + first_pair*2;
            }
        }
    }
    return *sum;
}

//denne funktion finder tre go fire ens
int three_alike(const int *dice, int *sum, int is_four, int N)
{
    int current_result = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if(is_four == 0 && i!=j && i!=k && j!=k && dice[i] == dice[j] && dice[i] == dice[k] && current_result < (dice[i] * 3) )
                {
                    current_result = dice[i] * 3;
                }
                for (int l = 0; l < N; ++l) {
                    if(is_four == 1 && i!=j && i!=k && i!=l && j!=k && j!=l && k!=l && dice[i] == dice[j] && dice[i] == dice[k] && dice[i] == dice[l] && current_result < (dice[i] * 4) )
                    {
                        current_result = dice[i] * 4;
                    }
                }
            }
        }
    }
    *sum = current_result;return current_result;
}
//denne funktion finder lille og stor
int small_large(const int *dice, int *sum, int stor, int N){
    int current_result = 0;
    for (int i = 0; i < N; ++i)
    {
        if (dice[i] == stor + 1)
            for (int j = 0; j < N; ++j)
            {
                if (dice[j] == stor + 2)
                    for (int k = 0; k < N; ++k)
                    {
                        if(dice[k] == stor + 3)
                            for (int l = 0; l < N; ++l)
                            {
                                if (dice[l] ==  stor + 4)
                                    for (int m = 0; m < N; ++m)
                                    {
                                        if (dice[m] == stor + 5)current_result = 15;
                                        if (stor == 1)current_result = 20;
                                    }
                            }
                    }
            }
    }
    *sum = current_result;
    return current_result;
}

//denne funktion finder fuld hus den bruger 2 funktioner
int house(const int *dice, int *sum, int N){
    int threePair = three_alike(dice, sum, 0, N) / 3;
    int onePair = pair_one(dice, sum, threePair, N);
    *sum = onePair + (threePair * 3);
    return *sum;
}

//denne funtion bruger vi når vi skal qsort
int compaire (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

//denne finder chance
int chance(int *dice, int *sum, int N){
    qsort(dice, N, sizeof(int), compaire);
    for (int i  = N - 1 ; i > N - 6; i--) {
        if (i<0)break;
        *sum  = *sum  + dice[i];
    }
    return *sum;
}
//her finder vi yatzy ved brug af qsort
int yatzy(int *dice, int *sum, int N) {
    int counter = 5;
    int result = 0;
    qsort(dice, N, sizeof(int), compaire);
    for (int i = 0; i < N ; ++i){
        for (int j = 0; j < N; ++j)
        {
            if ( i!=j && dice[i] == dice[j])
            {
                counter--;
                if (counter == 0){
                    result = 50;
                }
            }
        }
        counter = 5;
    }
    *sum = result;
    return result;
}