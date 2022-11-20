#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIE_MAX_EYES 6
#define N 15
#define YATZIGAMELENTH 15

void roll_multiple_dies(int *array);
int alike(const int *dice, int *sum, int size);
int pair_one(const int *dice, int *sum, int ishoue);
int pair_two(const int *dice, int *sum);
int three_alike(const int *dice, int *sum, int is_four);
int small_lange(const int *dice, int *sum, int stor);
int yatzy(const int *dice, int *sum);
int house(const int *dice, int *sum);
int chance(int *dice, int *sum);

int main(void) {
    int dice_array[N];
    int sum_arry[YATZIGAMELENTH];
    char names[][17] = {"1-ere","2-ere","3-ere","4-ere","5-ere","6-ere","Et par","To par","Tre ens","Fire ens","Lille","Stor","Fuld hus","Chance","YATZY","TOTAL"};


    //roll_multiple_dies(dice_array);
    srand(time(NULL));  // Seeding the random number generator.
    // Do this only once!
    for (int i = 0; i < YATZIGAMELENTH; ++i) {
        sum_arry[i] = 0;
        printf("%s", names[i]);
        roll_multiple_dies(dice_array);
        if (i<6) {
            printf(" -- %d", alike(dice_array, &sum_arry[i], i));
        }
        if(i == 6) printf(" -- %d", pair_one(dice_array, &sum_arry[i], 0));
        if(i == 7) printf(" -- %d", pair_two(dice_array, &sum_arry[i]));
        if(i == 8) printf(" -- %d", three_alike(dice_array, &sum_arry[i], 0));
        if(i == 9) printf(" -- %d", three_alike(dice_array, &sum_arry[i], 1));
        if(i == 10) printf(" -- %d", small_lange(dice_array, &sum_arry[i], 0));
        if(i == 11) printf(" -- %d", small_lange(dice_array, &sum_arry[i], 1));
        if(i == 12) printf(" -- %d", house(dice_array, &sum_arry[i]));
        if(i == 13) printf(" -- %d", chance(dice_array, &sum_arry[i]));
        if(i == 14) printf(" -- %d", yatzy(dice_array, &sum_arry[i]));
        printf("\n");

    }

    return 0;
}

int alike(const int *dice, int *sum, int size){
    int couter = 5;
    for (int i = 0; i < N; ++i) {
        if(dice[i] == size + 1 && couter != 0){
            couter--;
            *sum += size + 1;
        }
    }
    return *sum;
}

void roll_multiple_dies(int *array){
    for (int i = 0; i < N; ++i) {
        array[i] = (rand() % DIE_MAX_EYES) + 1;
        printf(" %d", array[i]);
    }
}
int pair_one(const int *dice, int *sum, int ishoue)
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
int pair_two(const int *dice, int *sum)
{
    int first_pair = pair_one(dice, sum, 0)/2;
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


int three_alike(const int *dice, int *sum, int is_four)
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
    *sum = current_result;
    return current_result;
}
int small_lange(const int *dice, int *sum, int stor){
    int current_result = 0;
    for (int i = 0; i < N; ++i)
    {
        if (dice[i] == stor + 1)for (int j = 0; j < N; ++j)
            {
                if (dice[j] == stor + 2)for (int k = 0; k < N; ++k)
                    {
                        if(dice[k] == stor + 3)for (int l = 0; l < N; ++l)
                            {
                                if (dice[l] ==  stor + 4)for (int m = 0; m < N; ++m)
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
int house(const int *dice, int *sum){
    int threePair = three_alike(dice, sum, 0) / 3;
    int onePair = pair_one(dice, sum, threePair);
    *sum = onePair + (threePair * 3);
    return *sum;
}
int compaire (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}
int chance(int *dice, int *sum){
    qsort(dice, N, sizeof(int), compaire);
    for (int i  = N - 1; i > N - 6; i--) {
        *sum = *sum + dice[i];
    }
    return *sum;
}
int yatzy(const int *dice, int *sum) {
    int current_result = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0 + 1; j < N; ++j) {
            for (int k = 0 + 2; k < N; ++k) {
                for (int l = 0 + 3; l < N; ++l) {
                    for (int m = 0 + 4; m < N; ++m) {
                        //if (dice[i] == dice[j] && dice[i] == dice[k] && dice[i] == dice[l] && dice[i] == dice[m] )printf("xxxxx%d", dice[m]);
                    }
                }
            }
        }
    }
    *sum = current_result;
    return current_result;
}