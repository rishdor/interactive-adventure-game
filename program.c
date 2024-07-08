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

// unction prototypes for each chapter
void start();
void chapter1(Player *player);
void chapter2(Player *player);
void chapter3(Player *player);
void chapter4(Player *player);
void chapter5(Player *player);

int main() {
    start();
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
    printf("Welcome to Pyroklas, a city under siege by rogue dragons. As the newest member of the Wing of Fire Squad, it's your job to help protect the city.\n");

    printf("You meet your new teammates, Lyla and Magnus. Lyla is a seasoned dragon hunter, smart and agile. Magnus is big and strong but a bit self-absorbed.\n");

    printf("Lyla turns to you and asks, 'So, %s, ever had a close encounter with a dragon before?'\n", player->name);

    printf("1: I arrived from Eflara where I was a member of the Order of the Flame.\n");
    printf("2: Actually, no. I just finished my training.\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Magnus: 'The Order of the Flame, huh? Impressive.'\n");
        printf("Lyla: 'Glad to have someone experienced on board.'\n");
        player->xp += 20;
    } else {
        printf("Magnus: 'A newbie, huh? Don’t worry, we’ll take good care of you.'\n");
        printf("Lyla: 'Just stick close and you’ll be fine, rookie.'\n");
        player->xp += 5;
    }

    printf("You gained %d XP. Your total XP is now %d.\n", choice == 1 ? 20 : 5, player->xp);

    printf("After some conversation about Magnus and Lyla's previous experiences with dragons, they ask you to make a decision on who you want to be paired up with.\n");

    printf("1: Pair up with Lyla\n");
    printf("2: Pair up with Magnus\n");

    scanf("%d", &choice);
    player->partner = choice == 1 ? -1 : 0;

    printf("Congratulations on joining the team! Suddenly, alarms blare - a dragon is attacking a nearby neighborhood. The team departs the HQ.\n");
}


void chapter2(Player *player) {
    
}

void chapter3(Player *player) {
    
}

void chapter4(Player *player) {

}

void chapter5(Player *player) {

}
