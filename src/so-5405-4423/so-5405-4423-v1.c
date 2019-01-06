#include <stdio.h>
#include <string.h>

char line[1001]; // The line supports up to a 1000 characters
char lines[11][1001]; // An array of lines (up to 10 lines where each line is a 1000 characters max)
char info[100]; // Holds extra info provided by user

char * extra_info(
        char string_1[],
        char string_2[],
        char string_3[],
        char string_4[],
        char string_5[]
    );

int main(void){

    int 
    i, // Line number
    j; // Length of the line
    char result[100], text[100];
    FILE *file;

    strcpy(text, "String No."); // The default text

    file = fopen("test.txt", "w+"); // Open the file for reading and writing

    for(i = 0; i < 10; i++){ // Loop to create a line.

        if(i != 9){ // If the line is NOT at the 10th string

            sprintf(result, "%s%d, ", text, i); // Format the text and store it in result

        }
        else{

            sprintf(result, "%s%d ", text, i); // Format the text and store it in result            

        }

        extra_info(
            "st",
            "nd",
            "rd",
            "th",
            "th"
        );

        strncat(line, info, 100); // Append the extra info at the end of each line        

        printf("%s", result); // Display the result variable to the screen

        strncat(line, result, 15); // Concatenate all strings in one line

    }

    strncat(line, "\n\n", 2); // Add a new-line character at the end of each line

    for(j = 0; j < 10; j++){ // Now loop to change the line

        strcpy(lines[i], line); // Copy the line of text into each line of the array

        fputs(lines[i], file); // Put each line into the file        

    }

    fclose(file);  

    return 0;
}

char * extra_info( // Append user defined and predefined info at the end of a line
        char string_1[],
        char string_2[],
        char string_3[],
        char string_4[],
        char string_5[]
    ){
        char text[100]; // A variable to hold the text

        /* Append a default text into each strings 
        and concatenate them into one line */

        sprintf(text, " 1%s", string_1);
        strncat(line, text, 100);

        sprintf(text, ", 2%s", string_2);
        strncat(line, text, 100);

        sprintf(text, ", 3%s", string_3);
        strncat(line, text, 100);

        sprintf(text, ", 4%s", string_4);
        strncat(line, text, 100);

        sprintf(text, ", 5%s.", string_5);
        strncat(line, text, 100);

        strcpy(info, line); // Copies the line into the info global variable

        return line;
}
