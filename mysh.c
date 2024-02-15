#include <stdio.h>
#include <string.h>

#define MAX_ARG 20


void print(char **my_line){
    int i;

    for(i = 0; my_line[i]; ++i)
    {
        printf("my_line[%d] = %s\n", i, my_line[i]);
    }
}

char* getCommandin(char **my_line){

    int i;

    char* cmd_options[] = {
        "echo",
        "exit",
        NULL
    };

    char* my_command = my_line[0];

    for (i = 0; cmd_options[i] != NULL; i++) {
        if (strcmp(my_command, cmd_options[i]) == 0) {
            printf("command found\n");
            return my_command;
        }
    }

    return "NA";
}

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

int main()
{
    printf("Welcome to My Shell!\n");
    printf("CS 390 Programming Assignment 1 | September Abbott\n\n");
    
    // begin loop
        // read
        // parse
        // execute
    
    // end loop
    
    int state = 0;
    char input[256]; // Assuming a maximum input length of 256 characters

    char *line[MAX_ARG];
    char *options[MAX_ARG];
    char *arguments[MAX_ARG];

    char *token;
    char *command;

    while (state != 1) {
        printf("Enter input: ");

        // READ
        fgets(input, sizeof(input), stdin); 

        if (strcmp(input, "exit\n") == 0) {
            state = 1;
            break; // Exit the loop
        }
        token = strtok(input, " ");

        // PARSE
        parse(token, line);
        command = getCommandin(line);

        // EXECUTE
        print(line);

        printf("my command is %s\n", command);

    }

    return 0;
}

