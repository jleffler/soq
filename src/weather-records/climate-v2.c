/**
 * climate.c
 *
 * Performs analysis on climate data provided by the
 * National Oceanic and Atmospheric Administration (NOAA).
 *
 * Input:    Tab-delimited file(s) to analyze.
 * Output:   Summary information about the data.
 *
 * Compile:  run make
 *
 * Example Run:      ./climate data_tn.tdv data_wa.tdv
 *
 * Opening file: data_tn.tdv
 * Opening file: data_wa.tdv
 * States found: TN WA
 * -- State: TN --
 * Number of Records: 17097
 * Average Humidity: 49.4%
 * Average Temperature: 58.3F
 * Max Temperature: 110.4F on Mon Aug  3 11:00:00 2015
 * Min Temperature: -11.1F on Fri Feb 20 04:00:00 2015
 * Lightning Strikes: 781
 * Records with Snow Cover: 107
 * Average Cloud Cover: 53.0%
 * -- State: WA --
 * Number of Records: 48357
 * Average Humidity: 61.3%
 * Average Temperature: 52.9F
 * Max Temperature: 125.7F on Sun Jun 28 17:00:00 2015
 * Min Temperature: -18.7F on Wed Dec 30 04:00:00 2015
 * Lightning Strikes: 1190
 * Records with Snow Cover: 1383
 * Average Cloud Cover: 54.5%
 *
 * TDV format:
 *
 * CA» 1428300000000»  9prcjqk3yc80»   93.0»   0.0»100.0»  0.0»95644.0»277.58716
 * CA» 1430308800000»  9prc9sgwvw80»   4.0»0.0»100.0»  0.0»99226.0»282.63037
 * CA» 1428559200000»  9prrremmdqxb»   61.0»   0.0»0.0»0.0»102112.0»   285.07513
 * CA» 1428192000000»  9prkzkcdypgz»   57.0»   0.0»100.0»  0.0»101765.0» 285.21332
 * CA» 1428170400000»  9prdd41tbzeb»   73.0»   0.0»22.0»   0.0»102074.0» 285.10425
 * CA» 1429768800000»  9pr60tz83r2p»   38.0»   0.0»0.0»0.0»101679.0»   283.9342
 * CA» 1428127200000»  9prj93myxe80»   98.0»   0.0»100.0»  0.0»102343.0» 285.75
 * CA» 1428408000000»  9pr49b49zs7z»   93.0»   0.0»100.0»  0.0»100645.0» 285.82413
 *
 * Each field is separated by a tab character \t and ends with a newline \n.
 *
 * Fields:
 *      state code (e.g., CA, TX, etc),
 *      timestamp (time of observation as a UNIX timestamp),
 *      geolocation (geohash string),
 *      humidity (0 - 100%),
 *      snow (1 = snow present, 0 = no snow),
 *      cloud cover (0 - 100%),
 *      lightning strikes (1 = lightning strike, 0 = no lightning),
 *      pressure (Pa),
 *      surface temperature (Kelvin)
 */

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_STATES 50

/* TODO: Add elements to the climate_info struct as necessary. */
struct climate_info
{
    char code[3];
    unsigned int num_records;
    long long lo_millitime;
    long long hi_millitime;
    double humidity;
    double snow;
    double cloud;
    double lightning;
    double temperature;
    double lo_temp_reading;
    double hi_temp_reading;
    unsigned long int lo_temp_timestamp;
    unsigned long int hi_temp_timestamp;
};

void analyze_file(FILE *file, struct climate_info *states[], int num_states);
void print_report(struct climate_info *states[], int num_states);

int main(int argc, char *argv[])
{
    /* TODO: fix this conditional. You should be able to read multiple files. */
    if (argc < 2)
    {
        printf("Usage: %s tdv_file1 tdv_file2 ... tdv_fileN\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Let's create an array to store our state data in. As we know, there are
     * 50 US states. */
    struct climate_info *states[NUM_STATES] = { NULL };

    int i;
    for (i = 2; i < argc; ++i)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            fprintf(stderr, "%s: error opening file %s for reading\n", argv[0], argv[i]);
            continue;
        }
        analyze_file(fp, states, NUM_STATES);
        fclose(fp);
    }

    /* Now that we have recorded data for each file, we'll summarize them: */
    print_report(states, NUM_STATES);

    return 0;
}

static
int returnStatement(struct climate_info **states, char code1[3], int currentStates)
{
    int rank = 0;
    while (rank < currentStates)
    {
        if (strcmp(states[rank]->code, code1) == 0)
        {
            return rank;
        }
        rank++;
    }
    return -1;
}

static
int countStates(struct climate_info **states)
{
    int num = 0;
    while (num < NUM_STATES && states[num] != NULL)
    {
        num++;
    }
    return num;
}

void analyze_file(FILE *file, struct climate_info **states, int num_states)
{
    const int line_sz = 100;
    char line[line_sz];
    int currentStates = countStates(states);
    while (fgets(line, line_sz, file) != NULL)
    {
        /* TODO: We need to do a few things here:
         *
         *       * Tokenize the line.
         *       * Determine what state the line is for. This will be the state
         *         code, stored as our first token.
         *       * If our states array doesn't have a climate_info entry for
         *         this state, then we need to allocate memory for it and put it
         *         in the next open place in the array. Otherwise, we reuse the
         *         existing entry.
         *       * Update the climate_info structure as necessary.
         */

        char *foundCode = strtok(line, "\t");
        int rankOfState = returnStatement(states, foundCode, currentStates);
        if (rankOfState == -1)
        {
            states[currentStates] = (struct climate_info *)malloc(sizeof(struct climate_info) * num_states);
            strcpy(states[currentStates]->code, foundCode);
            states[currentStates]->num_records = 1;

            char *currentTimeStamp = strtok(NULL, "\t");
            unsigned long TIMESTAMP;
            sscanf(currentTimeStamp, "%lu", &TIMESTAMP);
            printf("%lu\n", TIMESTAMP);

            char *currentGeol = strtok(NULL, "\t");
            printf("%s\n", currentGeol);

            char *currentHumidity = strtok(NULL, "\t");
            double HUMIDITY;
            sscanf(currentHumidity, "%lf", &HUMIDITY);
            printf("%lf\n", HUMIDITY);

            char *currentSnow = strtok(NULL, "\t");
            float SNOW;
            sscanf(currentSnow, "%f", &SNOW);
            printf("%f\n", SNOW);

            char *currentCloud = strtok(NULL, "\t");
            double CLOUD;
            sscanf(currentCloud, "%lf", &CLOUD);
            printf("%lf\n", CLOUD);

            char *currentLightning = strtok(NULL, "\t");
            float LIGHTNING;
            sscanf(currentLightning, "%f", &LIGHTNING);
            printf("%f\n", LIGHTNING);

            char *currentPressure = strtok(NULL, "\t");
            double PRESSURE;
            sscanf(currentPressure, "%lf", &PRESSURE);
            printf("%lf\n", PRESSURE);

            char *currentTemp = strtok(NULL, "\t\n");
            double TEMP;
            sscanf(currentTemp, "%lf", &TEMP);
            printf("%lf\n", TEMP);

            printf("\n");
            currentStates++;
        }
        else
        {
            (*(states + rankOfState))->num_records += 1;
        }
    }
}

void print_report(struct climate_info *states[], int num_states)
{
    printf("States found: ");
    int i;
    for (i = 0; i < num_states; ++i)
    {
        if (states[i] != NULL)
        {
            struct climate_info *info = states[i];
            printf("%s ", info->code);
        }
    }
    printf("\n");

    /* TODO: Print out the summary for each state. See format above. */
}
