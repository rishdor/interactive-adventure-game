#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

typedef struct {
    char name[50];
    int hp;
    int xp;
    int partner;
    int weapon;
    int armor;
    int heal_potion;
    int chapter;
} Player;

const char *dialogs_main[1] = {
"Load game from file or start new game?\n1: load\n2: start new game\n"
};

const char PATH[] = "C:\\Users\\doros\\alltheshit\\practice\\c\\c uni project\\savegame.txt";

// function prototypes for each chapter
void init(Player *player, int load);
void chapter1(Player *player);
void chapter2(Player *player);
void chapter3(Player *player);
void chapter4(Player *player);
void chapter5(Player *player);
void loadGame(const char *filepath, Player *player);
void saveGame(Player *player, const char *filepath);
int duel(Player *player);
void waitForEnter();

typedef void(*f)(Player *player);

f func[5] = {&chapter1, &chapter2, &chapter3, &chapter4, &chapter5};

/**
 * @brief the main function of the program.
 * 
 * this function is the entry point of the program. tt prompts the user to choose between loading a game from a file or starting a new game. 
 * if the user chooses to load a game, it prompts the user to enter the filepath and then calls the loadGame function to load the game from the specified file.
 * if the user chooses to start a new game, it calls the start function to initialize a new game.
 * if the user enters an invalid choice, it displays an error message and starts a new game by default.
 * 
 * @return 0 indicating successful execution of the program.
 */
int main() {
    Player player;

    srand(time(0));

    printf(dialogs_main[0]);

    int choice;
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while (getchar() != '\n');
        printf("Invalid choice, please select 1 or 2:\n");
    }
    
    init(&player, choice);
    
    int i;
    for (i=0; i<5; ++i){
        if (player.chapter == i){
            func[i](&player);
        }
     }

    return 0;
}

void init(Player *player, int load){
    if (load == 1){
        loadGame(PATH, player);     
    }
    else {
        player->hp = 100;
        player->xp = 0;
        player->partner = 0;
        player->weapon = 0;
        player->armor = 0;
        player->heal_potion = 0;
        player->chapter = 0;
    }
}

void chapter1(Player *player) {
    // introductory storyline
    printf("Welcome to Pyroklas, a city under siege by rogue dragons. As the newest member of the Wing of Fire Squad, it's your job to help protect the city.\n");
    waitForEnter();

    printf("Your new teammates are Lyla and Magnus. Lyla is a seasoned dragon hunter, smart and agile. Magnus is strong and ambitious but a bit self-absorbed.\n");
    waitForEnter();

    // prompt player for their name
    printf("What's your name?\n");
    fflush(stdin);
    fgets(player->name, 50, stdin);
    player->name[strcspn(player->name, "\n")] = '\0';

    printf("Lyla turns to you and asks, 'So, %s, ever had a close encounter with a dragon before?'\n", player->name);

    printf("1: I arrived from Flanor where I was a member of the Order of the Flame.\n");
    printf("2: Actually, no. I just finished my training.\n");
  
    int choice;
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while (getchar() != '\n');
        printf("Invalid choice, please select 1 or 2:\n");
    }

    // handle player's choice and update XP
    if (choice == 1) {
        printf("Magnus: 'The Order of the Flame, huh? Impressive.'\n");
        printf("Lyla: 'Glad to have someone experienced on board.'\n");
        player->xp += 20;
    } else {
        printf("Magnus: 'A newbie, huh? Don’t worry, we’ll take good care of you.'\n");
        printf("Lyla: 'Just stick close and you’ll be fine, rookie.'\n");
        player->xp += 5;
    }

    printf("You gained %d XP.\n", choice == 1 ? 20 : 5);
    waitForEnter();

    // prompt player to choose a teammate which is very relevant to the plot
    printf("After some conversation about Magnus and Lyla's previous experiences with dragons, they ask you to make a decision on who you want to be paired up with.\n");

    printf("1: Pair up with Lyla\n");
    printf("2: Pair up with Magnus\n");

    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while (getchar() != '\n');
        printf("Invalid choice, please select 1 or 2:\n");
    }
    player->partner = choice == 1 ? 1 : 2;

    printf("Good choice! Congratulations on joining the team!\nSuddenly, alarms blare - a dragon is attacking a nearby neighborhood. The team departs the HQ. The adventure starts now. \n");
    waitForEnter();

    // update player's progress and save the game
    player->chapter++;
    saveGame(player, PATH);
}

void chapter2(Player *player) {
    printf("As you and your team approach the endangered neighborhoods of Pyroklas, the air grows thick with smoke. The once vibrant streets are now deserted, save for the flickering shadows cast by the raging fires.\n");
    waitForEnter();

    printf("Suddenly, a deafening roar echoes through the air, sending a chill down your spine. You turn to see a massive dragon, its scales glistening in the firelight, looming over the city. Its eyes, glowing with an eerie light, meet yours, and for a moment, time seems to stand still.\n");
    waitForEnter();

    printf("Lyla grips her bow tightly, her eyes never leaving the dragon. Magnus, despite his earlier bravado, seems taken aback by the sight of the beast.\n");
    waitForEnter();

    // a riddle
    printf("On the ground, you find a scroll with a riddle: 'I fly without wings, I cry without eyes. Wherever I go, darkness follows me. What am I?'\n");

    printf("1: A cloud\n");
    printf("2: The wind\n");

    int choice;
    // input validation
    do {
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
        } else if (choice < 1 || choice > 2) {
            printf("Choice must be 1 or 2.\n");
        }
    } while (choice < 1 || choice > 2);

    if (choice == 1) {
        printf("Correct! The scroll glows and a spell to banish the dragon appears. You gain 10 XP and a spell to banish the dragon.\n");
        player->xp += 10;
        printf("You used the spell and the dragon vanished.\n");
    } else {
        printf("Incorrect! The dragon roars and attacks. You must fight the dragon.\n");
        waitForEnter();
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

    do {
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
        } else if (choice < 1 || choice > 2) {
            printf("Choice must be 1 or 2.\n");
        }
    } while (choice < 1 || choice > 2);

    // picking a randomized item
    if (choice == 1) {
        int randomOutcome = rand() % 10; // generate a number between 0 and 9
        
        if (randomOutcome < 4) { // 0, 1, 2, 3 for healing potion (40%)
            printf("You picked up the healing potion.\n");
            player->heal_potion++;
        } else if (randomOutcome < 8) { // 4, 5, 6, 7 for poison (40%)
            printf("Oh no! It's poison! (-10 hp)\n");
            player->hp -= 10;
        } else { // 8, 9 for water (20%)
            printf("It's just water. No effect.\n");
        }
    }

    printf("As you continue your journey, you encounter a short grumpy man who tells you a legend about the Emberlord.\n");
    waitForEnter();

    printf("'In our city, there exists an old tale,' he begins, his voice raspy with age. 'It speaks of a time when dragons lived in harmony with us. But as the game of life progressed, a mysterious force began to stir them up.'\n");
    waitForEnter();

    printf("'This force,' he continues, 'is known only as the Lord of Embers. A creature of myth, a dragon of legend, said to have lived for centuries hidden in the volcanic mountains surrounding Pyroklas. To defeat it, they say you have to...'\n");
    waitForEnter();

    printf("Suddenly you hear a faint noise. It's probably a piece of ruined building that fell but you never know right?.\n");
    printf("1: Follow the noise\n");
    printf("2: Stay and listen to the rest of the story\n");

    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while (getchar() != '\n');
        printf("Invalid choice, please select 1 or 2:\n");
    }

    if (choice == 1) {
        printf("You follow the noise and find an old woman trapped under some rubble. You manage to save her and as a thank you she gives you a healing potion.\n");
        player->heal_potion++;
    } else {
        printf("You decide to stay and listen to the rest of the story. Unfortunately, there was nothing important left to hear. Old man was rambling about the red mood and withes. You thanked him for the information.\n");
    }

    printf("Your journey continues...\n");

    player->chapter++;
    saveGame(player, PATH);
}

void chapter3(Player *player) {
    printf("%s decided to check something out, at the other end of the city and separates from you and %s.\n", player->partner == 1 ? "Magnus" : "Lyla",  player->partner == 2 ? "Magnus" : "Lyla");
    waitForEnter();

    printf("On the ground, you find another scroll with a riddle: 'I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?'\n");

    printf("1: An echo\n");
    printf("2: A shadow\n");

    int choice;
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while (getchar() != '\n');
        printf("Invalid choice, please select 1 or 2:\n");
    }

    if (choice == 1) {
        printf("Correct! The scroll glows and you gain 20 XP.\n");
        player->xp += 20;
    } else {
        printf("Incorrect! Nothing happens.\n");
    }

    printf("Suddenly, a thunderous growl rumbles through the air, causing the ground beneath you to shudder. You turn to see an enormous dragon, its scales shimmering like diamonds.\n");
    waitForEnter();

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

    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while (getchar() != '\n');
        printf("Invalid choice, please select 1 or 2:\n");
    }

    if (choice == 1) {
        printf("You picked up the object, but it's cursed! You start rapidly losing HP.\n");
        waitForEnter();

        if (player->heal_potion > 0) {
            printf("You used a healing potion and recoved your HP to 100.\n");
            player->heal_potion--;
            player->hp = 100;
        } else if (player->partner == 1) {
            printf("Your partner Lyla gives you her potion and you are saved.\n");
            player->hp = 100;
        } else {
            printf("Unfortunately you don't have any healing potions.\n");
            waitForEnter();
            printf("You ask your partner Magnus to give you his, but he refuses and walks away. Your journey ends here. Game over.\n"); // first real ending [based on choices] (dying in the duel is just lame so it doesnt count)
            return;
        }
    } else {
        printf("You didn't pick up the object. It explodes, but luckily you dodged the bullet.\n");
    }

    if (player->hp > 0) {
        printf("A woman comes up to you and tells you she can't reach her family and asks you to go check it out.\n");
    
        printf("1: Go check it out\n");
        printf("2: Proceed with your mission\n");
    
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
            while (getchar() != '\n');
            printf("Invalid choice, please select 1 or 2:\n");
        }
    
        if (choice == 1) {
            printf("You decide to help the woman and go check it out.\n");
            player->chapter++;
        } else {
            printf("You decide to proceed with your mission.\n");
            player->chapter = 4;
        }
        saveGame(player, PATH);
    }
}

void chapter4(Player *player) {
    // chapter that can be skipped depending on the last decision but it has some important clues about the final battle so i dont recommend skipping it
    printf("You reunite with your third team member. The three of you stand together, ready to face whatever comes next.\n");
    waitForEnter();

    printf("On the ground, you find another scroll with a riddle: 'I am taken from a mine, and shut up in a wooden case, from which I am never released, and yet I am used by almost every person. What am I?'\n");

    printf("1: A pencil\n");
    printf("2: A diamond\n");

    int choice;
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while (getchar() != '\n');
        printf("Invalid choice, please select 1 or 2:\n");
    }

    if (choice == 1) {
        printf("Correct! The scroll glows and you gain 10 XP. It also reveals a piece of information about the Emberlord: 'The Emberlord's scales are impenetrable, save for one weak spot right beneath its left wing.'\n");
        player->xp += 10;
    } else {
        printf("Incorrect! Nothing happens.\n");
    }
    waitForEnter();

    printf("A piercing screech slices through the air, sending a jolt of fear down your spine. You turn to see a colossal dragon, its scales a vibrant green that blends seamlessly with the foliage, looming over the trees.\n");
    waitForEnter();

    printf("You notice that the dragon starts moving in the direction of a civilians so you jump in front of them to save them.\n");
    waitForEnter();

    if (duel(player)) {
        printf("You defeated the dragon! You gain 20 XP. \n");
        player->xp += 20;
    } else {
        printf("You were defeated by the dragon. Game over.\n");
        return;
    }
    printf("After the vicious battle, you notice a burning building on the verge of collapsing.\n");
    printf("Do you go into the building? There might be someone there. Are you willing to risk your life?\n");
    printf("1: Yes\n"); // this choice has 25% of dying and 75% clue which weapon to choose to defeat the boss
    printf("2: No\n");

    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while (getchar() != '\n');
        printf("Invalid choice, please select 1 or 2:\n");
    }
    
    if (choice == 1) {
        if (rand() % 4 != 0 ) { 
            printf("You decide to risk it and go into the building. You manage to save a puppy just in time. It's owner (freckled ginger boy) comes up to you and recites a poem:\n");
            waitForEnter();
            // a poem generated by Bing Copilot (some of the dialogues and narrator entries are written by me but fixed by Bing)
            printf("\n```\nIn the heart of the battle, under the dragon's wing,\n");
            printf("A hero emerges, their praises we sing.\n");
            printf("With courage in their heart and a spear in their hand,\n");
            printf("They strike at the beast, making their stand.\n");
            printf("The spear finds its mark, the dragon's reign ends,\n");
            printf("In the heart of the fire, a new era begins.\n```\n");
            waitForEnter();
        } else {
            printf("You decide to risk it and go into the building, but unfortunately, it collapses before you can exit. You did not survive. Game over.\n"); // second real ending [almost random death -- just unlucky]
            return;
        }
    } else {
        printf("You decide not to risk it and stay away from the building.\n");
    }

    printf("You saved the civilians and got an important clue. Good job!\nYour journey continues...\n");

    player->chapter++;
    saveGame(player, PATH);
}

void chapter5(Player *player) {
    printf("You arrive at the foot of the volcano, the alleged lair of the Emberlord. The air is thick with smoke and the ground trembles beneath your feet.\n");

    printf("You have to choose your weapon:\n");
    printf("1: Sword\n");
    printf("2: Bow\n");
    printf("3: Spear\n"); // best one [influences damage points in battle]

    int choice;
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        while (getchar() != '\n'); 
        printf("Invalid choice, please select 1, 2, or 3:\n");
    }
    player->weapon = choice;

    printf("You also have to choose your armor:\n");
    printf("1: Dragon Scale Armor\n");
    printf("2: Iron Plate Armor\n");
    printf("3: Shadow Cloak\n"); // best one [influences damage points in battle]

    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        while (getchar() != '\n'); 
        printf("Invalid choice, please select 1, 2, or 3:\n");
    }
    player->armor = choice;

    printf("With your chosen weapon and armor, you and your team ascend the volcano and confront the Emberlord. The battle begins.\n");

    if (duel(player)) {
        printf("You defeated the dragon! You gain 20 XP.\n");
        player->xp += 20;
    } else {
        printf("You were defeated by the dragon. Game over.\n"); // this duels death is the most probable out of all duel deaths
        return;
    }

    printf("During the battle, you get badly injured.\n");
    if (player->heal_potion > 0) {
        printf("It appears you have a healing potion. You use it and recover your HP.\n");
        player->hp += 10;
        player->heal_potion--;
    } else if (player->partner == 1) {
        printf("Your partner Lyla gives you her potion and you are saved.\n");
        player->hp += 10;
    } else {
        printf("Your partner Magnus convinces Lyla that they can't save you and they need to head back to the HQ and regroup. You die. Game over.\n"); // third real ending [completely based on decisions]
        return;
    }
    
    if (player->hp > 0) {
        printf("You find yourself face to face with the giant dragon. You feel its breath on your face, and the heat from its body. You stare into its eyes and notice something. You get a weird lump in your stomach but there is no explanation for it.\n");
        waitForEnter();

        printf("You reach your hand out and touch the dragon's face.\n");
        printf("1: Stab the dragon\n");
        printf("2: Don't stab the dragon\n");
    
        int choice;
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
            while (getchar() != '\n'); 
            printf("Invalid choice, please select 1 or 2:\n");
        }
    
        if (choice == 2) {
            printf("You reach out with your both hand and gently pet the dragon. It transforms into a little girl under your gentle touch. It turns out there is an evil warlock who enchanted her. She was scared and panicked, that's why she caused such havoc. There is a treasure hidden somewhere in the city and the warlock enchanted the girl so she would lead the dragon to burn down the city so he could easily access it. Your next adventure awaits...\n");
        } else {
            printf("You give the dragon a final stab in the heart. The dragon dies with a vicious, human-like cry. You feel a pang of guilt inside, as if you did something wrong and there was another way.\n");
 
        }

        waitForEnter();
        printf("You saved the city from the destruction. You're a Hero now. As a thank you, people of Pyroklas reward you.\n"); // 4 and 5 ending aka The Victory
    }

    player->chapter++;
    saveGame(player, PATH);
}

// there is a lot of room for impovement for this method but this is the best one i managed to do that made winning possible
// it takes into account the current chapter (level), the xp points gained, the weapon and armor chosen at the last chapter and of course there is a bit of pseudo randomness
int duel(Player *player) {

    int dragon_hp = 100 + (player->chapter - 1) * 25; 
    
    printf("You are in a battle with the dragon. It has %d HP.\n", dragon_hp);

    while (dragon_hp > 0 && player->hp > 0) {
        Sleep(2000);

        int attack_bonus = (player->armor + player->weapon) * 2;
        int player_attack = (rand() % 11 + 10) + player->chapter * 3 + player->xp / 10 + attack_bonus;
        dragon_hp -= player_attack;
        printf("You deal %d damage. Dragon HP: %d\n", player_attack, dragon_hp);

        if (dragon_hp <= 0) break;

        int dragon_attack = (rand() % 3 + 3);
        player->hp -= dragon_attack;
        printf("Dragon deals %d damage. Player HP: %d\n", dragon_attack, player->hp);
    }

    if (player->hp > 0) {
        return 1;
    } else {
        return 0;
    }
}

void waitForEnter() {
    printf("(next)\n");
    char c;
    do {
        c = getch();
    } while (c != '\r' && c != ' ');
}

// saving the game for later loading, saving is at the end of each chapter
// if the player hasnt finished the chapter they will start from the beginning of that chapter (mining xp is not possible:))
void saveGame(Player *player, const char *filepath) {
    FILE *file = fopen(filepath, "w");
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
    fprintf(file, "chapter: %d\n", player->chapter);

    fclose(file);
}

void loadGame(const char *filepath, Player *player) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("err\n");
        return;
    }

    char line[256];
    // checking if the header matches --> checking if the file is actualy a saved game or a random file
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
    fgets(line, sizeof(line), file);
    sscanf(line, "chapter: %d", &player->chapter);

    fclose(file);
}