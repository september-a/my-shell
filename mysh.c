#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#define MAX_ARG 20
#define BUFFERSIZE 2048


void print(char **my_line){
    // print for debugging
    int i;

    for(i = 0; my_line[i]; ++i)
    {
        printf("my_line[%d] = %s\n", i, my_line[i]);
    }
}

char* getCommandin(char **my_line){

    int i;

    // Array of commands that can be used
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

    return my_line[0];
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
    // not fully functional
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

    // option flag check - not fully functional
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

    // Inspired from class handout
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

    // instantiate line_str
    char line_str[total_length];

    // cp contents in my_line to line_str
    for (i = 0; my_line[i] != NULL; i++) {
        strcat(line_str, my_line[i]);
        strcat(line_str, " ");
    }


    // put values after equals into prompt_str - excluding quotes
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

    // update prompt
    *prompt = strdup(prompt_str);

    //printf("PS1 will be performed on: %s\n", *prompt);

    return 0;
}

char* checkFilename(char *filename){
    // checks if file exists. Used in instructions where a specific file path is needed. 

    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (file == NULL) {
        printf("Error opening file");
        fclose(file);
        return "NA";
    }
    else
    {
        fclose(file);
        return filename;
    }
    
    
}

void my_cat(char **my_line){
    char* filename = my_line[1];
    filename = checkFilename(filename);

    if (strcmp(filename, "NA") != 0){
        FILE *file = fopen(filename, "r"); // Open the file for reading
        char buffer[BUFFERSIZE]; // Buffer to hold data read from the file

        // Read and print the contents of the file
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }

        fclose(file); // Close the file when done
        printf("\n");
    }

}

char* createFile(char *filename){
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file");
        fclose(file);
        return "NA";
    }
    else
    {
        fclose(file);
        return filename;
    }
    fclose(file);
}

void my_rm(char **my_line){
    char* filename = my_line[1];
    filename = checkFilename(filename);

    //printf("\nrm will be done on this: %s", filename);

    if (strcmp(filename, "NA") != 0) {
        // removing the file
        if (remove(filename) != 0) {
            printf("Error deleting the file");
        }

    }
    printf("\n");

}

void my_cp(char **my_line){

    // parsing arguments - separtating into source and destination
    char* source = my_line[1];
    source = checkFilename(source);
    char* dest = my_line[2];
    dest = createFile(dest);    // need to create file before copying to it

    // buffer to copy contents from one to the other
    char buffer[BUFFERSIZE];
    size_t bytes_read;

    //printf("\ncp will be done on this %s and this %s", source, dest);

    if ((strcmp(source, "NA") != 0) && (strcmp(dest, "NA"))) {
        FILE *file_s = fopen(source, "rb"); // Open the file for reading
        FILE *file_d = fopen(dest, "wb"); // Open the file for reading
        while ((bytes_read = fread(buffer, 1, BUFFERSIZE, file_s)) > 0) {
            fwrite(buffer, 1, bytes_read, file_d);
        }
        fclose(file_s);
        fclose(file_d);

    }

    printf("\n");

}

void my_mkdir(char **my_line) {
    //printf("my mkdir function\n");

    // making the directory
    char *directory_name = my_line[1];

    int status = mkdir(directory_name, 777);

    if (status != 0) {
        perror("Error creating directory\n");
    }

    printf("\n");
}

void my_rmdir(char **my_line) {
    const char* directory_name = my_line[1];

    // Remove the directory
    int status = rmdir(directory_name);

    if (status != 0) {
        perror("Error removing directory\n");
    }

    printf("\n");

}

int _execv(const char *path, char *const argv[]){

    int i = 0;
    for (i = 0; argv[i] != NULL; i++);

    char command[BUFFERSIZE]; 
    if (i == 1) {
        snprintf(command, sizeof(command), "%s", path);
        system(command);
    }
    else if (i == 2) {
        // If there's only one argument, construct the command without the second argument
        snprintf(command, sizeof(command), "%s %s", path, argv[1]);
        system(command);
    } else if (i == 3) {
        // If there are two arguments, construct the command with both arguments
        snprintf(command, sizeof(command), "%s %s %s", path, argv[1], argv[2]);
        system(command);
    }
    else
        printf("Improper use of myls");
        return 0;

    return 1;
}

char* find_function(char **my_line){
    // Lets find the path from PATH!
    const char *path_value = getenv("PATH");
    if (path_value == NULL) {
        fprintf(stderr, "Error: PATH environment variable not found.\n");
        return NULL;
    }
    
    // Tokenizing and searching PATH
    char *new_token = strtok(strdup(path_value), ":");
    while (new_token != NULL) {

        char *function_path = malloc(strlen(new_token) + strlen("/") + strlen(my_line[0]) + 1);
        if (function_path == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return NULL; // Return if memory allocation failed
        }
        
        strcpy(function_path, new_token);
        strcat(function_path, "/");
        strcat(function_path, my_line[0]);
       

        // Check if the file exists and is executable
        if (access(function_path, X_OK) == 0) {
            return function_path;
        }

        new_token = strtok(NULL, ":");
    }
    return NULL;

}

void execute(char **my_line, char *my_command, int *state_flag, char **prompt_value){

    // Big if statement

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
    else if (strcmp(my_command, "mkdir") == 0) {
        my_mkdir(my_line);
    }
    else if(strcmp(my_command, "rmdir") == 0) {
        my_rmdir(my_line);
    }
    else if (strcmp(my_command, "exit") == 0){
        *state_flag = -1;
    }
    else
    {
        char *path = find_function(my_line);
        if (path != NULL)
        {
            _execv(path, my_line);
        }
        else
        {
            printf("Command not found\n");
        }
        
    }

    printf("\n");

}

int main()
{
    printf("Welcome to My Shell!\n");
    printf("CS 390 Programming Assignment 1 | September Abbott\n\n");

    // Structure of Main
    // begin loop
        // read
        // parse
        // execute
    // end loop
    
    // state used for ending program upon "exit"
    int state;
    int *state_p = &state;

    // max input is the same as buffer
    char input[BUFFERSIZE];

    // a line can only have 20 arguments
    char *line[MAX_ARG];

    // tokens delimited by spaces
    char *token;

    // command (first argument is saved)
    char *command;

    // beginning prompt is $ - as stated in assignment hand out
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

