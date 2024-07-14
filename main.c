#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORD_LENGTH 10
#define TYPES 4
#define UPPER 1
#define LOWER 6
#define NUM 1
#define SYM 2

void uppercase()
{
    int temp = rand() % ('Z' - 'A' + 1);
    putchar(temp + 'A');
}

void lowercase()
{
    int temp = rand() % ('z' - 'a' + 1);
    putchar(temp + 'a');
}

void number()
{
    int temp = rand() % ('9' - '0' + 1);
    putchar(temp + '0');
}

void symbol()
{
    int temp = rand() % ('$' - '!' + 1);
    putchar(temp + '!');
}

int main()
{
    int length = 0;
    int tries = 0; // for testing and optimizing
    unsigned counts[TYPES] = { LOWER, SYM, NUM, UPPER };
    void (*functions[TYPES])() = {  &lowercase, &symbol, &number, &uppercase };
    srand((unsigned) time(NULL));

    
    while (length < PASSWORD_LENGTH) 
    {
        tries++;
        int ind = (rand() % TYPES);
        while (!counts[ind])
        {
            ind = (ind + 1) % TYPES; // eliminates O(random) by predictably incrementing temp
            tries++;
        }
        if (counts[ind])
        {
            counts[ind]--;
            functions[ind]();
            length++;
        }
    }
    printf("\nTries: %d", tries);

    return 0;
}