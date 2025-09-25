#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_COUNTRY_NAME 100
#define MAX_COLOR_NAME 50
#define MAX_PLAYERS 10

typedef struct {
    char country[MAX_COUNTRY_NAME];
    char color[MAX_COLOR_NAME];
    int number;
} Player;

int PlayersNumber = 2;
Player db_reg[MAX_PLAYERS];
int db_count = 0;

void to_lowercase(char *str) {
    for (; *str; ++str) *str = tolower(*str);
}

void textTag_reg(const char *text, char *buffer) {
    sprintf(buffer, "--- %s ---", text);
}

void textTag_map(char *buffer) {
    sprintf(buffer, "\n==============================\n WORLD MAP - CURRENT SITUATION \n==============================");
}

void textTag_country(const char *text, char *buffer) {
    sprintf(buffer, "- %s", text);
}

void reg_init() {
    char buffer[256];
    printf("\n REGISTER %d COUNTRY FOR GAME WORLD: \n \n", PlayersNumber);
    printf("----------------------------------------\n");
    for (int count = 0; count < PlayersNumber; count++) {
        textTag_reg("Register the country", buffer);
        printf("\n");
        char reg_text[50];
        sprintf(reg_text, "Register the %d country", count + 1);
        textTag_reg(reg_text, buffer);
        printf("%s\n", buffer);

        char new_reg_country[MAX_COUNTRY_NAME];
        char new_reg_trooperColor[MAX_COLOR_NAME];
        int new_reg_numberTrooper;

        printf("Country name: ");
        if (fgets(new_reg_country, sizeof(new_reg_country), stdin) == NULL) exit(1);
        new_reg_country[strcspn(new_reg_country, "\n")] = 0; // remove newline
        to_lowercase(new_reg_country);

        printf("Trooper color: ");
        if (fgets(new_reg_trooperColor, sizeof(new_reg_trooperColor), stdin) == NULL) exit(1);
        new_reg_trooperColor[strcspn(new_reg_trooperColor, "\n")] = 0;
        to_lowercase(new_reg_trooperColor);

        printf("Trooper number: ");
        if (scanf("%d", &new_reg_numberTrooper) != 1) exit(1);
        while(getchar() != '\n'); // clear input buffer

        strcpy(db_reg[db_count].country, new_reg_country);
        strcpy(db_reg[db_count].color, new_reg_trooperColor);
        db_reg[db_count].number = new_reg_numberTrooper;
        db_count++;
    }
}

void show_allPlayers() {
    char buffer[256];
    for (int count = 0; count < PlayersNumber; count++) {
        printf("\n COUNTRY %d:\n", count + 1);
        char temp[150];

        sprintf(temp, "Name: %s", db_reg[count].country);
        textTag_country(temp, buffer);
        printf("%s\n", buffer);

        sprintf(temp, "Dominated color: %s trooper", db_reg[count].color);
        textTag_country(temp, buffer);
        printf("%s\n", buffer);

        sprintf(temp, "Troopers: %d", db_reg[count].number);
        textTag_country(temp, buffer);
        printf("%s\n", buffer);
    }
}

int battle_result(int attackerPos, int defenderPos);

void wl_action(int compAtk, int compDf, int diceA, int diceD) {
    if (diceA < diceD) {
        printf("%s color won the attack from %s over of %s territory\n",
               db_reg[compDf - 1].color, db_reg[compAtk - 1].color, db_reg[compDf - 1].country);
        db_reg[compAtk - 1].number = db_reg[compAtk - 1].number - 1;
    }
    else if (diceD < diceA) {
        printf("The color %s dominated %s\n", db_reg[compAtk - 1].color, db_reg[compDf - 1].country);
        strcpy(db_reg[compDf - 1].color, db_reg[compAtk - 1].color);
    }
    else {
        printf("drawn!\n");
    }
}

int atack_phase() {
    char buffer[256];
    textTag_reg("ATACK PHASE", buffer);
    printf("\n%s\n", buffer);

    while (1) {
        int atk;
        printf("Choose the country to ATACK (press 0 to exit): ");
        if (scanf("%d", &atk) != 1) exit(1);
        while(getchar() != '\n');

        if (atk == 0) {
            printf("\n EXIT ATACK PHASE!\n");
            return 0;
        }

        if (atk >= 1 && atk <= PlayersNumber) {
            while (1) {
                int df;
                printf("Choose the country to DEFESE: ");
                if (scanf("%d", &df) != 1) exit(1);
                while(getchar() != '\n');

                if (df > 0 && df <= PlayersNumber && df != atk &&
                    strcmp(db_reg[df - 1].color, db_reg[atk - 1].color) != 0) {
                    battle_result(atk, df);
                    return 0;
                }
                printf("CHOOSE INVALID, TRY AGAIN!\n");
            }
        }
        printf("CHOOSE INVALID, TRY AGAIN!\n");
    }
}

int battle_result(int attackerPos, int defenderPos) {
    char buffer[256];
    textTag_reg("BATTLE RESULT", buffer);
    printf("\n%s\n", buffer);

    int diceAtk = (rand() % 6) + 1;
    int diceDef = (rand() % 6) + 1;

    printf("Country attacker %s roll %d\n", db_reg[attackerPos - 1].country, diceAtk);
    printf("Country defender %s roll %d\n", db_reg[defenderPos - 1].country, diceDef);

    wl_action(attackerPos, defenderPos, diceAtk, diceDef);
    return 0;
}

void winner_condition(int max) {
    int return_condition = 1;
    int c = max;
    while (c > 1) {
        if (strcmp(db_reg[c - 2].color, db_reg[c - 1].color) == 0) {
            return_condition = 1;
        } else {
            return_condition = 0;
            break;
        }
        c--;
    }
    if (return_condition == 1) {
        printf("%s Ganhou!\n", db_reg[0].color);
        exit(0);
    }
}

int main() {
    srand((unsigned int)time(NULL));

    reg_init();

    char buffer[256];
    textTag_map(buffer);
    printf("%s\n", buffer);

    int loop_confirm = 1;
    while (loop_confirm) {
        printf("State: \n");
        show_allPlayers();
        loop_confirm = atack_phase();
        winner_condition(PlayersNumber);

        printf("Press ENTER to continue... (press 0 to exit)");
        char ver[10];
        if (fgets(ver, sizeof(ver), stdin) == NULL) break;
        if (ver[0] == '0') break;
    }

    return 0;
}
