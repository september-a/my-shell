#include <stdio.h>
#include <string.h>

#define MAX_ARG 20


void parse(char *token, char **my_line){
    int i;

    // from code in assignment description
    for(i = 0; token != 0 && i < (MAX_ARG- 1); ++i)
    {
        my_line[i] = token;
        token = strtok(0, " ");
    }
    my_line[i] = 0;

}

void execute(char **my_line){
    int i;

    for(i = 0; my_line[i]; ++i)
    {
        printf("my_line[%d] = %s\n", i, my_line[i]);
    }
}

int main()
{
    printf("Welcome to My Shell!\n");
    printf("CS 390 Programming Assignment 1 | September Abbott\n\n");
    
    // begin loop
        // read
        // parse
        // execute
    
    // end loop
    
    char *token;
    int state = 0;
    char input[256]; // Assuming a maximum input length of 256 characters
    char *line[MAX_ARG];

    while (state != 1) {
        printf("Enter input: ");
        fgets(input, sizeof(input), stdin); 

        if (strcmp(input, "exit\n") == 0) {
            state = 1;
            break; // Exit the loop
        }

        // Read
        token = strtok(input, " ");
        parse(token, line);
        execute(line);

    }

    return 0;
}

