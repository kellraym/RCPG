#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 8
#define TYPES 4

int sum(unsigned *nums, int length)
{
    int total = 0;
    for (int i = 0; i < length; i++)
    {
        total += nums[i];
    }
    return total;
}

int get_string_length(char *s)
{
    int length = 0;
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
        c = getchar(); // on failure to provide numeric char, getchar clears previous newline from buffer
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
    return int_from_string(user_in);
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

// TODO: refactor use more widely accepted symbols
void symbol()
{
    int temp = rand() % ('$' - '!' + 1);
    putchar(temp + '!');
}

void get_counts(unsigned counts[TYPES], char *requests[TYPES])
{
    for (int i = 0; i < TYPES; i++)
    {
        counts[i] = get_input_num(requests[i]);
    }
}

int main()
{
    int password_length; // length of final password
    int i = 0;
    int tries = 0; // for testing and optimizing
    unsigned counts[TYPES];
    void (*functions[TYPES])() = {  &symbol, &number, &uppercase, &lowercase };
    char *count_requests[] = {
        "Enter the number of special characters: ",
        "Enter the number of numbers: ",
        "Enter the number of uppercase letters: ",
        "Enter the number of lowercase letters: "
    };
    srand((unsigned) time(NULL));

    get_counts(counts, count_requests);
    password_length = sum(counts, TYPES);
    
    while (i < password_length) 
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
            i++;
        }
    }
    printf("\nTries: %d", tries);

    return 0;
}