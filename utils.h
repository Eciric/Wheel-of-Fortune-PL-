#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

//Enums required by the task
enum ACTION
{
    SPIN_THE_WHEEL = 1,
    BUY_VOWEL,
    GUESS,
    INCORRECT_ACTION
};

enum LETTER
{
    VOWEL,
    CONSONANT
};

enum PLAYER_TYPE
{
    COMPUTER_PLAYER_1,
    COMPUTER_PLAYER_2,
    HUMAN_PLAYER
};

//Functions required by the task
int count_letters(const char tab[]);
void guess_puzzle(const char tab[], const char category[], char tab2[], enum PLAYER_TYPE, char tab3[]);
enum ACTION choose_action(const char tab[], int money, enum PLAYER_TYPE, char tab2[]);
char choose_letter(const char tab[], enum LETTER, enum PLAYER_TYPE, char list_of_letters[], char list_of_wrong_letters[]);

//My own functions
int spin_the_wheel(int rewards[]);
int is_letter(char letter);
int in_password(char letter, char password[]);
int in_list(char letter, char list_of_letters[]);
int append_list(char letter, char list_of_letters[], int index);
int is_vowel(char letter);
int is_consonant(char letter);

#endif
