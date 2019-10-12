#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"

int main(void)
{
    srand(time(NULL));
    //Database for the categories
    char database[] = "Titles|Robinson Crusoe|Alice's Adventures in Wonderland|Heart of Darkness|The Lord of the Rings|Game of Thrones|House of Cards^Quotes|Two wrongs don't make a right|When in Rome, do as the Romans|Hope for the best, but prepare for the worst|Keep your friends close and your enemies closer^Names|William Shakespeare|John Kennedy|Sherlock Holmes|Martin Luther King|Friedrich Nietzsche^Proverbs|He who does not advance goes backwards|If you can't beat them, join them|Don't judge a book by its cover|A broken watch is right two times a day|The best defence is a good offence|No man can serve two masters";

    //Every possible result of a wheel spin
    int circle[] = {25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 425, 450, 475,-1,-1,-1,-2,-2};

    //Parse the database here
    //Gets the number of categories
    int number_of_categories=1;
    for(int i = 0; database[i] != '\0'; i++) if(database[i]=='^') number_of_categories++;

    //This is gonna store all the categories with their passwords
    char list_of_categories[number_of_categories][500];
    char copy_list_of_categories[number_of_categories][500];
    //Make a copy of the Database
    char databaseCopy[strlen(database)];
    strcpy(databaseCopy,database);

    //Create a pointer for the strtok to split the string
    char * tempPointer;
    tempPointer = strtok(databaseCopy, "^"); //Gets the string up to the first occurence of ^


    //A loop to get all the categories, strtok with null means the strtok will continue from where it finished last
    int categoriesIndex = 0;
    while(tempPointer != NULL)
    {
        strcpy(list_of_categories[categoriesIndex],tempPointer);
        strcpy(copy_list_of_categories[categoriesIndex],tempPointer);
        categoriesIndex++;
        tempPointer = strtok(NULL, "^");
    }

    //Create a list of all the words in a multidimensional array
    int number_of_passwords = 10; //Since number of passwords aren't equal in all categories, i'm gonna assign a safe value
    int max_length_of_password = 100; //Similar situation here
    char list_of_passwords[number_of_categories][number_of_passwords][max_length_of_password];

    //Now a loop to fill the array list_of_passwords
    char * tempPointer2;
    int passwordsIndex = 0;
    int categoriesIndex2 = 0;

    while(categoriesIndex2 < number_of_categories)
    {
        tempPointer2 = strtok(list_of_categories[categoriesIndex2],"|");
        passwordsIndex = 0;
        while(tempPointer2 != NULL)
        {
            strcpy(list_of_passwords[categoriesIndex2][passwordsIndex],tempPointer2);
            passwordsIndex++;
            tempPointer2 = strtok(NULL,"|");
        }
        categoriesIndex2++;
    }

    //All the passwords are now nicely stored in the list_of_passwords array

    //Now for the user interface and game logic

    //How many users
    int players_count;
    while(1)
    {
        printf("Ilu graczy(1-3, jesli zostanie miejsce to zajmie je bot): ");
        scanf("%d",&players_count);
        if(players_count>0 && players_count < 4) break;
        printf("Out of bounds :)\n");
    }
    int bot_count = 3 - players_count;
    //If less than 3 then ask for bot difficulties
    int difficulty_bot_1;
    int difficulty_bot_2;
    if(players_count == 2)
    {
        while(1)
        {
            printf("Trudnosc bota 1(latwy-0, trudny-1): ");
            scanf("%d",&difficulty_bot_1);
            if(difficulty_bot_1>=0 && difficulty_bot_1<=1) break;
            else printf("Tak nie wolno :( \n");
        }
    }
    if(players_count == 1)
    {
        while(1)
        {
            printf("Trudnosc bota 1(latwy-0, trudny-1): ");
            scanf("%d",&difficulty_bot_1);
            printf("Trudnosc bota 2(latwy-0, trudny-1): ");
            scanf("%d",&difficulty_bot_2);
            if((difficulty_bot_1>=0 && difficulty_bot_1<=1) && (difficulty_bot_2 >= 0 && difficulty_bot_2 <= 1)) break;
            else printf("Tak nie wolno :( \n");
        }
    }

    int game_on = 1;
    int current_round = 0;
    int players_account[players_count+bot_count];
    for(int i = 0; i < players_count+bot_count; i++)
    {
        players_account[i] = 0;
    }
    enum PLAYER_TYPE current_player;
    if(players_count!=3) current_player = difficulty_bot_1;
    else current_player = 2;
    int next_player = 0;
    int nagroda;
    int password_guessed = 0;
    char tempPassGuess[100];
    char tempCurrentPassword[100];
    char password_guess[100];
    char consonant, vowel;
    int player = 0;
    int indexlisty = 0;
    int indexlisty2 = 0;
    //Main game loop
    while(game_on)
    {
        indexlisty = 0;
        char list_of_letters[100];
        for(int i = 0; i<100; i++) list_of_letters[i] = '#';
        indexlisty2 = 0;
        char list_of_wrong_letters[100];
        for(int i = 0; i<100; i++) list_of_wrong_letters[i] = '#';
        current_round += 1;
        if(current_round>=4)
        {
            printf("Koniec gry!\n");
            printf("Wyniki koncowe\n");
            printf("-------------------\n");
            for(int i = 0; i < players_count+bot_count; i++)
            {
                printf("Stan konta gracza %d: %d zl\n", i+1, players_account[i]);
            }
            getchar();
            break;
        }
        //Get a random category and corresponding random password withing the category
        int random_category = rand()%number_of_categories; //(0-3)
        //Since different categories have different amount of passwords we need to get those
        int passwords_for_current_category=0;
        for(int i = 0; i<strlen(copy_list_of_categories[random_category]); i++)
        {
             if(copy_list_of_categories[random_category][i]=='|') passwords_for_current_category++;
        }

        int random_password = rand()%passwords_for_current_category;
        if(random_password == 0) random_password += 1;
        char * currentCategory = list_of_passwords[random_category][0];
        char * currentPassword = list_of_passwords[random_category][random_password];
        char hiddenPassword[strlen(currentPassword)];
        password_guessed = 0;
        int passwordlength = 0;
        for(int i = 0; currentPassword[i] != '\0'; i++)
        {
            if(is_letter(currentPassword[i])) passwordlength++;
        }
        while(!password_guessed) //Choices loop, break only if the password has been guessed
        {
            if(next_player) //Controls players and bots orders
            {
                player++;
                if(players_count == 2)
                {
                    if(!difficulty_bot_1)
                    {
                        if(current_player == 0) current_player = 2;
                        if(current_player == 2 && player == 3) current_player = 0;
                    }
                    if(difficulty_bot_1)
                    {
                        if(current_player == 1) current_player = 2;
                        if(current_player == 2 && player == 3) current_player = 1;
                    }
                }
                else if(players_count == 1)
                {
                    if(!difficulty_bot_1 && !difficulty_bot_2)
                    {
                        if(current_player == 2) current_player = 0;
                        if(current_player == 0 && player == 1) current_player = 2;
                    }
                    if(difficulty_bot_1 && difficulty_bot_2)
                    {
                        if(current_player == 2) current_player = 1;
                        if(current_player == 1 && player == 1) current_player = 2;
                    }
                    else
                    {
                        if(difficulty_bot_1 == 0 && difficulty_bot_2 == 1)
                        {
                            if(current_player == 2) current_player = 0;
                            else if(current_player == 0) current_player = 1;
                            else if(current_player == 1 ) current_player = 2;
                        }
                        else if(difficulty_bot_1 == 1 && difficulty_bot_2 == 0)
                        {
                            if(current_player == 2) current_player = 1;
                            else if(current_player == 1) current_player = 0;
                            else if(current_player == 0) current_player = 2;
                        }
                    }
                }
                if(player >= players_count+bot_count) player = 0;
                next_player = 0;
            }
            printf("------------------------------------\n");
            printf("Runda: %d\n", current_round);
            printf("Tura gracza: %d\n", player+1);
            printf("Wylosowana kategoria: %s\n",currentCategory);
            //Hide the password here
            printf("Wylosowane haslo: ");
            for(int i = 0; i < strlen(currentPassword); i++)
            {
                if((is_letter(currentPassword[i])) && (!(in_list(currentPassword[i],list_of_letters))))
                {
                    hiddenPassword[i] = '_';
                    printf("_");
                }
                else
                {
                    hiddenPassword[i] = currentPassword[i];
                    printf("%c",currentPassword[i]);
                }
            }
            if(count_letters(hiddenPassword) == passwordlength)
            {
                printf("\n");
                printf("Odkryto haslo!\n");
                players_account[player] += (1000*current_round);
                break;
            }
            printf("\n");
            printf("........................................\n");
            //Print the possible Choices
            for(int i = 0; i < players_count+bot_count; i++)
            {
                printf("Stan konta gracza %d: %d zl\n", i+1, players_account[i]);
            }
            printf("1.Zakrec kolem\n");
            printf("2.Kup samogloske\n");
            printf("3.Zgadnij haslo\n");
            enum ACTION choice;
            printf("Wybor: ");
            choice = choose_action(currentPassword, players_account[player], current_player, hiddenPassword);
            switch(choice)
            {
                case 1: //Spin the wheel
                nagroda = spin_the_wheel(circle);
                printf("Nagroda: %d\n",nagroda);
                if(nagroda >= -2 && nagroda <= -1)
                {
                    if(nagroda == -2)
                    {
                        printf("Tracisz ture!\n");
                        next_player = 1;
                        break;
                    }
                    if(nagroda == -1)
                    {
                        printf("Bankrutujesz!\n");
                        players_account[player] = 0;
                        next_player = 1;
                    }
                }
                else
                {
                    players_account[player] += nagroda;
                    //Guess a consonant here
                    while(1)
                    {
                        consonant = choose_letter(hiddenPassword, 1, current_player, list_of_letters, list_of_wrong_letters);
                        if(is_consonant(consonant)) break;
                        else printf("Nie podales spolgoski! Podaj ponownie\n");
                    }

                    if(in_password(consonant, currentPassword))
                    {
                        if(!in_list(consonant,list_of_letters))
                        {
                            printf("Podales poprawna spolgloske!\n");
                            printf("Zostanie odkryta w hasle!\n");
                            append_list(consonant, list_of_letters, indexlisty);
                            indexlisty++;
                        }
                        else
                        {
                            printf("Ta spolgloska zostala juz podana!\n");
                            next_player = 1;
                        }
                    }
                    else
                    {
                        printf("Podales zla spolgloske!\n");
                        append_list(consonant, list_of_wrong_letters, indexlisty2);
                        indexlisty2++;
                        next_player = 1;
                    }
                }
                break;

                case 2: //Buy a vowel
                //You can only buy a vowel if you have >= 250 pln
                if(players_account[player] >= 250)
                {
                    printf("Zakupiles probe zgadniecia samogloski!\n");
                    players_account[player] -= 250;
                    while(1)
                    {
                        vowel = choose_letter(hiddenPassword, 0, current_player, list_of_letters, list_of_wrong_letters);
                        if(!is_vowel(vowel)) printf("Nie podales samogloski!\n");
                        else break;
                    }
                    if(in_password(vowel, currentPassword))
                    {
                        if(!in_list(vowel,list_of_letters))
                        {
                            printf("Podales poprawna samogloske!\n");
                            printf("Zostanie odkryta w hasle!\n");
                            append_list(vowel, list_of_letters, indexlisty);
                            indexlisty++;
                        }
                        else
                        {
                            printf("Ta samogloska zostala juz podana!\n");
                            next_player = 1;
                        }
                    }
                    else
                    {
                        printf("Podales zla samogloske!\n");
                        append_list(vowel, list_of_wrong_letters, indexlisty2);
                        indexlisty2++;
                        next_player = 1;
                    }
                }
                else
                {
                    printf("Nie posiadasz wystarczajaco pieniazkow!\n");
                    next_player = 1;
                }
                break;

                case 3: //Guess the password
                guess_puzzle(currentPassword, list_of_passwords[random_category][0], password_guess, current_player, hiddenPassword);

                for(int i = 0; i < strlen(password_guess); i++)
                {
                    if(is_letter(password_guess[i])) tempPassGuess[i] = tolower(password_guess[i]);
                    else tempPassGuess[i] = password_guess[i];
                }
                tempPassGuess[strlen(password_guess)] = '\0';

                for(int i = 0; i< strlen(currentPassword); i++)
                {
                    if(is_letter(currentPassword[i])) tempCurrentPassword[i] = tolower(currentPassword[i]);
                    else tempCurrentPassword[i] = currentPassword[i];
                }
                tempCurrentPassword[strlen(currentPassword)] = '\0';

                if(strcmp(tempPassGuess, tempCurrentPassword)==0)
                {
                    printf("Zgadles!\n");
                    players_account[player] += (1000*current_round);
                    password_guessed = 1;
                }
                else
                {
                    printf("Nie zgadles!\n");
                    next_player = 1;
                }
                break;

                default:
                printf("Nie ma takiej opcji!\n");
            }
        }
    }
    getchar();
    return 0;
}
