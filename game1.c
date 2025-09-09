
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 10
#define MAX_COUNTRY_NAME 50
#define MAX_COLOR_NAME 20

typedef struct {
    char country[MAX_COUNTRY_NAME];
    char color[MAX_COLOR_NAME];
    int number;
} Player;

Player db_reg[MAX_PLAYERS];
int PlayersNumber = 2;

void textTag_reg(char *text, char *output) {
    sprintf(output, "--- %s ---", text);
}

void textTag_map(char *output) {
    sprintf(output, "\n%s\n WORLD MAP - CURRENT SITUATION \n%s", "==============================", "==============================");
}

void textTag_country(char *text, char *output) {
    sprintf(output, "- %s", text);
}

void reg_init() {
    char country[MAX_COUNTRY_NAME];
    char color[MAX_COLOR_NAME];
    int number;

    printf("\n REGISTER %d COUNTRY FOR GAME WORLD: \n\n", PlayersNumber);
    for (int count = 0; count < PlayersNumber; count++) {
        char tag[100];
        textTag_reg("Register the country", tag);
        printf("\n%s\n", tag);
        printf("Country name: ");
        scanf("%s", country);
        printf("Trooper color: ");
        scanf("%s", color);
        printf("Trooper number: ");
        scanf("%d", &number);
        
        strcpy(db_reg[count].country, country);
        strcpy(db_reg[count].color, color);
        db_reg[count].number = number;
    }
}

void show_allPlayers() {
    char tag[100];
    for (int count = 0; count < PlayersNumber; count++) {
        printf("\n COUNTRY %d:\n", count + 1);
        textTag_country(db_reg[count].country, tag);
        printf("%s\n", tag);
        textTag_country(db_reg[count].color, tag);
        printf("%s\n", tag);
        printf("Troopers: %d\n", db_reg[count].number);
    }
}

void battle_result(int atackerPos, int defenderPos) {
    char tag[100];
    printf("\n");
    textTag_reg("BATTLE RESULT", tag);
    printf("%s\n", tag);
    
    int diceAtk = rand() % 6 + 1;
    int diceDef = rand() % 6 + 1;
    
    printf("Country attacker %s roll %d\n", db_reg[atackerPos - 1].country, diceAtk);
    printf("Country defender %s roll %d\n", db_reg[defenderPos - 1].country, diceDef);
    
    if (diceAtk < diceDef) {
        printf("%s color won the attack from %s color over %s territory\n", db_reg[defenderPos - 1].color, db_reg[atackerPos - 1].color, db_reg[defenderPos - 1].country);
        db_reg[atackerPos - 1].number--;
    } else if (diceDef < diceAtk) {
        printf("The color %s dominated %s\n", db_reg[atackerPos - 1].color, db_reg[defenderPos - 1].country);
        strcpy(db_reg[defenderPos - 1].color, db_reg[atackerPos - 1].color);
    } else {
        printf("drawn!\n");
    }
}

int atack_phase() {
    char tag[100];
    printf("\n");
    textTag_reg("ATACK PHASE", tag);
    printf("%s\n", tag);
    
    while (1) {
        int atk;
        printf("Choose the country to ATACK (press 0 to exit): ");
        scanf("%d", &atk);
        if (atk == 0) {
            printf("\n EXIT ATACK PHASE!\n");
            return 0;
        }
        if (atk >= 1 && atk <= PlayersNumber) {
            while (1) {
                int df;
                printf("Choose the country to DEFESE: ");
                scanf("%d", &df);
                if (df > 0 && df <= PlayersNumber && df != atk && strcmp(db_reg[df - 1].color, db_reg[atk - 1].color) != 0) {
                    battle_result(atk, df);
                    return 0;
                }
                printf("CHOOSE INVALID, TRY AGAIN!\n");
            }
        }
        printf("CHOOSE INVALID, TRY AGAIN!\n");
    }
}

int main() {
    srand(time(NULL));
    reg_init();
    
    char map[200];
    textTag_map(map);
    printf("%s\n", map);
    
    show_allPlayers();
    
    while (1) {
        atack_phase();
        printf("Press ENTER to continue... (press 0 to exit)\n");
        getchar(); // To consume the newline character left by previous input
        if (getchar() == '0') break;
    }
    
    return 0;
}
