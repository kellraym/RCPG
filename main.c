#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 8
#define PASSWORD_LENGTH 10
#define TYPES 4
#define UPPER 1
#define LOWER 6
#define NUM 1
#define SYM 2

int get_string_length(char *s)
{
    size_t length = 0;
    while (s[length + 1] != '\0')
    {
        length++;
    }
    return length;
}

int int_from_string(char *s)
{
    int length = get_string_length(s);
    int val = 0;
    int factor = 1;
    while (length >= 0)
    {
        val += (s[length--] - '0') * factor;
        factor *= 10;
    }
    return val;
}

int get_input_num(char *s)
{
    char user_in[BUFFER_SIZE];
    char c;
    int i;
    goto first_attempt;
    start_input:
        c = getchar(); // on failure to provide numeric char getchar clears previous newline from buffer
        first_attempt:
            i = 0;
            printf("%s", s);
            while ((c = getchar()) != '\n')
            {
                if (c >= '0' && c <= '9')
                {
                    user_in[i++] = c;
                }
                else
                {
                    printf("Please enter a number\n");
                    goto start_input;
                }

            }
    user_in[i] = '\0';
    printf("user_in: %d\n", int_from_string(user_in));
    return 1;
}


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

void get_counts(unsigned counts[TYPES])
{
    char *user_in[BUFFER_SIZE];
    char c;
    int i = 0;

    printf("Welcome to Ray's Cool Password Generator!\n");
    // call get_input_num next

}

int main()
{
    int length = 0;
    int tries = 0; // for testing and optimizing
    unsigned counts[TYPES] = { LOWER, SYM, NUM, UPPER };
    void (*functions[TYPES])() = {  &lowercase, &symbol, &number, &uppercase };
    srand((unsigned) time(NULL));
    get_input_num("enter a number: ");
    
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