#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int hp;
    int xp;
    int partner;
    int weapon;
    int armor;
    int heal_potion;
    // int attack_potion;
    // int heal_spell;
    int chapter;
} Player;

// function prototypes for each chapter
void start();
void chapter1(Player *player);
void chapter2(Player *player);
void chapter3(Player *player);
void chapter4(Player *player);
void chapter5(Player *player);
void loadGame(const char *filepath, Player *player);
void saveGame(Player *player, const char *filepath);
int duel(Player *player);

int main() {
    Player player;

    printf("Load game from file or start new game?\n 1: load \n2: start new game)\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("filepath: \n");
        char path[200];
        scanf("%s", path);
        loadGame(path, &player);
    } else if (choice == 2) {
        start(&player);
    } else {
        printf("You picked the wrong opiton.\nStarting new game.....\n");
        start(&player);
    }
    return 0;
}

void start(Player *player){

    player->hp = 100;
    player->xp = 0;
    player->partner = 0;
    player->weapon = 0;
    player->armor = 0;
    player->heal_potion = 0;
    // player->attack_potion = 0;
    player->chapter = 0;

    chapter1(player);
}

void chapter1(Player *player) {
    printf("Welcome to Pyroklas, a city under siege by rogue dragons. As the newest member of the Wing of Fire Squad, it's your job to help protect the city.\n");

    printf("Your new teammates are Lyla and Magnus. Lyla is a seasoned dragon hunter, smart and agile. Magnus is strong and ambitious but a bit self-absorbed.\n");

    printf("What's your name?\n");
    fflush(stdin);
    fgets(player->name, 50, stdin);
    player->name[strcspn(player->name, "\n")] = '\0';

    printf("Lyla turns to you and asks, 'So, %s, ever had a close encounter with a dragon before?'\n", player->name);

    printf("1: I arrived from Flanor where I was a member of the Order of the Flame.\n");
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
    player->partner = choice == 1 ? 1 : 2;

    printf("Good choice! Congratulations on joining the team!\nSuddenly, alarms blare - a dragon is attacking a nearby neighborhood. The team departs the HQ. The adventure starts now. \n");

    player->chapter++;
    saveGame(player, "savegame.txt");

    chapter2(player);   
}

void chapter2(Player *player) {
    printf("As you and your team approach the endangered neighborhoods of Pyroklas, the air grows thick with smoke. The once vibrant streets are now deserted, save for the flickering shadows cast by the raging fires.\n");

    printf("Suddenly, a deafening roar echoes through the air, sending a chill down your spine. You turn to see a massive dragon, its scales glistening in the firelight, looming over the city. Its eyes, glowing with an eerie light, meet yours, and for a moment, time seems to stand still.\n");

    printf("Lyla grips her bow tightly, her eyes never leaving the dragon. Magnus, despite his earlier bravado, seems taken aback by the sight of the beast.\n");

    printf("On the ground, you find a scroll with a riddle: 'I fly without wings, I cry without eyes. Wherever I go, darkness follows me. What am I?'\n");

    printf("1: A cloud\n");
    printf("2: The wind\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Correct! The scroll glows and a spell to banish the dragon appears. You gain 10 XP and a spell to banish the dragon.\n");
        player->xp += 10;
        printf("You used the spell and the dragon vanished.");
    } else {
        printf("Incorrect! The dragon roars and attacks. You must fight the dragon.\n");
        if (duel(player)) {
            printf("You defeated the dragon! You gain 20 XP. \n");
            player->xp += 20;
        } else {
            printf("You were defeated by the dragon. Game over.\n");
            return;
        }
    }

    printf("After the battle, you find a weird colored potion. Do you pick it up? (Beware, it might be dangerous.)\n");
    printf("1: Yes\n");
    printf("2: No\n");

    scanf("%d", &choice);

    if (choice == 1) {
        int randomOutcome = rand() % 3;

        switch (randomOutcome) {
            case 0:
                printf("You picked up the healing potion.\n");
                player->heal_potion++;
                break;
            case 1:
                printf("Oh no! It's poison. (-10 hp)\n");
                player->hp -= 10;
                break;
            case 2:
                printf("It's just water. No effect.\n");
                break;
        }
    }

    printf("As you continue your journey, you encounter a short grumpy man who tells you a legend about the Emberlord.\n"); // TODO: think of the legend
    printf("During his story, you hear a noise. It's probably a piece of ruined building that fell.\n");
    printf("1: Follow the noise\n");
    printf("2: Stay and listen to the rest of the story\n");

    scanf("%d", &choice);

    if (choice == 1) {
        printf("You follow the noise and find a old woman trapped under some rubble. You manage to save her and as a thank you she gives you a healing potion.\n");
        player->heal_potion++;
    } else {
        printf("You decide to stay and listen to the rest of the story. Unfortunately, there was nothing important left to hear.\n");
    }

    printf("Your journey continues...\n");

    player->chapter++;
    saveGame(player, "savegame.txt");

    chapter3(player);
}

void chapter3(Player *player) {
    printf("The team member you didn't choose to pair up with decides to check something out, leaving you with your partner.\n"); // fix this so it uses names

    printf("On the ground, you find another scroll with a riddle: 'I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?'\n");

    printf("1: An echo\n");
    printf("2: A shadow\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Correct! The scroll glows and you gain 20 XP.\n");
        player->xp += 10;
    } else {
        printf("Incorrect! Nothing happens.\n");
    }

    printf("Suddenly, a duel ensues."); // fix this so it describes the dragon

    if (duel(player)) {
        printf("You defeated the dragon! You gain 20 XP. \n");
        player->xp += 20;
    } else {
        printf("You were defeated by the dragon. Game over.\n");
        return;
    }

    printf("After the duel, a shiny object falls to the ground.\n");

    printf("Do you pick it up?\n");
    printf("1: Yes\n");
    printf("2: No\n");

    scanf("%d", &choice);

    if (choice == 1) {
        printf("You picked up the object, but it's cursed! You start rapidly losing HP.\n");
        if (player->heal_potion > 0) {
            printf("You use a healing potion and recover your HP.\n");
            player->heal_potion--;
        } else if (player->partner == 1) {
            printf("Your partner Lyla gives you her potion and you are saved.\n");
            player->hp += 10;
        } else {
            printf("Your partner Magnus betrays you and runs away. You die. Game over.\n");
            return;
        }
    } else {
        printf("You didn't pick up the object. It explodes, but luckily you dodge the bullet.\n");
    }

    if (player->hp > 0) {
        printf("A woman comes up to you and tells you she can't reach her family and asks you to go check it out.\n");

        printf("1: Go check it out\n");
        printf("2: Proceed with your mission\n");

        scanf("%d", &choice);

        if (choice == 1) {
            printf("You decide to help the woman and go check it out.\n");
            player->chapter++;
            saveGame(player, "savegame.txt");
            chapter4(player);
        } else {
            printf("You decide to proceed with your mission.\n");
            player->chapter+=2;
            saveGame(player, "savegame.txt");
            chapter5(player);
        }
    }
}

void chapter4(Player *player) {
    printf("You reunite with your third team member. The three of you stand together, ready to face whatever comes next.\n"); // TODO: add the name

    printf("On the ground, you find another scroll with a riddle: 'I am taken from a mine, and shut up in a wooden case, from which I am never released, and yet I am used by almost every person. What am I?'\n");

    printf("1: A pencil\n");
    printf("2: A diamond\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Correct! The scroll glows and you gain 10 XP. It also reveals a piece of information about the Emberlord: 'The Emberlord's scales are impenetrable, save for one weak spot right beneath its left wing.'\n");
        player->xp += 10;
    } else {
        printf("Incorrect! Nothing happens.\n");
    }

    printf("A duel ensues with a dragon. After the duel, you notice a burning building on the verge of collapsing.\n"); // fix this "you encounter the dragon blah blah"

    if (duel(player)) {
        printf("You defeated the dragon! You gain 20 XP. \n");
        player->xp += 20;
    } else {
        printf("You were defeated by the dragon. Game over.\n");
        return;
    }

    printf("Do you go into the building? There might be someone there. Are you willing to risk your life?\n");
    printf("1: Yes\n");
    printf("2: No\n");

    scanf("%d", &choice);

    if (choice == 1) {
        // randomize this later (50% chance of dying)
        printf("You decide to risk it and go into the building. You manage to save a puppy just in time. A freckled ginger boy comes up to you and recites a poem:\n");
        printf("\n```\nIn the heart of the battle, under the dragon's wing,\n");
        printf("A hero emerges, their praises we sing.\n");
        printf("With courage in their heart and a spear in their hand,\n");
        printf("They strike at the beast, making their stand.\n");
        printf("The spear finds its mark, the dragon's reign ends,\n");
        printf("In the heart of the fire, a new era begins.\n```\n");
    } else {
        printf("You decide not to risk it and stay away from the building.\n");
    }

    printf("Your journey continues...\n");

    player->chapter++;
    saveGame(player, "savegame.txt");

    chapter5(player);
}

void chapter5(Player *player) {
    printf("You arrive at the foot of the volcano, the alleged lair of the Emberlord. The air is thick with smoke and the ground trembles beneath your feet.\n");

    printf("You have to choose your weapon:\n");
    printf("1: Sword\n");
    printf("2: Bow\n");
    printf("3: Spear\n");

    int choice;
    scanf("%d", &choice);
    player->weapon = choice;

    printf("You also have to choose your armor:\n");
    printf("1: Dragon Scale Armor\n");
    printf("2: Iron Plate Armor \n");
    printf("3: Shadow Cloak\n");

    scanf("%d", &choice);
    player->armor = choice;

    printf("With your chosen weapon and armor, you and your team ascend the volcano and confront the Emberlord. The battle begins.\n");

    if (duel(player)) {
        printf("You defeated the dragon! You gain 20 XP. \n");
        player->xp += 20;
    } else {
        printf("You were defeated by the dragon. Game over.\n");
        return;
    }

    printf("During the battle, you get badly injured.\n");
    if (player->heal_potion > 0) {
        printf("It appears you have a spear healing potion. You use it and recover your HP.\n");
        player->hp += 10;
        player->heal_potion--;
    } else if (player->partner == 1) {
        printf("Your partner Lyla gives you her potion and you are saved.\n");
        player->hp += 10;
    } else {
        printf("Your partner Magnus convinces Lyla that they can't save you and they need to head back to the HQ and regroup. You die. Game over.\n");
        return;
    }

    if (player->hp > 0) {
        printf("You find yourself face to face with the giant dragon. You feel its breath on your face, and the heat from its body. You stare into its eyes and notice something. You get a weird lump in your stomach but there is no explanation for it.\n");

        printf("You reach your hand out and touch the dragons face.\n");
        printf("1: Stab the dragon\n");
        printf("2: Don't stab the dragon\n");

        scanf("%d", &choice);

        if (choice == 1) {
            printf("You reach out with your both hand and gently pet the dragon. It transforms into a little girl under yuour gentel touch. It turns out there is an evil warlock who enchanted her. She was scared and panicked, that's why she caused such havoc. There is a treasure hidden somewhere in the city and the warlock enchanted the girl so she would lead the dragon to burn down the city so he could easily access it. Your next adventure awaits...\n");
        } else {
            printf("You give the dragon a final stab in the heart. The dragon dies with a vicious, human-like cry. You feel a pang of guilt inside, as if you did something wrong and there was another way.\n");
            printf("You save the city from destruction. You're a Hero. As a thank you, people of Pyroklas reward you.\n");
        }
    }

    player->chapter++;
    saveGame(player, "savegame.txt");
}

int duel(Player *player) {
    int dragon_hp = 100;
    int round_damage;
    while (dragon_hp > 0 && player->hp > 0) {
        int player_choice;
        printf("Choose your attack power (1-12): ");
        scanf("%d", &player_choice); // player inputs a number from 1-12
        round_damage = (player_choice / player->chapter ) * 2; // divide by chapter and multiply by 2
        round_damage += rand() % 10 - 5; // add a random number between -5 and 5
        round_damage += player->xp / 10; // add a value influenced by the player's xp
        dragon_hp -= round_damage;
        printf("You deal %d damage to the dragon. It has %d HP left.\n", round_damage, dragon_hp);
        if (dragon_hp > 0) {
            round_damage = rand() % (player->chapter * 10);
            player->hp -= round_damage;
            printf("The dragon deals %d damage to you. You have %d HP left.\n", round_damage, player->hp);
        }
    }
    if (player->hp > 0) {
        return 1;
    } 
    return 0;
}

void saveGame(Player *player, const char *filepath) {
    FILE *file = fopen("C:/Users/doros/alltheshit/practice/c/c uni project/savegame.txt", "w");
    if (file == NULL) {
        printf("err\n");
        return;
    }

    fprintf(file, "Mission: Save Pyroklas\n");
    fprintf(file, "name: %s\n", player->name);
    fprintf(file, "hp: %d\n", player->hp);
    fprintf(file, "xp: %d\n", player->xp);
    fprintf(file, "partner: %d\n", player->partner);
    fprintf(file, "weapon: %d\n", player->weapon);
    fprintf(file, "armor: %d\n", player->armor);
    fprintf(file, "heal_potion: %d\n", player->heal_potion);
    // fprintf(file, "attack_potion: %d\n", player->attack_potion);
    // fprintf(file, "heal_spell: %d\n", player->heal_spell);
    fprintf(file, "chapter: %d\n", player->chapter);

    fclose(file);
}

void loadGame(const char *filepath, Player *player) {
    FILE *file = fopen("C:/Users/doros/alltheshit/practice/c/c uni project/savegame.txt", "r");
    if (file == NULL) {
        printf("err\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file);
    if (strcmp(line, "Mission: Save Pyroklas\n") != 0) {
        printf("Invalid game data\n");
        return;
    }

    fgets(line, sizeof(line), file);
    sscanf(line, "name: %s", player->name);
    fgets(line, sizeof(line), file);
    sscanf(line, "hp: %d", &player->hp);
    fgets(line, sizeof(line), file);
    sscanf(line, "xp: %d", &player->xp);
    fgets(line, sizeof(line), file);
    sscanf(line, "partner: %d", &player->partner);
    fgets(line, sizeof(line), file);
    sscanf(line, "weapon: %d", &player->weapon);
    fgets(line, sizeof(line), file);
    sscanf(line, "armor: %d", &player->armor);
    fgets(line, sizeof(line), file);
    sscanf(line, "heal_potion: %d", &player->heal_potion);
    // fgets(line, sizeof(line), file);
    // sscanf(line, "attack_potion: %d", &player->attack_potion);
    // fgets(line, sizeof(line), file);
    // sscanf(line, "heal_spell: %d", &player->heal_spell);
    fgets(line, sizeof(line), file);
    sscanf(line, "chapter: %d", &player->chapter);

    fclose(file);

    // start the game at the saved chapter
    switch (player->chapter) {
        case 0:
            chapter1(player);
            break;
        case 1:
            chapter2(player);
            break;
        case 2:
            chapter3(player);
            break;
        case 3:
            chapter4(player);
            break;
        case 4:
            chapter5(player);
            break;
        default:
            printf("invalid chapter number\nStarting the game from the beginning.....");
            start(player);
            break;
    }
}