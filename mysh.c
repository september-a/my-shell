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
        "cat",
        "cp",
        "rm",
        "mkdir",
        "rmdir",
        NULL
    };

    char* my_command = my_line[0];

    for (i = 0; cmd_options[i] != NULL; i++) {
        if (strcmp(my_command, cmd_options[i]) == 0) {
            // Command found!
            return my_command;
        } 
    }
    if (strstr(my_command, "PS1") != 0) {
        my_command = "PS1";
        return my_command;
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

int checkOption(char **my_line){

    char *optionVal = "-n";

    if (my_line[1] == optionVal){
        printf("option found\n");
        return 1;
    }
    else{
        return 0;
    }
}

void my_echo(char **my_line){
    // My echo function
    
    int i;
    int option_flag = checkOption(my_line);

    if (option_flag == 0){
        for (i = 1; my_line[i] != NULL; ++i)
        {
            printf("%s ", my_line[i]);
        }
        printf("\n");
    }
    else{
        printf("option raised\n");
    }
    
}

void removeNL(char **my_line){
    int i;

    for (i = 0; my_line[i] != NULL; ++i) {
        // Find the newline character and replace it with null terminator
        char *newline = strchr(my_line[i], '\n');
        if (newline != NULL)
            *newline = '\0';
    }
}

int my_PS1(char **my_line, char **prompt){
    int i;
    int total_length = 1;

    // Calculate the total length needed for line_str
    for (i = 0; my_line[i] != NULL; i++) {
        total_length += strlen(my_line[i]);
    }

    char line_str[total_length];

    for (i = 0; my_line[i] != NULL; i++) {
        strcat(line_str, my_line[i]);
        strcat(line_str, " ");
    }

    int equals_flag = 0;
    char prompt_str[total_length];

    for (i = 0; line_str[i]; i++) {
        
        if (equals_flag == 1 && line_str[i] != '"') {
            strncat(prompt_str, &line_str[i], 1);
        }
        if (line_str[i] == '=') {
            equals_flag = 1;
        }

    }

    *prompt = strdup(prompt_str);

    //printf("PS1 will be performed on: %s\n", *prompt);

    return 0;
}

char* getFilename(char *filename){
    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (file == NULL) {
        printf("Error opening file");
        return "NA";
    }
    else
    {
        return filename;
    }
    
}

void my_cat(char **my_line){
    char* filename = my_line[1];
    filename = getFilename(filename);

    if (strcmp(filename, "NA") != 0){
        FILE *file = fopen(filename, "r"); // Open the file for reading
        char buffer[1024]; // Buffer to hold data read from the file

        // Read and print the contents of the file
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }

        fclose(file); // Close the file when done
        printf("\n");
    }

}

void my_rm(char **my_line){
    char* filename = my_line[1];
    filename = getFilename(filename);

    printf("\nrm will be done on this: %s", filename);

    if (strcmp(filename, "NA") != 0) {
        // do something

    }

}

void my_cp(char **my_line){
    char* source = my_line[1];
    source = getFilename(source);
    char* dest = my_line[2];
    dest = getFilename(dest);

    printf("\ncp will be done on this %s and this %s", source, dest);

    if ((strcmp(source, "NA") != 0) && (strcmp(dest, "NA"))) {
        // do something

    }

}

void execute(char **my_line, char *my_command, int *state_flag, char **prompt_value){

    if (strcmp(my_command, "echo") == 0){
        my_echo(my_line);
    }
    else if (strcmp(my_command, "PS1") == 0){
        my_PS1(my_line, prompt_value);
    }
    else if (strcmp(my_command, "cat") == 0) {
        my_cat(my_line);
    }
    else if (strcmp(my_command, "cp") == 0) {
        my_cp(my_line);
    }
    else if (strcmp(my_command, "rm") == 0) {
        my_rm(my_line);
    }
    else if (strcmp(my_command, "exit") == 0){
        *state_flag = -1;
    }
    else
    {
        printf("Command not found\n");
    }

    printf("\n");

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
    
    int state;
    int *state_p = &state;
    char input[256]; // Assuming a maximum input length of 256 characters

    char *line[MAX_ARG];

    char *token;
    char *command;

    char *prompt = "$ ";

    while (state != -1) {
        state = 0;
        printf("%s ", prompt);

        // READ
        fgets(input, sizeof(input), stdin); 
        token = strtok(input, " ");

        // PARSE
        parse(token, line);
        removeNL(line);
        command = getCommandin(line);

        // EXECUTE
        //print(line);
        execute(line, command, state_p, &prompt);      

    }

    return 0;
}

