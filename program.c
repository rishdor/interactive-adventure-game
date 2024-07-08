#include <stdio.h>

typedef struct {
    char name[50];
    int hp;
    int xp;
    int partner;
    int weapon;
    int armor;
    int heal_potion;
    int attack_potion;
    int heal_spell;
} Player;

// Function prototypes for each chapter
void chapter1(Player *player);
void chapter2(Player *player);
void chapter3(Player *player);
void chapter4(Player *player);
void chapter5(Player *player);

int main() {
    return 0;
}

void start(){

    Player player;
    player.hp = 100;
    player.xp = 0;

    printf("Enter your name: ");
    fgets(player.name, 50, stdin);

    chapter1(&player);
    chapter2(&player);
    chapter3(&player);
    chapter4(&player);
    chapter5(&player);
}

void chapter1(Player *player) {
    
}

void chapter2(Player *player) {
    
}

void chapter3(Player *player) {
    
}

void chapter4(Player *player) {

}

void chapter5(Player *player) {

}
