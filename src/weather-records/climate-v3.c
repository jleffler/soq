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
 * s
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_STATES 50

struct climate_info
{
    char code[3];
    unsigned long num_records;
    double humidity;
    double snow;
    double cloud;
    double lightning;
    double temperature;
    double lo_temp_reading;
    double hi_temp_reading;
    long long lo_temp_millitime;
    long long hi_temp_millitime;
};

void analyze_file(FILE *file, const char *name, struct climate_info *states[], int num_states);
void print_report(struct climate_info *states[], int num_states);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s file.tdv [file.tdv ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Let's create an array to store our state data in. As we know, there are
     * 50 US states. */
    struct climate_info *states[NUM_STATES] = { NULL };

    for (int i = 1; i < argc; ++i)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            fprintf(stderr, "%s: error opening file %s for reading\n", argv[0], argv[i]);
            continue;
        }
        analyze_file(fp, argv[i], states, NUM_STATES);
        fclose(fp);
    }
    print_report(states, NUM_STATES);
    return 0;
}

static struct climate_info *find_state(const char *state,
    struct climate_info **states, int num_states)
{
    int i;
    for (i = 0; i < num_states && states[i] != NULL; i++)
    {
        if (strcmp(states[i]->code, state) == 0)
            return states[i];
    }
    if (i >= num_states)
    {
        fprintf(stderr, "Too many different state codes!\n");
        for (i = 0; i < num_states; i++)
        {
            fprintf(stderr, " %s", states[i]->code);
            if (i > 0 && i % 25 == 24)
                putc('\n', stderr);
        }
        if (i % 25 != 0)
            putc('\n', stderr);
        exit(EXIT_FAILURE);
    }
    states[i] = calloc(1, sizeof(*states[i]));
    if (states[i] == NULL)
    {
        fprintf(stderr, "failed to allocate %zu bytes memory\n", sizeof(*states[i]));
        exit(EXIT_FAILURE);
    }
    strcpy(states[i]->code, state);
    return states[i];
}

void analyze_file(FILE *file, const char *name, struct climate_info **states, int num_states)
{
    const int line_sz = 100;
    char line[line_sz];
    int number = 0;

    while (fgets(line, line_sz, file) != NULL)
    {
        number++;
        enum { NUM_FIELDS = 9 };
        enum { F_STATE, F_MILLITIME, F_GEOHASH, F_HUMIDITY, F_SNOW,
               F_CLOUD, F_LIGHTNING, F_PRESSURE, F_TEMPERATURE };
        char copy[line_sz];
        strcpy(copy, line);
        char *field[NUM_FIELDS];
        char *start = copy;
        for (int i = 0; i < NUM_FIELDS; i++)
        {
            field[i] = strtok(start, " \t\n");
            start = NULL;
        }

        struct climate_info *info = find_state(field[F_STATE], states, num_states);

        long long millitime = strtoll(field[F_MILLITIME], NULL, 10);
        double humidity = strtod(field[F_HUMIDITY], NULL);
        double snow = strtod(field[F_SNOW], NULL);
        double cloud = strtod(field[F_CLOUD], NULL);
        double lightning = strtod(field[F_LIGHTNING], NULL);
        double temperature = strtod(field[F_TEMPERATURE], NULL);

        /* Add the data to the state record */
        info->num_records++;
        info->humidity += humidity;
        info->cloud += cloud;
        info->lightning += lightning;
        info->temperature += temperature;
        info->snow += snow;
        if (temperature < info->lo_temp_reading || info->hi_temp_millitime == 0)
        {
            info->lo_temp_reading = temperature;
            info->lo_temp_millitime = millitime;
        }
        if (temperature > info->hi_temp_reading || info->hi_temp_millitime == 0)
        {
            info->hi_temp_reading = temperature;
            info->hi_temp_millitime = millitime;
        }
    }
    printf("File %s - %d lines\n", name, number);
}

void print_report(struct climate_info *states[], int num_states)
{
    printf("States found:");
    int i;
    for (i = 0; i < num_states; ++i)
    {
        if (states[i] != NULL)
        {
            struct climate_info *info = states[i];
            printf(" %s", info->code);
        }
    }
    printf("\n");

    for (i = 0; i < num_states && states[i] != NULL; i++)
    {
        printf("-- State: %s --\n", states[i]->code);
        printf("Number of records:     %lu\n", states[i]->num_records);
        printf("Aggregate humidity:    %8.1f\n", states[i]->humidity);
        printf("Aggregate lightning:   %.0f\n", states[i]->lightning);
        printf("Aggregate snow:        %.0f\n", states[i]->snow); 
        printf("Aggregate cloud:       %.0f\n", states[i]->cloud); 
        printf("Aggregate temperature: %.5f\n", states[i]->temperature); 
        printf("Lowest temperature:    %9.5f (at %lld)\n",
                states[i]->lo_temp_reading, states[i]->lo_temp_millitime);
        printf("Highest temperature:   %9.5f (at %lld)\n",
                states[i]->hi_temp_reading, states[i]->hi_temp_millitime);
    }

    /* TODO: Print out the summary for each state. See format above. */
}

/*
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
 */
