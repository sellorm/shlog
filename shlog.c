#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*
Shell Logger - Simple shell script loggin utility
ALL < trace < DEBUG < INFO < WARN < ERROR < FATAL < OFF.
0   < 1     < 2     < 3    < 4    < 5     < 6     < 7
*/

// Usage
void usage(char* progname)
{
   printf("%s requires exactly 2 arguments. A log level and a message\n", progname);
}

// return the numeric log level
int numloglvl(char* leveltext)
{
    if ((strcmp(leveltext, "all") == 0)  || (strcmp(leveltext, "ALL") == 0) ) {
        return 0;
    } else if ((strcmp(leveltext, "trace") == 0)  || (strcmp(leveltext, "TRACE") == 0) ) {
        return 1;
    } else if ((strcmp(leveltext, "debug") == 0)  || (strcmp(leveltext, "DEBUG") == 0) ) {
        return 2;
    } else if ((strcmp(leveltext, "info") == 0)  || (strcmp(leveltext, "INFO") == 0) ) {
        return 3;
    } else if ((strcmp(leveltext, "warn") == 0)  || (strcmp(leveltext, "WARN") == 0) ) {
        return 4;
    } else if ((strcmp(leveltext, "error") == 0)  || (strcmp(leveltext, "ERROR") == 0) ) {
        return 5;
    } else if ((strcmp(leveltext, "fatal") == 0)  || (strcmp(leveltext, "FATAL") == 0) ) {
        return 6;
    } else if ((strcmp(leveltext, "off") == 0) || (strcmp(leveltext, "OFF") == 0) ) {
        return 7;
    } else {
        return 999;
    }
}
    

// Main
int main(int argc, char **argv)
{
    // Check that some args have been set
    if(argv[1] == NULL)
    {
        printf("No input defined\n");
        usage(argv[0]);
        return 1;
    }

    // Check that not more than 2 args have been set
    if(argv[3] != NULL)
    {
        printf("Error: Too many arguments.\n");
        usage(argv[0]);
        return 1;
    }

    // Check for a defined log level
    char* ENVLOGLEVEL = getenv("LOGLEVEL");
    int loglevel;
    if( ENVLOGLEVEL == NULL)
    {
        loglevel = numloglvl("info");
        //printf("LOGLEVEL not set. Defaulting to INFO (%d)\n", loglevel);
        
    } else {
        loglevel = numloglvl(ENVLOGLEVEL);
        if( loglevel == 999)
        {
            printf("Error: invalid LOGLEVEL. Check LOGLEVEL setting ands try again.\n");
            return 2;
        }
        // printf("LOGLEVEL is: %s (%d)\n", ENVLOGLEVEL, loglevel);
    }

    // variables to store date and time components
    int hours, minutes, seconds, day, month, year;

    // time_t is arithmetic time type
    time_t now;

    // Obtain current time
    // time() returns the current time of the system as a time_t value
    time(&now);

    // localtime converts a time_t value to calendar time and
    // returns a pointer to a tm structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);
 
    hours = local->tm_hour;          // get hours since midnight (0-23)
    minutes = local->tm_min;         // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;         // get seconds passed after minute (0-59)
 
    day = local->tm_mday;            // get day of month (1 to 31)
    month = local->tm_mon + 1;       // get month of year (0 to 11)
    year = local->tm_year + 1900;    // get year since 1900

    // convert the msg loglevel to uppercase


    // word to convert to uppercase
    char* input_msg_level = argv[1];
    int len = strlen(input_msg_level); 
    char upper_msg_level[len];

    // Loop
    int i;
    for (i = 0; i < len; i++)
    { 
        upper_msg_level[i] = toupper(input_msg_level[i]); 
    }

    // print the output
    int msglevel = numloglvl(argv[1]);
    if (msglevel >= loglevel)
    {
        printf("%02d-%02d-%d %02d:%02d:%02d [ %5s ] %s\n", year, month, day, hours, minutes, seconds, upper_msg_level, argv[2]);
    }
    return 0;
}

