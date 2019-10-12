#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

//Functions required by the task
int count_letters(const char tab[])
{
    int letters = 0;
    for(int i = 0; tab[i] != '\0'; i++)
    {
        if(is_letter(tab[i])) letters++;
    }
    return letters;
}

void guess_puzzle(const char tab[], const char category[], char tab2[], enum PLAYER_TYPE player, char tab3[])
{
    if(player == 0)
    {
        //The weaker bot, always has 25% to correctly guess the password
        int random_num = rand()%4;
        if(!random_num)
        {
            strcpy(tab2,tab);
        }
        else
        {
            strcpy(tab2,"nie udalo sie");
        }
    }
    else if(player == 1)
    {
        //The stronger bot
        int number_of_letters_in_password = 0;
        for(int i = 0; tab[i] != '\0'; i++)
        {
            if(is_letter(tab[i])) number_of_letters_in_password++;
        }
        float res = count_letters(tab3) / (float)number_of_letters_in_password;
        res *= 100;
        int random_num = rand()%101;
        if(random_num <= (int)res)
        {
            strcpy(tab2,tab);
        }
        else
        {
            strcpy(tab2,"nie udalo sie");
        }
    }
    else if(player == 2)
    {
        char ftempass[100];
        printf("Zgadnij haslo: ");
        scanf("%100[^\n]s", ftempass);
        strcpy(tab2,ftempass);
    }
}

enum ACTION choose_action(const char tab[], int money, enum PLAYER_TYPE player, char tab2[])
{
    int number;
    int number_of_letters_in_password = 0;
    for(int i = 0; tab[i] != '\0'; i++)
    {
        if(is_letter(tab[i])) number_of_letters_in_password++;
    }
    if(player == 0)
    {
        //The easy bot
        printf("Bot latwiejszy zastanawia sie...\n");
        Sleep(3000);
        if(!count_letters(tab2))
        {
            printf("Bot wybral zakrecenie kolem!\n");
            Sleep(2000);
            return 1;
        }
        else
        {
            float res = count_letters(tab2) / (float)number_of_letters_in_password;
            res *= 100;
            int random_num = rand()%100+1;
            if(random_num <= (int)res)
            {
                printf("Bot zgaduje haslo!\n");
                Sleep(2000);
                return 3;
            }
            else
            {
                if(money >= 250)
                {
                    //50%
                    random_num = rand()%2;
                    if(random_num)
                    {
                        printf("Bot wybral zakrecenie kolem!\n");
                        Sleep(2000);
                        return 1;
                    }
                    else
                    {
                        printf("Bot wybral zakup samogloski!\n");
                        Sleep(2000);
                        return 2;
                    }
                }
                else
                {
                    printf("Bot wybral zakrecenie kolem!\n");
                    Sleep(2000);
                    return 1;
                }
            }
        }
    }
    else if(player == 1)
    {
        //The better bot
        printf("Bot trudniejszy zastanawia sie...\n");
        Sleep(3000);
        if(!count_letters(tab2))
        {
            printf("Bot wybral zakrecenie kolem!\n");
            Sleep(2000);
            return 1;
        }
        else
        {
            float res = count_letters(tab2) / (float)number_of_letters_in_password;
            res *= 100;
            int random_num = rand()%100+1;
            if(random_num <= (int)res)
            {
                printf("Bot zgaduje haslo!\n");
                Sleep(2000);
                return 3;
            }
            else
            {
                if(money >= 250)
                {
                    //50%
                    random_num = rand()%2;
                    if(random_num)
                    {
                        printf("Bot wybral zakrecenie kolem!\n");
                        Sleep(2000);
                        return 1;
                    }
                    else
                    {
                        printf("Bot wybral zakup samogloski!\n");
                        Sleep(2000);
                        return 2;
                    }
                }
                else
                {
                    printf("Bot wybral zakrecenie kolem!\n");
                    Sleep(2000);
                    return 1;
                }
            }
        }
    }
    else if(player == 2)
    {
        scanf("%d", &number);
        getchar();
    }
    return number;
}

char choose_letter(const char tab[], enum LETTER kind, enum PLAYER_TYPE player, char list_of_letters[], char list_of_wrong_letters[])
{
    char letter;
    char vowels[] = "aeiouy";
    char consonants[] = "bcdfghjklmnpqrstvwxz";
    if(player == 2)
    {
        if(kind == 0) printf("Podaj samogloske: ");
        if(kind == 1) printf("Podaj spolgloske: ");
        scanf("%c", &letter);
        scanf("%*c");
    }
    if(kind == 0)
    {
        if(player == 0)
        {
            //The dumber bot, guesses from the possible numbers array, here the vowels
            printf("Bot latwiejszy zastanawia sie...\n");
            Sleep(3000);
            int random_num = rand()%6;
            printf("Bot wybral samogloske: %c\n", vowels[random_num]);
            Sleep(2000);
            letter = vowels[random_num];
        }
        else if(player == 1)
        {
            //The smarter bot, guesses from the possible numbers array, but without the already guessed by others
            //and the ones uncovered in the password
            printf("Bot trudniejszy zastanawia sie...\n");
            Sleep(3000);
            while(1)
            {
                int random_num = rand()%6;
                int possible = 1;
                for(int i = 0; list_of_letters[i] != '#'; i++)
                {
                    if(vowels[random_num] == list_of_letters[i]) possible = 0;
                }
                for(int i = 0; list_of_wrong_letters[i] != '#'; i++)
                {
                    if(vowels[random_num] == list_of_wrong_letters[i]) possible = 0;
                }
                for(int i = 0; tab[i] != '\0'; i++)
                {
                    if(vowels[random_num] == tab[i]) possible = 0;
                }
                if(possible)
                {
                    printf("Bot wybral samogloske: %c\n", vowels[random_num]);
                    Sleep(2000);
                    letter = vowels[random_num];
                    break;
                }
            }
        }
    }
    else if(kind == 1)
    {
        if(player == 0)
        {
            //The dumber bot, guesses consonants
            printf("Bot latwiejszy zastanawia sie...\n");
            Sleep(3000);
            int random_num = rand()%20;
            printf("Bot wybral spolgloske: %c\n", consonants[random_num]);
            Sleep(2000);
            letter = consonants[random_num];
        }
        else if(player == 1)
        {
            //The smarter bot, the same rules as for vowels apply
            printf("Bot trudniejszy zastanawia sie...\n");
            Sleep(3000);
            while(1)
            {
                int random_num = rand()%20;
                int possible = 1;
                for(int i = 0; list_of_letters[i] != '#'; i++)
                {
                    if(consonants[random_num] == list_of_letters[i]) possible = 0;
                }
                for(int i = 0; list_of_wrong_letters[i] != '#'; i++)
                {
                    if(consonants[random_num] == list_of_wrong_letters[i]) possible = 0;
                }
                for(int i = 0; tab[i] != '\0'; i++)
                {
                    if(consonants[random_num] == tab[i]) possible = 0;
                }
                if(possible)
                {
                    printf("Bot wybral spolgloske: %c\n", consonants[random_num]);
                    Sleep(2000);
                    letter = consonants[random_num];
                    break;
                }
            }
        }
    }
    return letter;
}

//My functions
int spin_the_wheel(int rewards[])
{
    int size = 0;
    for(int i = 0; rewards[i]>-3 && rewards[i]<1000; i++) size++;

    int random_number = rand()%size;
    return rewards[random_number];

}

int is_letter(char letter)
{
    if(tolower(letter)>='a' && tolower(letter)<='z') return 1;
    else return 0;
}

int in_password(char letter, char password[])
{
    int size = 0, exists = 0;
    for(int i = 0; password[i] != '\0'; i++) size++;
    for(int i = 0; i < size; i++)
    {
        if(tolower(password[i]) == tolower(letter))
        {
            exists = 1;
            break;
        }
    }
    return exists;
}

int append_list(char letter, char list_of_letters[], int index)
{
    list_of_letters[index] = letter;
    return 1;
}

int in_list(char letter, char list_of_letters[])
{
    int size = 0, exists = 0;
    for(int i = 0; list_of_letters[i] != '#'; i++) size++;
    for(int i = 0; i < size; i++)
    {
        if(tolower(list_of_letters[i]) == tolower(letter))
        {
            exists = 1;
            break;
        }
    }
    return exists;
}

int is_vowel(char letter)
{
    char list_of_vowels[] = "aeiouy";
    int its_a_vowel = 0;
    for(int i = 0; list_of_vowels[i] != '\0'; i++)
    {
        if(tolower(letter) == list_of_vowels[i]) its_a_vowel = 1;
    }
    return its_a_vowel;
}

int is_consonant(char letter)
{
    char list_of_consonants[] = "bcdfghjklmnpqrstvwxz";
    int its_a_consonant = 0;
    for(int i = 0; list_of_consonants[i] != '\0'; i++)
    {
        if(tolower(letter) == list_of_consonants[i]) its_a_consonant = 1;
    }
    return its_a_consonant;
}

int is_valid_choice(int number)
{
    if(number > 0 && number < 3) return 1;
    else return 0;
}
