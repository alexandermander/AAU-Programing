#include <stdio.h>
#include <math.h>
#include <stdlib.h> //til NULL
#include <time.h> //til terningerne

#define NUM_ROUNDS 16

typedef struct{
    int scores[NUM_ROUNDS];
    int BONUS;
    int sum;

} score_h;

//funktionsprototyper:
int roll_dice(void);
int roll_multiple_dies(int N, int array[][N]);
int singles(int N, const int arrays[][N], int number_to_find);
int sort_pair(int *arrays, int N, int numbers_to_find);
int pairs(int *arrays, int N, int pairs_to_find);
void sort_identical_array(int *arrays, char *identical, int N);
int identical(int *arrays, int N, int identical_numbers_find);
int small_straight(int *arrays, int N);
int large_straight(int *arrays, int N);
void calculate_score(int N, int array[][N], score_h *);
void calculate_final_sccore(score_h *score);
void display_score_board(int N, int array[][N], score_h *score);

#define DICE_MAX_EYES 6

int roll_dice(void){
    return (rand() % DICE_MAX_EYES) + 1;
}

int main(void) {
    int N;


//sÃ¦tter alle members til 0:
    score_h score;
    score.BONUS = 0;
    score.sum = 0;

    for(int i = 0; i < NUM_ROUNDS; i++){
        score.scores[i] = 0;

    }

    srand(time(NULL));  //SÃ¥ning af den tilfÃ¦ldige talgenerator.

    do {
        printf("How many dice?");
        scanf("%d", &N);

        if (N <= 4){
            printf("Error, the amount of dice have to be equal or greater than 5.\n Try again\n ");
        } else {
            printf("Yatzy with %d dice:\n", N);
        }

    } while (N < 4);

    // Definer array stÃ¸rrelse og sÃ¦t startvÃ¦rdi til 0 for score:
    int array[15][N];
    int scoresss[15] = {0};


    /// ////////////////////////////////////////////////////////////////////////FUNKTIONSKALD HER/////////////////////////////////////////////////////////////////////////////////////
    roll_multiple_dies(N, array); // usynlig addresseoperator!!
    for (int i = 0; i < NUM_ROUNDS; ++i) {
        for (int j = 0; j < N; ++j) {
            // printf("%d ", array[i][j]);
        }
        //printf("\n");
    }
    calculate_score(N, array, (score_h *) score.scores);
    //display_score_board(N, array, score);

    return 0;
}


int roll_multiple_dies(int N, int array[][N]){

    // Todimensionelt array med runder og terningekast N
    for(int i = 0; i < NUM_ROUNDS; i++){

        for(int y = 0; y < N; y++){
            array[i][y] = roll_dice();
        }
    }

    return 0;
}


void calculate_score(int N, int array[][N], score_h *score){
    const char rounds_yatzy[][NUM_ROUNDS] = {"1-ere", "2-ere", "3-ere", "4-ere", "5-ere", "6-ere", "Bonus", "Et par", "To par", "Tre ens", "Fire ens", "Lille", "Stor", "Fuld hus", "Chance", "YATZY", "TOTAl"};

    for (int i = 0; i < NUM_ROUNDS; i++){
        printf("%s    \t |  ", rounds_yatzy[i]);


        if(i < 6) {
            score->scores[i] =  singles( N, array, 1+i);
            //score->scores[i] = singles(array[i], N, 1+i);
        }

        if ( i > 6 && i < 9) {
            //score->scores[i] = pairs(array[i], N, i-6);
        }

        if ( i > 8 && i < 11) {
            // score->scores[i] = identical(array[i], N, i-6);

        }

        if (i > 10 && i < 14) {
            //score->scores[i] = small_straight(array[i], N);


        }

        if (i == NUM_ROUNDS) {

        }

        calculate_final_sccore(score);
        printf("\n");
    }
}


void calculate_final_sccore(score_h *score){


    int temp_sum = 0;
    // Beregn summen af de fÃ¸rste 6 rÃ¦kker.
    for(int i = 0; i < 6; i++) {
        temp_sum += score->scores[i];
    }

    if(temp_sum >= 63) {
        score->BONUS = 50;
    }
    // Beregn summen af alle rÃ¦kkerne.
    temp_sum = 0;
    for(int i = 0; i < 15; i++) {
        temp_sum += score->scores[i];
    }

    temp_sum += score->BONUS;
    score->sum = temp_sum;

}


int singles(int N, const int arrays[][N], int number_to_find) {
    int count_1 = 0;
    for(int i = 0; i < N; i++) {
        if (arrays[number_to_find - 1][i] == number_to_find) {
            count_1++;
            if (count_1 == 5) {
                break;
            }
        }
    }
    printf("%d ", count_1 * number_to_find);
    return count_1 * number_to_find;
}


// sortere efter par for alle nummere 1-6.
int sort_pair(int *arrays, int N, int numbers_to_find) {
    int count_2 = 0;

    for(int i = 0; i < N; i++) {
        if (arrays[i] == numbers_to_find) {
            for(int y = i+1; y < N; y++) {
                if (arrays[y] == numbers_to_find) {
                    count_2++;
                    i=y+1;
                    break;

                }
            }
        }
    }

    return count_2;

}
// Putter de sortede par ind i pairs[i].
int pairs(int *arrays, int N, int pairs_to_find) {
    int sum_2 = 0, pairs_found = 0;
    char pairs[6] = {0};

    for(int i = 0; i < 6; i++){
        pairs[i] = sort_pair(arrays, N, i+1);
    }

    // Infinte loop der stopper nÃ¥r man breaker tjekker for par: et par, to par.
    while(1) {
        for(int i = 5; i > 0; i--) {
            if (pairs[i] > 0) {
                sum_2 += ((i+1) * 2) * pairs[i];
                pairs_found += pairs[i];
            }
        }
        // Breaker nÃ¥r den har fundet parne.
        if(pairs_found == pairs_to_find) {
            break;
        }
    }

    return sum_2;

}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!FORSTÃ…!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void sort_identical_array(int *arrays, char *identical, int N) {

    for(int i = 0; i < N; i++) {
        int number = arrays[i];
        identical[number]++;

    }

}
int identical(int *arrays, int N, int identical_number_find) {
    char identical[15] = {0};
    int sum_3 = 0;

    sort_identical_array(arrays, identical, N);

    for(int i = 5; i > 0; i--) {
        if(identical[i] >= identical_number_find) {
            sum_3 += (identical_number_find * identical[i]);
            break;

        }
    }
    return sum_3;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int sort_straight(int *arrays, int N, int number_to_find) {
    int sum_4 = 0;

    for(int i = 0; i < N; i++) {
        if (arrays[i] == number_to_find)
            sum_4 += arrays[i];
        break;

    }
    return sum_4;
}


int small_straight(int *arrays, int N) { //runde 11
    int combination_score[5];
    for (int i =0; i < 6; ++i){
        combination_score[i] = sort_straight (arrays, N, i+1);
    }

    if (combination_score[0] && combination_score[1] && combination_score[2] && combination_score[3] && combination_score[4]){
        return 15;
    } else {
        return 0;
    }

}


int large_straight(int *arrays, int N) {
    int combination_score[5];
    for (int i =0; i < 6; ++i){
        combination_score[i] = sort_straight(arrays, N, i+2);
    }

    if (combination_score[0] && combination_score[1] && combination_score[2] && combination_score[3] && combination_score[4]){
        return 20;
    } else {
        return 0;
    }

}

//Chance: Any combination of dice. Score: Sum of all the dice.


int Yatzy(int *arrays, int N){

    //Yatzy: All five dice with the same number. Score: 50 points.

    return 0;
}


void display_score_board(int N, int array[][N], score_h *score) {


    const char *rounds_yatzy[NUM_ROUNDS] = {"1-ere", "2-ere", "3-ere", "4-ere", "5-ere", "6-ere", "Bonus", "Et par", "To par", "Tre ens", "Fire ens", "Lille", "Stor", "Fuld hus", "Chance", "YATZY", "TOTAl"};

    for(int i = 0; i < NUM_ROUNDS; i++) {
        printf("%s\t|", rounds_yatzy[i]);

        for(int y = 0; y < N; y++) {
            printf("%d", array[i][y]);



            ///print ogsÃ¥ scoren////

        }
    }
}