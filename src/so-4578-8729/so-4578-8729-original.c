/*
 * License: GPLv3
 *
 * File: main.c
 *
 * Description: A program.
 *
 * Author:  Brandon Authier (hblkr)
 * Date:    6 Aug 2017
 * Version: 1.0
 *
 */

// Includes for program to run
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

// Global debug
bool DEBUG = false;

unsigned long hash(unsigned char *str);
bool getWord(char* line, int* idx, unsigned char* word);
void processFile(FILE* textFp);

/* A djb2 hash function sourced online.
 */

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != '\0')
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

/*
 * Using a file pointer, get the first word and then pass a copy of the word
 * back
 *
 * @returns: a boolean of true when word is built
 *
 * TODO: Find issue in here causing memory error
 *
 */
bool getWord(char* line, int* idx, unsigned char* word)
{
    int wordIdx = 0;

    // Build word character by character
    for ( ; line[*idx] != '\0'; *idx = (*idx + 1))
    {
        if (isalpha(line[*idx]) || (line[*idx] == '-'))
        {
            word[wordIdx++] = tolower(line[*idx]);
        }
        else if (isspace(line[*idx]))
        {
            *idx += 1;
            return true;
        }
    }

    return true;
}

/*
 * Process file. Tokenize each line and process each word.
 *
 * TODO: Process file.
 */
void processFile(FILE* textFp)
{
    // Variables to hold:
    //   a line for text
    //   a word once it is parsed
    //   an index to keep track of the line
    char line[1024] = "";
    unsigned char* word = malloc(sizeof(unsigned char) * 50);
    int* lineIdx = malloc(sizeof(int));
    int lineCount = 1;

    // Set the line index to keep track of the line
    *lineIdx = 0;

    while (fgets(line, sizeof(line), textFp) != NULL)
    {
        // Get line character Count
        int charcount = 0;
        int wordCount = 1;

        for(int m = 0; line[m] != '\0'; m++)
        {
            // By counting spaces, you can get a rough estimate of how many words
            // are in each line. (totalSpaces + 1)
            if ((line[m] == ' ') && (line[m - 1] != ' '))
            {
                 wordCount++;
            }

            if(line[m] != '\n' && line[m] != '\r')
            {
                charcount++;
            }
            else
            {
                line[m] = '\0';
            }
        }

        if (DEBUG == true)
        {
            fprintf(stdout, "line %d:\n", lineCount);
            fprintf(stdout, "  words in line: %d\n", wordCount);
            fprintf(stdout, "  charcount: %d\n", charcount);
            fprintf(stdout, "  lineIdx: %d\n", *lineIdx);
            fprintf(stdout, "  value: \"%s\"\n\n", line);
        }

        // Get word
        while (*lineIdx < (charcount - 1))
        {
            // Sanitize word
            for (int i = 0; i < 50; i++)
            {
                word[i] = '\0';
            }

            getWord(line, lineIdx, word);
            unsigned long hash_output = hash(word);

            if (DEBUG == true)
            {
                fprintf(stdout, "key: %10ld,\t", hash_output);
                fprintf(stdout, "value: %8s,\t", word);
                fprintf(stdout, "lineIdx: %2d\n", *lineIdx);
            }
        } // End while for word

        if (DEBUG == true) { fprintf(stdout, "\n========\n\n"); }

        // Reset line index to 0 for new line
        *lineIdx = 0;
        lineCount++;
    } // End while for line

    if (DEBUG == true) { if (feof(textFp)) { fprintf(stderr, "Reached FEOF.\n"); } }

    // Free pointers
    free(lineIdx);
    free(word);
}


// Main
int main (int argc, char* argv[])
{
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //        VERIFY COMMAND LINE ARGUMENTS NECESSARY FOR PROGRAM
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // User did not pass in any argument
    if (argc == 1)
    {
        fprintf(stderr, "usage: main afile.txt\n");
        exit(-1);
    }

    // Grab text file, possibly turn on debug, and ignore other arguments
    if (argc >= 3)
    {
        // For debug purposes
        if (strcmp("-d", argv[2]) == 0)
        {
            DEBUG = true;
            fprintf(stdout, "+++++++++++++++++++++++++++++++++++++++\n");
            fprintf(stdout, "+            [DEBUGGING ON]           +\n");
            fprintf(stdout, "+++++++++++++++++++++++++++++++++++++++\n\n");
        }
    }


  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //        PROCESS PASSED IN TEXT FILE
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // Open file for reading
    FILE* fp = fopen(argv[1], "r+");

    // If fp is NULL, file does not exist
    if (fp == 0)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(1);
    }
    if (DEBUG == true) { fprintf(stdout, "File exists.\n"); }
    if (DEBUG == true)
    {
        fprintf(stdout, "\n");
        fprintf(stdout, "================================================================================\n");
    }

    // Process file
    processFile(fp);

    // Close file pointer
    if (fclose(fp) != 0)
    {
        fprintf(stderr, "File did not close.\n");
    }
    if (DEBUG == true) { fprintf(stdout, "File closed.\n"); }
    if (DEBUG == true)
    {
        fprintf(stdout, "================================================================================\n");
        fprintf(stdout, "\n");
    }


  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //        FREE ALL MEMORY THAT HASN'T BEEN FREED YET
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    exit(0);
}
