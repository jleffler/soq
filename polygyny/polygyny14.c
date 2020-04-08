/* Main Section of Code */

#include "polygyny14.h"

int main()
{
	float shrink_factor=1.0;

	idummy = -1;
	ran1(&idummy);        /* initialize random number generator */
	idummy = 1;

	int loop_count1;

	int numruns=1;
    int disease_intro_time=(int)(1000*12);
    int numsteps=(int)(20000*12);
	int inject_infection=(int)(70*12);
	float case_import_probability=0.01;

	float transmission_probability=0.85;
    float recovery_probability=1.0/12;
	float theta=0.05;
    float punishing_threshold=0;

	float disease_death_probability=0;
    float natural_death_probability=1.0/70.0/12.0;
    float effective_birth_probability;
    float polygyny_penalty;

    float infertility_rate_X;
    float infertility_rate_M;
    float infertility_rate_P;
    int num_infertile_X;
    int num_infertile_M;
    int num_infertile_P;
    int num_X_men;
    int num_M_men;
    int num_P_men;

    float X_part_distrib_output[5];
    float M_part_distrib_output[5];
    float P_part_distrib_output[5];

    float mean_birth_probability=log(0.07857/12);
    float SD_birth_probability = fabs(mean_birth_probability*0.057669);

    float fertility_penalty=0.25;

	float breakup_probability=0.05/12;
	float formation_probability=0.1;

    double mate_exponent=1.5;

	float cost_paid=0.01;
	float cost_imposed=0.01;

	float error_term=0.01;
	float exogamy=0.8;
    int baseline_carrying_capacity=(int)((float)(MAXGROUPSIZE-5)*shrink_factor);
	int strategy_adoption_parameter=1;
	int splitting_threshold = (int)(baseline_carrying_capacity*0.9);

	int current_group_ID;

	int initial_pop_size=500;
	int initial_num_groups=50;

	int initial_M_strategists=10;
	int initial_X_strategists=10;

	float competition_factor = 10;
	float competition_probability = 0.05;
    float competition_odds;
    int group1_size, group2_size;
    int group1, group2;
    int num_of_searches;
    int competition_occurs;
    int partner_distribution_criterion_met;

    int num_groups;

	int num_X_infected;
	int num_M_infected;
	int num_P_infected;

	float X_prevalence;
	float M_prevalence;
	float P_prevalence;
    float total_prevalence;
    int time_count;

    float X_prevalence1;
    float M_prevalence1;
    float P_prevalence1;
    int time_count1;

    float X_prevalence2;
    float M_prevalence2;
    float P_prevalence2;
    int time_count2;

    float X_prevalence3;
    float M_prevalence3;
    float P_prevalence3;
    int time_count3;

    float prop_group;
	float X_prevalence_in_X_group;
	float M_prevalence_in_X_group;
	float P_prevalence_in_X_group;
	float prevalence_in_X_group;
	float X_prevalence_in_M_group;
	float M_prevalence_in_M_group;
	float P_prevalence_in_M_group;
	float prevalence_in_M_group;
	float X_prevalence_in_P_group;
	float M_prevalence_in_P_group;
	float P_prevalence_in_P_group;
    float prevalence_in_P_group;
    int time_count0;

	int num_X_infected_in_X_group;
	int num_M_infected_in_X_group;
	int num_P_infected_in_X_group;
	int num_X_infected_in_M_group;
	int num_M_infected_in_M_group;
	int num_P_infected_in_M_group;
	int num_X_infected_in_P_group;
	int num_M_infected_in_P_group;
	int num_P_infected_in_P_group;

	int num_X_in_X_group;
	int num_M_in_X_group;
	int num_P_in_X_group;
	int num_X_in_M_group;
	int num_M_in_M_group;
	int num_P_in_M_group;
	int num_X_in_P_group;
	int num_M_in_P_group;
	int num_P_in_P_group;

    int time_count_X_fitness, time_count_M_fitness , time_count_P_fitness;
    int time_count_X_prevalence , time_count_M_prevalence , time_count_P_prevalence;
    int time_count_prev_X_in_X , time_count_prev_M_in_X , time_count_prev_P_in_X;
    int time_count_prev_X_in_M , time_count_prev_M_in_M , time_count_prev_P_in_M;
    int time_count_prev_X_in_P , time_count_prev_M_in_P , time_count_prev_P_in_P;
    int time_count_X_group_size , time_count_M_group_size , time_count_P_group_size;
    int time_count_prev_in_X , time_count_prev_in_M , time_count_prev_in_P;
    int time_count_total_group_size;
    int time_count_total_prevalence;
    int time_count_X_avg_num_partners,time_count_M_avg_num_partners, time_count_P_avg_num_partners;
    int time_count_X_distrib_num_partners, time_count_M_distrib_num_partners, time_count_P_distrib_num_partners;

    float overall_prevalence_near_end;
    int time_count_end;
    float overall_prevalence_near_end2;
    int time_count_end2;

	float X_group_size;
	float M_group_size;
	float P_group_size;
	float total_group_size;

    float X_group_size1;
    float M_group_size1;
    float P_group_size1;

    float X_group_size2;
    float M_group_size2;
    float P_group_size2;

    float X_group_size3;
    float M_group_size3;
    float P_group_size3;

	int X_group_size_counter;
	int M_group_size_counter;
	int P_group_size_counter;
	int total_group_size_counter;

    int X_group_size_counter1;
    int M_group_size_counter1;
    int P_group_size_counter1;

    int X_group_size_counter2;
    int M_group_size_counter2;
    int P_group_size_counter2;

    int X_group_size_counter3;
    int M_group_size_counter3;
    int P_group_size_counter3;

    int X_group_size_temp;
	int M_group_size_temp;
	int P_group_size_temp;
	int total_group_size_temp;

    int X_group_size_temp1;
    int M_group_size_temp1;
    int P_group_size_temp1;

    int X_group_size_temp2;
    int M_group_size_temp2;
    int P_group_size_temp2;

    int X_group_size_temp3;
    int M_group_size_temp3;
    int P_group_size_temp3;

    float X_avg_num_partners;
	float M_avg_num_partners;
	float P_avg_num_partners;

	int X_avg_num_partners_count;
	int M_avg_num_partners_count;
	int P_avg_num_partners_count;

	int X_avg_num_partners_temp;
	int M_avg_num_partners_temp;
	int P_avg_num_partners_temp;

	float X_distrib_num_partners[5];
	float M_distrib_num_partners[5];
	float P_distrib_num_partners[5];

	int X_distrib_num_partners_count;
	int M_distrib_num_partners_count;
	int P_distrib_num_partners_count;

	int X_distrib_num_partners_temp[5];
	int M_distrib_num_partners_temp[5];
	int P_distrib_num_partners_temp[5];

	float X_avg_fitness;
	float M_avg_fitness;
	float P_avg_fitness;

	int X_avg_fitness_temp;
	int M_avg_fitness_temp;
	int P_avg_fitness_temp;

	int X_avg_fitness_count;
	int M_avg_fitness_count;
	int P_avg_fitness_count;

    float prev_X_temp, prev_M_temp, prev_P_temp;
    float temp_prev1, temp_prev2;

    /**********/

	float g1percentP, g1percentX, g2percentP, g2percentX;
	int P_group_wins=0, X_group_wins=0;
	int a, b, c, d, j, k, n, t, gp;
	int partner_flag;
	int group_assignment;
	int initial_group_size;
	int group_flag;
	int P; /* number of partnerships */
	int num_infected = 0;
	int num_pairs = 0;
	int num_individuals = 0;
	int num_X=0;
	int num_P=0;
	int num_M=0;
	int percent_X_wins, percent_P_wins, percent_M_wins;

    float average_size_P_groups;
    float average_size_X_groups;
    float average_incidence_P_groups;

    int num_P_groups;
    int num_X_groups;
    int num_M_groups;

    float prop_X_in_X, prop_M_in_X, prop_P_in_X;
    float prop_X_in_M, prop_M_in_M, prop_P_in_M;
    float prop_X_in_P, prop_M_in_P, prop_P_in_P;

    float prop_X_in_X_previous, prop_M_in_X_previous, prop_P_in_X_previous;
    float prop_X_in_M_previous, prop_M_in_M_previous, prop_P_in_M_previous;
    float prop_X_in_P_previous, prop_M_in_P_previous, prop_P_in_P_previous;

	int num_infected_bygroup[initial_num_groups];
	int num_pairs_bygroup[initial_num_groups];
	int num_individuals_bygroup[initial_num_groups];
	int num_X_bygroup[initial_num_groups];
	int num_P_bygroup[initial_num_groups];
	int num_M_bygroup[initial_num_groups];

	float average_X_fitness, stdev_X_fitness;
	float average_M_fitness, stdev_M_fitness;
	float average_P_fitness, stdev_P_fitness;

	FILE *f1, *f2, *f3, *f4, *f5, *f6;
	FILE *fg1, *fg2, *fg3, *fg4, *fg5, *fg6, *fg7, *fg8, *fg9, *fg10;
	FILE *fg11, *fg12, *fg13, *fg14, *fg15, *fg16, *fg17, *fg18, *fg19, *fg20;
	FILE *fg21, *fg22, *fg23, *fg24, *fg25, *fg26, *fg27, *fg28, *fg29, *fg30;
	FILE *fg31, *fg32, *fg33, *fg34, *fg35, *fg36, *fg37, *fg38, *fg39, *fg40;
	FILE *fg41, *fg42, *fg43, *fg44, *fg45, *fg46, *fg47, *fg48, *fg49, *fg50;
	FILE *fparam;
	FILE *ftemp;
    ftemp = fopen("group_size_data.csv","a");

	f1 = fopen("timeseries.csv","a");
	f2 = fopen("status_file.csv","a");
	f3 = fopen("timeseries_by_type.csv","a");
	f4 = fopen("output_statistics.csv","a");
	f5 = fopen("output_statistics_brief.csv","a");
	f6 = fopen("output_statistics_Xwins.csv","a");

	fparam = fopen("parameters.csv", "a");

	fg1 = fopen("group1.csv","a");
	fg2 = fopen("group2.csv","a");
	fg3 = fopen("group3.csv","a");
	fg4 = fopen("group4.csv","a");
	fg5 = fopen("group5.csv","a");
	fg6 = fopen("group6.csv","a");
	fg7 = fopen("group7.csv","a");
	fg8 = fopen("group8.csv","a");
	fg9 = fopen("group9.csv","a");
	fg10 = fopen("group10.csv","a");
	fg11 = fopen("group11.csv","a");
	fg12 = fopen("group12.csv","a");
	fg13 = fopen("group13.csv","a");
	fg14 = fopen("group14.csv","a");
	fg15 = fopen("group15.csv","a");
	fg16 = fopen("group16.csv","a");
	fg17 = fopen("group17.csv","a");
	fg18 = fopen("group18.csv","a");
	fg19 = fopen("group19.csv","a");
	fg20 = fopen("group20.csv","a");
	fg21 = fopen("group21.csv","a");
	fg22 = fopen("group22.csv","a");
	fg23 = fopen("group23.csv","a");
	fg24 = fopen("group24.csv","a");
	fg25 = fopen("group25.csv","a");
	fg26 = fopen("group26.csv","a");
	fg27 = fopen("group27.csv","a");
	fg28 = fopen("group28.csv","a");
	fg29 = fopen("group29.csv","a");
	fg30 = fopen("group30.csv","a");
	fg31 = fopen("group31.csv","a");
	fg32 = fopen("group32.csv","a");
	fg33 = fopen("group33.csv","a");
	fg34 = fopen("group34.csv","a");
	fg35 = fopen("group35.csv","a");
	fg36 = fopen("group36.csv","a");
	fg37 = fopen("group37.csv","a");
	fg38 = fopen("group38.csv","a");
	fg39 = fopen("group39.csv","a");
	fg40 = fopen("group40.csv","a");
	fg41 = fopen("group41.csv","a");
	fg42 = fopen("group42.csv","a");
	fg43 = fopen("group43.csv","a");
	fg44 = fopen("group44.csv","a");
	fg45 = fopen("group45.csv","a");
	fg46 = fopen("group46.csv","a");
	fg47 = fopen("group47.csv","a");
	fg48 = fopen("group48.csv","a");
	fg49 = fopen("group49.csv","a");
	fg50 = fopen("group50.csv","a");

    for (j = 0 ; j < 10000 ; j ++)
        kyrand();

	node *ptr;
	if ((ptr = (node *)calloc(N,sizeof(node))) == NULL)
	{
		exit(0);
	}

	group *group_ptr;
	if ((group_ptr = (group *)calloc(MAXNUMGROUPS,sizeof(group))) == NULL)
	{
		exit(0);
	}

	fprintf(fparam," shrink_factor=%f \n", shrink_factor);
	fprintf(fparam," numruns=%d \n",numruns);
	fprintf(fparam," numsteps=%d \n",numsteps);
	fprintf(fparam," inject_infection=%d \n",inject_infection);
	fprintf(fparam," case_import_probability=%f \n",case_import_probability);
	fprintf(fparam," transmission_probability=%f, \n",transmission_probability);
	fprintf(fparam," recovery_probability=%f \n",recovery_probability);
	fprintf(fparam," theta=%f \n",theta);
	fprintf(fparam," disease_death_probability=%f \n",disease_death_probability);
	fprintf(fparam," natural_death_probability=%f \n",natural_death_probability);
	fprintf(fparam," mean_birth_probability=%f \n",mean_birth_probability);
	fprintf(fparam," SD_birth_probability=%f \n",SD_birth_probability);
	fprintf(fparam," breakup_probability=%f \n",breakup_probability);
	fprintf(fparam," formation_probability=%f \n",formation_probability);
	fprintf(fparam," error_term=%f \n",error_term);
	fprintf(fparam," exogamy=%f \n",exogamy);
	fprintf(fparam," mate_exponent=%f \n",mate_exponent);
	fprintf(fparam," baseline_carrying_capacity=%d \n",baseline_carrying_capacity);
	fprintf(fparam," strategy_adoption_parameter=%d \n",strategy_adoption_parameter);
	fprintf(fparam," cost_paid=%f \n",cost_paid);
	fprintf(fparam," cost_imposed=%f \n",cost_imposed);
	fprintf(fparam," initial_pop_size=%d \n",initial_pop_size);
	fprintf(fparam," initial_num_groups=%d \n",initial_num_groups);
	fprintf(fparam," initial_M_strategists=%d \n",initial_M_strategists);
	fprintf(fparam," initial_X_strategists=%d \n",initial_X_strategists);
	fprintf(fparam," competition_factor = %f \n",competition_factor);
	fprintf(fparam," competition_probability = %f \n\n",competition_probability);

	X_prevalence = M_prevalence = P_prevalence = total_prevalence = 0;
    time_count = 0;
    X_prevalence1 = M_prevalence1 = P_prevalence1 = 0;
    time_count1 = 0;
    X_prevalence2 = M_prevalence2 = P_prevalence2 = 0;
    time_count2 = 0;
    X_prevalence3 = M_prevalence3 = P_prevalence3 = 0;
    time_count3 = 0;

    time_count_X_fitness = time_count_M_fitness = time_count_P_fitness = 0;
    time_count_X_prevalence = time_count_M_prevalence = time_count_P_prevalence = 0;
    time_count_prev_X_in_X = time_count_prev_M_in_X = time_count_prev_P_in_X = 0;
    time_count_prev_X_in_M = time_count_prev_M_in_M = time_count_prev_P_in_M = 0;
    time_count_prev_X_in_P = time_count_prev_M_in_P = time_count_prev_P_in_P = 0;
    time_count_total_group_size = 0;
    time_count_total_prevalence = 0;
    time_count_X_group_size = time_count_M_group_size = time_count_P_group_size = 0;
    time_count_prev_in_X = time_count_prev_in_M = time_count_prev_in_P = 0;
    time_count_X_avg_num_partners = time_count_M_avg_num_partners = time_count_P_avg_num_partners = 0;
    time_count_X_distrib_num_partners = time_count_M_distrib_num_partners = time_count_P_distrib_num_partners = 0;

    X_prevalence_in_P_group = M_prevalence_in_P_group = P_prevalence_in_P_group = prevalence_in_P_group = 0;
	X_prevalence_in_M_group = M_prevalence_in_M_group = P_prevalence_in_M_group = prevalence_in_M_group = 0;
	X_prevalence_in_X_group = M_prevalence_in_X_group = P_prevalence_in_X_group = prevalence_in_X_group = 0;
	num_X_in_X_group = num_M_in_X_group = num_P_in_X_group = 0;
	num_X_in_M_group = num_M_in_M_group = num_P_in_M_group = 0;
	num_X_in_P_group = num_M_in_P_group = num_P_in_P_group = 0;
	num_X_infected_in_X_group = num_M_infected_in_X_group = num_P_infected_in_X_group = 0;
	num_X_infected_in_M_group = num_M_infected_in_M_group = num_P_infected_in_M_group = 0;
	num_X_infected_in_P_group = num_M_infected_in_P_group = num_P_infected_in_P_group = 0;
    time_count0 = 0;

	time_count = 0;
	X_group_size = M_group_size = P_group_size = total_group_size = 0;
    X_group_size1 = M_group_size1 = P_group_size1 = 0;
    X_group_size2 = M_group_size2 = P_group_size2 = 0;
    X_group_size3 = M_group_size3 = P_group_size3 = 0;

    X_avg_num_partners = M_avg_num_partners = P_avg_num_partners = 0;
	X_avg_fitness = M_avg_fitness = P_avg_fitness = 0;
	for (k = 0 ; k < 5 ; k ++)
	{
		X_distrib_num_partners[k] = 0;
		M_distrib_num_partners[k] = 0;
		P_distrib_num_partners[k] = 0;
	}

    overall_prevalence_near_end = 0;
    time_count_end = 0;
    overall_prevalence_near_end2 = 0;
    time_count_end2 = 0;

	/******************************/
	/* initialize group structure */
	/******************************/

	for (k = 0 ; k < MAXNUMGROUPS ; k ++)
	{
		group_ptr[k].carrying_capacity=baseline_carrying_capacity;
		group_ptr[k].size=0;

		for (j = 0 ; j < MAXGROUPSIZE ; j ++)
		{
			group_ptr[k].member[j]=-1;
		}
		group_ptr[k].active=1;
	}

	/***********************************/
	/* initialize individual structure */
	/***********************************/

	for (k = 0 ; k < N ; k ++)
	{
		ptr[k].active=0;
	}

	/******************************************/
	/* check input parameters for consistency */
	/******************************************/

	if (initial_pop_size > N)
	{
		printf("initial population size exceeds maximum population size.  exiting \n");
		exit(0);
	}

	if (initial_pop_size > 0.5*N)
	{
		printf("initial population size may not leave enough room for growth.  initial population is %d and max populatoin is %d. Continue? \n",initial_pop_size,N);
		getchar();
	}

	if (initial_num_groups > MAXNUMGROUPS)
	{
		printf("initial number of groups exceeds maximum number of groups.  exiting \n");
		exit(0);
	}

	initial_group_size = (int)((float)initial_pop_size/initial_num_groups);

	if (initial_group_size > MAXGROUPSIZE)
	{
		printf("initial group size exceeds maximum possible group size.  exiting \n");
		exit(0);
	}

	if (initial_group_size > 0.5*MAXGROUPSIZE)
	{
		printf("initial group size is %d compared to max group size of %d, which may not leave enough room for growth.  is this OK? \n",initial_group_size,MAXGROUPSIZE);
		getchar();
	}

	if (inject_infection > numsteps)
	{
		printf("time %d that infection is introduced exceeds total time %d of simulation.  is this OK? \n",inject_infection,numsteps);
		getchar();
	}

	for (k = 0 ; k < initial_num_groups; k ++)
	{
		if (initial_group_size > group_ptr[k].carrying_capacity)
		{
			printf("initial group size exceeds carrying capacity.  exiting \n");
			exit(0);
		}
		if (initial_group_size > 0.5*group_ptr[k].carrying_capacity)
		{
			printf("initial group size of group %d is %d compared to group carrying capacity of %d, which may not leave enough room for growth.  is this OK? ",k,initial_group_size,group_ptr[k].carrying_capacity);
			getchar();
		}
	}

	if (initial_M_strategists + initial_X_strategists > (int)((float)initial_pop_size/2))
	{
		printf("initial number of M and X strategists exceeds male population size.  exiting \n");
		exit(0);
	}

	/************************************************************/
	/* activate selected nodes, assign gender, group membership */
	/************************************************************/

	for (k = 0 ; k < initial_pop_size ; k ++)
	{
		/* update status, number of partners, etc */

		ptr[k].active=1;
		ptr[k].status='s';
		ptr[k].num_partners=0;
		ptr[k].fitness=0;
        ptr[k].fertile=1;

		for (n = 0 ; n < MAXNUMPARTNERS; n ++)
			ptr[k].partner[n]=-1;

		if (k%2==0)
			ptr[k].gender='m';
		else
			ptr[k].gender='f';

        ptr[k].virgin=1;

        /* assign individual to a group */

		group_assignment = (int)((float)k/initial_group_size);
		if (group_assignment >= initial_num_groups)
			group_assignment = initial_num_groups-1;
		ptr[k].group = group_assignment;

		/* update group membership roster */

		group_flag=0;
		for (j = 0 ; j < MAXGROUPSIZE ; j ++)
			if (group_ptr[group_assignment].member[j]==-1 && group_flag==0)
			{
				group_ptr[group_assignment].member[j]=k;
				group_ptr[group_assignment].size ++;
				group_flag=1;
			}
		if (group_flag==0)
		{
			printf("error in group assignment process.  exiting \n");
			exit(0);
		}
	}

	/*******************************************************/
	/* initial strategy distributions, birth probabilities */
	/*******************************************************/

	for (k = 0 ; k < initial_pop_size ; k ++)
	{
		if (ptr[k].gender=='m')
			ptr[k].strategy='P';
		else
			ptr[k].strategy='-';
	}

	k=0;
	do {
		j = (int)(initial_pop_size*kyrand());
		if (ptr[j].strategy=='P' && ptr[j].gender=='m')
		{
			ptr[j].strategy='M';
			k++;
		}
	} while (k < initial_M_strategists);

	k=0;
	do {
		j = (int)(initial_pop_size*kyrand());
		if (ptr[j].strategy=='P' && ptr[j].gender=='m')
		{
			ptr[j].strategy='X';
			k++;
		}
	} while (k < initial_X_strategists);

	for (k = 0 ; k < initial_pop_size ; k ++)
	{
		if (ptr[k].gender=='f')
			ptr[k].birth_probability=0;
		else
		{
            ptr[k].birth_probability = exp(mean_birth_probability + SD_birth_probability*gasdev(&idummy));
        }
	}

	/***************/
	/* check setup */
	/***************/

	/*		for (k = 0 ; k < initial_pop_size + 10 ; k ++)
	 {
	 printf("node=%d num_ptnrs=%d || gen=%c status=%c || gp=%d || str=%c || %d %d %d %d %d %d \n",k,ptr[k].num_partners,ptr[k].gender,ptr[k].status,ptr[k].group,ptr[k].strategy,ptr[k].partner[0],ptr[k].partner[1],ptr[k].partner[2],ptr[k].partner[3],ptr[k].partner[4],ptr[k].partner[5]);
	 }

	 for (k = 0 ; k < initial_num_groups; k ++)
	 {
	 printf("%d %d || ",group_ptr[k].size,group_ptr[k].carrying_capacity);
	 for (j = 0 ; j < MAXGROUPSIZE ; j++)
	 {
	 printf("%d ",group_ptr[k].member[j]);
	 }
	 printf("\n");
	 }
	 */

	/*********************/
	/*********************/
	/*********************/
	/*		simulate	 */
	/*********************/
	/*********************/
	/*********************/

	for (t=0 ; t < numsteps ; t ++)
	{
		/************************/
		/* initialize infection */
		/************************/

        if (t%inject_infection==0 && t > disease_intro_time)
		{
			for (k = 0 ; k < N ; k ++)
			{
                if (kyrand() < case_import_probability && ptr[k].active)
				{
					if (ptr[k].status=='s')
					{
						if (kyrand()<theta)
                        {
							ptr[k].status='i';
                            ptr[k].fertile=0;
                        }
						else
							ptr[k].status='a';
					}
				}
			}
		}

		/***************************/
		/***************************/
		/***************************/
		/* main part of simulation */
		/***************************/
		/***************************/
		/***************************/

		/******************************************/
		/* check for individual state transitions */
		/******************************************/

		for (k = 0 ; k < N ; k ++)
		{
			if (ptr[k].active)
			{
				/****************/
				/* transmission */
				/****************/

				if (ptr[k].status=='a' || ptr[k].status=='i')
				{
					for (c = 0 ; c < ptr[k].num_partners ; c ++)
					{
						d = ptr[k].partner[c];
						if (kyrand()<transmission_probability && ptr[d].status=='s')
						{
							if (kyrand()<theta)
                            {
								ptr[d].status='i';
                                ptr[k].fertile=0;
                            }
							else
								ptr[d].status='a';
						}
					}
				}

				/************/
				/* recovery */
				/************/

				if ((ptr[k].status=='i' || ptr[k].status=='a') && kyrand() < recovery_probability)
				{
					ptr[k].status='s';
				}

				/*************************/
				/* partnership formation */
				/*************************/

				if (kyrand()<formation_probability && ptr[k].gender=='f' && ptr[k].num_partners==0)
				{
					n = ptr[k].group;

                    if (kyrand()<exogamy && ptr[k].virgin==1)
					{
                        seek_partnership_outside(ptr,group_ptr,k,n,mate_exponent,fertility_penalty,cost_paid,cost_imposed,punishing_threshold);  /* THX1138 */
					}
					else
					{
                        seek_partnership_inside_ranked(ptr,group_ptr,k,n,mate_exponent,fertility_penalty,cost_paid,cost_imposed,punishing_threshold);
					}
				}

				/*************************/
				/* partnership breakup   */
				/*************************/

				if (kyrand()<breakup_probability && ptr[k].num_partners>0 && ptr[k].gender=='f')
				{
					do
					{
						c = (int)(kyrand()*MAXNUMPARTNERS);
						b = ptr[k].partner[c];
					} while (b == -1 || c==MAXNUMPARTNERS);

					break_partnership(ptr,k,b);
				}

				/********************/
				/* natural death	*/
				/********************/

				if (kyrand() < natural_death_probability)
				{
					individual_dies(ptr,group_ptr,k);
				}

				/********************/
				/* disease death	*/
				/********************/

				if (kyrand() < disease_death_probability && (ptr[k].status=='i' || ptr[k].status=='a'))
				{
					individual_dies(ptr,group_ptr,k);
				}

				/************/
				/* birth	*/
				/************/

                if (ptr[k].gender=='f' && ptr[k].num_partners > 0 && ptr[k].fertile==1 && her_partner_fertile(ptr, k) && ptr[k].active)
                {
                    polygyny_penalty = 1.0/(fertility_penalty*ptr[her_current_partner(ptr,k)].num_partners + (1-fertility_penalty)); /* THX1138 */

                    effective_birth_probability = ptr[her_current_partner(ptr,k)].birth_probability*her_partners_penalty(group_ptr, ptr, k, cost_paid, cost_imposed, punishing_threshold)*polygyny_penalty;  /* THX1138 */

                    if (kyrand() < effective_birth_probability)
                        individual_born(ptr,group_ptr,k,error_term,strategy_adoption_parameter,mean_birth_probability,SD_birth_probability);

                }
			}
		}

		/*******************************/
		/* check for group competition */
		/*******************************/

		if (kyrand()<competition_probability)
		{
			num_of_searches=0;
			competition_occurs=1;

            do
            {
                group1 = (int)(kyrand()*initial_num_groups);
                num_of_searches++;
            } while (num_in_group(group_ptr, ptr, group1)==0 && num_of_searches < 500);

            if (num_of_searches==500)
                competition_occurs=0;

            num_of_searches=0;
            do
            {
                group2 = (int)(kyrand()*initial_num_groups);
                num_of_searches++;
            } while ((num_in_group(group_ptr, ptr, group2)==0 || group2==group1) && num_of_searches < 500);

            if (num_of_searches==500)
                competition_occurs=0;

			if (competition_occurs)
			{
				group1_size = num_in_group(group_ptr, ptr, group1);
				group2_size = num_in_group(group_ptr, ptr, group2);

                competition_odds = pow((float)group1_size, competition_factor)/(pow((float)group1_size, competition_factor) + pow((float)group2_size, competition_factor));

				g1percentP=100*(float)num_P_in_group(group_ptr,ptr,group1)/(num_X_in_group(group_ptr,ptr,group1)+num_M_in_group(group_ptr,ptr,group1)+num_P_in_group(group_ptr,ptr,group1));
				g1percentX=100*(float)num_X_in_group(group_ptr,ptr,group1)/(num_X_in_group(group_ptr,ptr,group1)+num_M_in_group(group_ptr,ptr,group1)+num_P_in_group(group_ptr,ptr,group1));
				g2percentP=100*(float)num_P_in_group(group_ptr,ptr,group2)/(num_X_in_group(group_ptr,ptr,group2)+num_M_in_group(group_ptr,ptr,group2)+num_P_in_group(group_ptr,ptr,group2));
				g2percentX=100*(float)num_X_in_group(group_ptr,ptr,group2)/(num_X_in_group(group_ptr,ptr,group2)+num_M_in_group(group_ptr,ptr,group2)+num_P_in_group(group_ptr,ptr,group2));


				if (kyrand() < competition_odds)
				{
					if (g1percentP > g1percentX && g2percentP < g2percentX)
					{
						P_group_wins++;
					}
					else if (g1percentX > g1percentP && g2percentX < g2percentP)
					{
						X_group_wins++;
					}

					kill_group(group_ptr, ptr, group1, group2); /* group 1 wins */
				}
				else
				{
					if (g2percentP > g2percentX && g1percentP < g1percentX)
					{
						P_group_wins++;
					}
					else if (g2percentX > g2percentP && g1percentX < g1percentP)
					{
						X_group_wins++;
					}

					kill_group(group_ptr, ptr, group2, group1); /* group 2 wins */
				}
			}
		}

		/*****************************/
		/* check for group splitting */
		/*****************************/

        for (k = 0 ; k < initial_num_groups ; k ++)
        {
            if (num_in_group(group_ptr, ptr, k) >= splitting_threshold)
                split_group(group_ptr, ptr, k, initial_num_groups);
        }

		/************************/
        /************************/
        /************************/
        /************************/
		/* print out statistics */
		/************************/
        /************************/
        /************************/
        /************************/

		for (k = 0 ; k < initial_num_groups ; k ++)
		{
			num_infected_bygroup[k]=0;
			num_pairs_bygroup[k]=0;
			num_individuals_bygroup[k]=0;
			num_X_bygroup[k]=0;
			num_P_bygroup[k]=0;
			num_M_bygroup[k]=0;
		}

		num_infected = 0;
		num_pairs = 0;
		num_individuals=0;
		num_X=0;
		num_P=0;
		num_M=0;

		for (k = 0 ; k < N ; k ++)
		{
			if (ptr[k].active)
			{
				num_individuals++;
				if (ptr[k].status=='i' || ptr[k].status=='a')
					num_infected ++;
				if (ptr[k].gender=='m')
					num_pairs += ptr[k].num_partners;
				if (ptr[k].strategy=='X')
					num_X++;
				else if (ptr[k].strategy=='M')
					num_M++;
				else if (ptr[k].strategy=='P')
					num_P++;

				gp=ptr[k].group;

				num_individuals_bygroup[gp]++;
				if (ptr[k].status=='i' || ptr[k].status=='a')
					num_infected_bygroup[gp] ++;
				if (ptr[k].gender=='m')
					num_pairs_bygroup[gp] += ptr[k].num_partners;
				if (ptr[k].strategy=='X')
					num_X_bygroup[gp]++;
				else if (ptr[k].strategy=='M')
					num_M_bygroup[gp]++;
				else if (ptr[k].strategy=='P')
					num_P_bygroup[gp]++;
			}
		}
		if (t%5000==0)
		{
			printf("%d num_individuals=%d num_infected=%d num_pairs=%d || X=%d, P=%d, M=%d \n",t,num_individuals,num_infected,num_pairs,num_X,num_P,num_M);
		}
		if (t==0)
		{
			fprintf(f1,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness, #X groups, #M groups, #P groups \n");
			fprintf(fg1,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg2,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg3,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg4,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg5,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg6,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg7,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg8,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg9,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg10,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg11,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg12,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg13,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg14,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg15,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg16,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg17,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg18,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg19,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg20,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg21,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg22,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg23,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg24,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg25,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg26,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg27,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg28,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg29,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg30,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg31,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg32,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg33,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg34,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg35,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg36,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg37,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg38,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg39,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg40,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg41,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg42,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg43,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg44,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg45,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg46,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg47,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg48,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg49,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
			fprintf(fg50,"time, year, population, #infected, #pairs, X, M, P, X fitness, M fitness, P fitness \n");
		}

		if (t%60==0)
		{
            /************************************************************************************/
            /************************************************************************************/
            /************************************************************************************/
            /* Output group and individual time series                                          */
            /************************************************************************************/
            /************************************************************************************/
            /************************************************************************************/

            /*************************/
            /* population level data */
            /*************************/

            num_X_groups=0;
            num_M_groups=0;
            num_P_groups=0;
            num_groups=0;

            for (k = 0 ; k < initial_num_groups ; k ++)
            {
                if (num_X_in_group(group_ptr, ptr, k) > num_M_in_group(group_ptr, ptr, k) && num_X_in_group(group_ptr, ptr, k) > num_P_in_group(group_ptr, ptr, k))
                    num_X_groups ++;
                else if (num_M_in_group(group_ptr, ptr, k) > num_X_in_group(group_ptr, ptr, k) && num_M_in_group(group_ptr, ptr, k) > num_P_in_group(group_ptr, ptr, k))
                    num_M_groups ++;
                else if (num_P_in_group(group_ptr, ptr, k) > num_X_in_group(group_ptr, ptr, k) && num_P_in_group(group_ptr, ptr, k) > num_M_in_group(group_ptr, ptr, k))
                    num_P_groups ++;

                if (num_X_in_group(group_ptr, ptr, k) + num_M_in_group(group_ptr, ptr, k) + num_P_in_group(group_ptr, ptr, k) > 0)
                    num_groups ++;
            }

            fprintf(f1,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f, %d, %d, %d \n",t,(float)t/12,num_individuals,num_infected,num_pairs,num_X,num_M,num_P,population_X_fitness(ptr),population_M_fitness(ptr),population_P_fitness(ptr),num_X_groups,num_M_groups,num_P_groups);

            /*************************/
            /*   group level data    */
            /*************************/

            fprintf(fg1,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[0],num_infected_bygroup[0],num_pairs_bygroup[0],num_X_bygroup[0],num_M_bygroup[0],num_P_bygroup[0],group_X_fitness(ptr,group_ptr,0),group_M_fitness(ptr,group_ptr,0),group_P_fitness(ptr,group_ptr,0));
            fprintf(fg2,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[1],num_infected_bygroup[1],num_pairs_bygroup[1],num_X_bygroup[1],num_M_bygroup[1],num_P_bygroup[1],group_X_fitness(ptr,group_ptr,1),group_M_fitness(ptr,group_ptr,1),group_P_fitness(ptr,group_ptr,1));
            fprintf(fg3,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[2],num_infected_bygroup[2],num_pairs_bygroup[2],num_X_bygroup[2],num_M_bygroup[2],num_P_bygroup[2],group_X_fitness(ptr,group_ptr,2),group_M_fitness(ptr,group_ptr,2),group_P_fitness(ptr,group_ptr,2));
            fprintf(fg4,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[3],num_infected_bygroup[3],num_pairs_bygroup[3],num_X_bygroup[3],num_M_bygroup[3],num_P_bygroup[3],group_X_fitness(ptr,group_ptr,3),group_M_fitness(ptr,group_ptr,3),group_P_fitness(ptr,group_ptr,3));
            fprintf(fg5,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[4],num_infected_bygroup[4],num_pairs_bygroup[4],num_X_bygroup[4],num_M_bygroup[4],num_P_bygroup[4],group_X_fitness(ptr,group_ptr,4),group_M_fitness(ptr,group_ptr,4),group_P_fitness(ptr,group_ptr,4));
            fprintf(fg6,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[5],num_infected_bygroup[5],num_pairs_bygroup[5],num_X_bygroup[5],num_M_bygroup[5],num_P_bygroup[5],group_X_fitness(ptr,group_ptr,5),group_M_fitness(ptr,group_ptr,5),group_P_fitness(ptr,group_ptr,5));
            fprintf(fg7,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[6],num_infected_bygroup[6],num_pairs_bygroup[6],num_X_bygroup[6],num_M_bygroup[6],num_P_bygroup[6],group_X_fitness(ptr,group_ptr,6),group_M_fitness(ptr,group_ptr,6),group_P_fitness(ptr,group_ptr,6));
            fprintf(fg8,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[7],num_infected_bygroup[7],num_pairs_bygroup[7],num_X_bygroup[7],num_M_bygroup[7],num_P_bygroup[7],group_X_fitness(ptr,group_ptr,7),group_M_fitness(ptr,group_ptr,7),group_P_fitness(ptr,group_ptr,7));
            fprintf(fg9,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[8],num_infected_bygroup[8],num_pairs_bygroup[8],num_X_bygroup[8],num_M_bygroup[8],num_P_bygroup[8],group_X_fitness(ptr,group_ptr,8),group_M_fitness(ptr,group_ptr,8),group_P_fitness(ptr,group_ptr,8));
            fprintf(fg10,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[9],num_infected_bygroup[9],num_pairs_bygroup[9],num_X_bygroup[9],num_M_bygroup[9],num_P_bygroup[9],group_X_fitness(ptr,group_ptr,9),group_M_fitness(ptr,group_ptr,9),group_P_fitness(ptr,group_ptr,9));
            fprintf(fg11,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[10],num_infected_bygroup[10],num_pairs_bygroup[10],num_X_bygroup[10],num_M_bygroup[10],num_P_bygroup[10],group_X_fitness(ptr,group_ptr,10),group_M_fitness(ptr,group_ptr,10),group_P_fitness(ptr,group_ptr,10));
            fprintf(fg12,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[11],num_infected_bygroup[11],num_pairs_bygroup[11],num_X_bygroup[11],num_M_bygroup[11],num_P_bygroup[11],group_X_fitness(ptr,group_ptr,11),group_M_fitness(ptr,group_ptr,11),group_P_fitness(ptr,group_ptr,11));
            fprintf(fg13,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[12],num_infected_bygroup[12],num_pairs_bygroup[12],num_X_bygroup[12],num_M_bygroup[12],num_P_bygroup[12],group_X_fitness(ptr,group_ptr,12),group_M_fitness(ptr,group_ptr,12),group_P_fitness(ptr,group_ptr,12));
            fprintf(fg14,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[13],num_infected_bygroup[13],num_pairs_bygroup[13],num_X_bygroup[13],num_M_bygroup[13],num_P_bygroup[13],group_X_fitness(ptr,group_ptr,13),group_M_fitness(ptr,group_ptr,13),group_P_fitness(ptr,group_ptr,13));
            fprintf(fg15,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[14],num_infected_bygroup[14],num_pairs_bygroup[14],num_X_bygroup[14],num_M_bygroup[14],num_P_bygroup[14],group_X_fitness(ptr,group_ptr,14),group_M_fitness(ptr,group_ptr,14),group_P_fitness(ptr,group_ptr,14));
            fprintf(fg16,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[15],num_infected_bygroup[15],num_pairs_bygroup[15],num_X_bygroup[15],num_M_bygroup[15],num_P_bygroup[15],group_X_fitness(ptr,group_ptr,15),group_M_fitness(ptr,group_ptr,15),group_P_fitness(ptr,group_ptr,15));
            fprintf(fg17,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[16],num_infected_bygroup[16],num_pairs_bygroup[16],num_X_bygroup[16],num_M_bygroup[16],num_P_bygroup[16],group_X_fitness(ptr,group_ptr,16),group_M_fitness(ptr,group_ptr,16),group_P_fitness(ptr,group_ptr,16));
            fprintf(fg18,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[17],num_infected_bygroup[17],num_pairs_bygroup[17],num_X_bygroup[17],num_M_bygroup[17],num_P_bygroup[17],group_X_fitness(ptr,group_ptr,17),group_M_fitness(ptr,group_ptr,17),group_P_fitness(ptr,group_ptr,17));
            fprintf(fg19,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[18],num_infected_bygroup[18],num_pairs_bygroup[18],num_X_bygroup[18],num_M_bygroup[18],num_P_bygroup[18],group_X_fitness(ptr,group_ptr,18),group_M_fitness(ptr,group_ptr,18),group_P_fitness(ptr,group_ptr,18));
            fprintf(fg20,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[19],num_infected_bygroup[19],num_pairs_bygroup[19],num_X_bygroup[19],num_M_bygroup[19],num_P_bygroup[19],group_X_fitness(ptr,group_ptr,19),group_M_fitness(ptr,group_ptr,19),group_P_fitness(ptr,group_ptr,19));
            fprintf(fg21,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[20],num_infected_bygroup[20],num_pairs_bygroup[20],num_X_bygroup[20],num_M_bygroup[20],num_P_bygroup[20],group_X_fitness(ptr,group_ptr,20),group_M_fitness(ptr,group_ptr,20),group_P_fitness(ptr,group_ptr,20));
            fprintf(fg22,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[21],num_infected_bygroup[21],num_pairs_bygroup[21],num_X_bygroup[21],num_M_bygroup[21],num_P_bygroup[21],group_X_fitness(ptr,group_ptr,21),group_M_fitness(ptr,group_ptr,21),group_P_fitness(ptr,group_ptr,21));
            fprintf(fg23,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[22],num_infected_bygroup[22],num_pairs_bygroup[22],num_X_bygroup[22],num_M_bygroup[22],num_P_bygroup[22],group_X_fitness(ptr,group_ptr,22),group_M_fitness(ptr,group_ptr,22),group_P_fitness(ptr,group_ptr,22));
            fprintf(fg24,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[23],num_infected_bygroup[23],num_pairs_bygroup[23],num_X_bygroup[23],num_M_bygroup[23],num_P_bygroup[23],group_X_fitness(ptr,group_ptr,23),group_M_fitness(ptr,group_ptr,23),group_P_fitness(ptr,group_ptr,23));
            fprintf(fg25,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[24],num_infected_bygroup[24],num_pairs_bygroup[24],num_X_bygroup[24],num_M_bygroup[24],num_P_bygroup[24],group_X_fitness(ptr,group_ptr,24),group_M_fitness(ptr,group_ptr,24),group_P_fitness(ptr,group_ptr,24));
            fprintf(fg26,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[25],num_infected_bygroup[25],num_pairs_bygroup[25],num_X_bygroup[25],num_M_bygroup[25],num_P_bygroup[25],group_X_fitness(ptr,group_ptr,25),group_M_fitness(ptr,group_ptr,25),group_P_fitness(ptr,group_ptr,25));
            fprintf(fg27,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[26],num_infected_bygroup[26],num_pairs_bygroup[26],num_X_bygroup[26],num_M_bygroup[26],num_P_bygroup[26],group_X_fitness(ptr,group_ptr,26),group_M_fitness(ptr,group_ptr,26),group_P_fitness(ptr,group_ptr,26));
            fprintf(fg28,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[27],num_infected_bygroup[27],num_pairs_bygroup[27],num_X_bygroup[27],num_M_bygroup[27],num_P_bygroup[27],group_X_fitness(ptr,group_ptr,27),group_M_fitness(ptr,group_ptr,27),group_P_fitness(ptr,group_ptr,27));
            fprintf(fg29,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[28],num_infected_bygroup[28],num_pairs_bygroup[28],num_X_bygroup[28],num_M_bygroup[28],num_P_bygroup[28],group_X_fitness(ptr,group_ptr,28),group_M_fitness(ptr,group_ptr,28),group_P_fitness(ptr,group_ptr,28));
            fprintf(fg30,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[29],num_infected_bygroup[29],num_pairs_bygroup[29],num_X_bygroup[29],num_M_bygroup[29],num_P_bygroup[29],group_X_fitness(ptr,group_ptr,29),group_M_fitness(ptr,group_ptr,29),group_P_fitness(ptr,group_ptr,29));
            fprintf(fg31,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[30],num_infected_bygroup[30],num_pairs_bygroup[30],num_X_bygroup[30],num_M_bygroup[30],num_P_bygroup[30],group_X_fitness(ptr,group_ptr,30),group_M_fitness(ptr,group_ptr,30),group_P_fitness(ptr,group_ptr,30));
            fprintf(fg32,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[31],num_infected_bygroup[31],num_pairs_bygroup[31],num_X_bygroup[31],num_M_bygroup[31],num_P_bygroup[31],group_X_fitness(ptr,group_ptr,31),group_M_fitness(ptr,group_ptr,31),group_P_fitness(ptr,group_ptr,31));
            fprintf(fg33,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[32],num_infected_bygroup[32],num_pairs_bygroup[32],num_X_bygroup[32],num_M_bygroup[32],num_P_bygroup[32],group_X_fitness(ptr,group_ptr,32),group_M_fitness(ptr,group_ptr,32),group_P_fitness(ptr,group_ptr,32));
            fprintf(fg34,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[33],num_infected_bygroup[33],num_pairs_bygroup[33],num_X_bygroup[33],num_M_bygroup[33],num_P_bygroup[33],group_X_fitness(ptr,group_ptr,33),group_M_fitness(ptr,group_ptr,33),group_P_fitness(ptr,group_ptr,33));
            fprintf(fg35,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[34],num_infected_bygroup[34],num_pairs_bygroup[34],num_X_bygroup[34],num_M_bygroup[34],num_P_bygroup[34],group_X_fitness(ptr,group_ptr,34),group_M_fitness(ptr,group_ptr,34),group_P_fitness(ptr,group_ptr,34));
            fprintf(fg36,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[35],num_infected_bygroup[35],num_pairs_bygroup[35],num_X_bygroup[35],num_M_bygroup[35],num_P_bygroup[35],group_X_fitness(ptr,group_ptr,35),group_M_fitness(ptr,group_ptr,35),group_P_fitness(ptr,group_ptr,35));
            fprintf(fg37,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[36],num_infected_bygroup[36],num_pairs_bygroup[36],num_X_bygroup[36],num_M_bygroup[36],num_P_bygroup[36],group_X_fitness(ptr,group_ptr,36),group_M_fitness(ptr,group_ptr,36),group_P_fitness(ptr,group_ptr,36));
            fprintf(fg38,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[37],num_infected_bygroup[37],num_pairs_bygroup[37],num_X_bygroup[37],num_M_bygroup[37],num_P_bygroup[37],group_X_fitness(ptr,group_ptr,37),group_M_fitness(ptr,group_ptr,37),group_P_fitness(ptr,group_ptr,37));
            fprintf(fg39,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[38],num_infected_bygroup[38],num_pairs_bygroup[38],num_X_bygroup[38],num_M_bygroup[38],num_P_bygroup[38],group_X_fitness(ptr,group_ptr,38),group_M_fitness(ptr,group_ptr,38),group_P_fitness(ptr,group_ptr,38));
            fprintf(fg40,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[39],num_infected_bygroup[39],num_pairs_bygroup[39],num_X_bygroup[39],num_M_bygroup[39],num_P_bygroup[39],group_X_fitness(ptr,group_ptr,39),group_M_fitness(ptr,group_ptr,39),group_P_fitness(ptr,group_ptr,39));
            fprintf(fg41,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[40],num_infected_bygroup[40],num_pairs_bygroup[40],num_X_bygroup[40],num_M_bygroup[40],num_P_bygroup[40],group_X_fitness(ptr,group_ptr,40),group_M_fitness(ptr,group_ptr,40),group_P_fitness(ptr,group_ptr,40));
            fprintf(fg42,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[41],num_infected_bygroup[41],num_pairs_bygroup[41],num_X_bygroup[41],num_M_bygroup[41],num_P_bygroup[41],group_X_fitness(ptr,group_ptr,41),group_M_fitness(ptr,group_ptr,41),group_P_fitness(ptr,group_ptr,41));
            fprintf(fg43,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[42],num_infected_bygroup[42],num_pairs_bygroup[42],num_X_bygroup[42],num_M_bygroup[42],num_P_bygroup[42],group_X_fitness(ptr,group_ptr,42),group_M_fitness(ptr,group_ptr,42),group_P_fitness(ptr,group_ptr,42));
            fprintf(fg44,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[43],num_infected_bygroup[43],num_pairs_bygroup[43],num_X_bygroup[43],num_M_bygroup[43],num_P_bygroup[43],group_X_fitness(ptr,group_ptr,43),group_M_fitness(ptr,group_ptr,43),group_P_fitness(ptr,group_ptr,43));
            fprintf(fg45,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[44],num_infected_bygroup[44],num_pairs_bygroup[44],num_X_bygroup[44],num_M_bygroup[44],num_P_bygroup[44],group_X_fitness(ptr,group_ptr,44),group_M_fitness(ptr,group_ptr,44),group_P_fitness(ptr,group_ptr,44));
            fprintf(fg46,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[45],num_infected_bygroup[45],num_pairs_bygroup[45],num_X_bygroup[45],num_M_bygroup[45],num_P_bygroup[45],group_X_fitness(ptr,group_ptr,45),group_M_fitness(ptr,group_ptr,45),group_P_fitness(ptr,group_ptr,45));
            fprintf(fg47,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[46],num_infected_bygroup[46],num_pairs_bygroup[46],num_X_bygroup[46],num_M_bygroup[46],num_P_bygroup[46],group_X_fitness(ptr,group_ptr,46),group_M_fitness(ptr,group_ptr,46),group_P_fitness(ptr,group_ptr,46));
            fprintf(fg48,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[47],num_infected_bygroup[47],num_pairs_bygroup[47],num_X_bygroup[47],num_M_bygroup[47],num_P_bygroup[47],group_X_fitness(ptr,group_ptr,47),group_M_fitness(ptr,group_ptr,47),group_P_fitness(ptr,group_ptr,47));
            fprintf(fg49,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[48],num_infected_bygroup[48],num_pairs_bygroup[48],num_X_bygroup[48],num_M_bygroup[48],num_P_bygroup[48],group_X_fitness(ptr,group_ptr,48),group_M_fitness(ptr,group_ptr,48),group_P_fitness(ptr,group_ptr,48));
            fprintf(fg50,"%d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f \n",t,(float)t/12,num_individuals_bygroup[49],num_infected_bygroup[49],num_pairs_bygroup[49],num_X_bygroup[49],num_M_bygroup[49],num_P_bygroup[49],group_X_fitness(ptr,group_ptr,49),group_M_fitness(ptr,group_ptr,49),group_P_fitness(ptr,group_ptr,49));

            /************************************************************************************/
            /************************************************************************************/
            /************************************************************************************/
            /*   Compute statistics on partnership distribution, before disease is introduced   */
            /************************************************************************************/
            /************************************************************************************/
            /************************************************************************************/

            if (t < disease_intro_time)
            {
                for (j = 0 ; j < 5 ; j ++)
                {
                    X_distrib_num_partners_temp[j]=0;
                    M_distrib_num_partners_temp[j]=0;
                    P_distrib_num_partners_temp[j]=0;
                }

                X_distrib_num_partners_count = 0;
                M_distrib_num_partners_count = 0;
                P_distrib_num_partners_count = 0;

                X_avg_num_partners_temp = 0;
                M_avg_num_partners_temp = 0;
                P_avg_num_partners_temp = 0;

                X_avg_num_partners_count = 0;
                M_avg_num_partners_count = 0;
                P_avg_num_partners_count = 0;

                for (k = 0 ; k < N ; k ++)
                {
                    if (ptr[k].active)
                    {
                        if (ptr[k].gender=='m')
                        {
                            if (ptr[k].strategy=='X')
                            {
                                X_avg_num_partners_temp += ptr[k].num_partners;
                                X_avg_num_partners_count ++;

                                if (ptr[k].num_partners==0)
                                    X_distrib_num_partners_temp[0]++;
                                else if (ptr[k].num_partners==1)
                                    X_distrib_num_partners_temp[1]++;
                                else if (ptr[k].num_partners==2)
                                    X_distrib_num_partners_temp[2]++;
                                else if (ptr[k].num_partners==3)
                                    X_distrib_num_partners_temp[3]++;
                                else if (ptr[k].num_partners>=4)
                                    X_distrib_num_partners_temp[4]++;

                                X_distrib_num_partners_count ++;
                            }
                            else if  (ptr[k].strategy=='M')
                            {
                                M_avg_num_partners_temp += ptr[k].num_partners;
                                M_avg_num_partners_count ++;


                                if (ptr[k].num_partners==0)
                                    M_distrib_num_partners_temp[0]++;
                                else if (ptr[k].num_partners==1)
                                    M_distrib_num_partners_temp[1]++;
                                else if (ptr[k].num_partners==2)
                                    M_distrib_num_partners_temp[2]++;
                                else if (ptr[k].num_partners==3)
                                    M_distrib_num_partners_temp[3]++;
                                else if (ptr[k].num_partners>=4)
                                    M_distrib_num_partners_temp[4]++;

                                M_distrib_num_partners_count ++;
                            }
                            else if  (ptr[k].strategy=='P')
                            {
                                P_avg_num_partners_temp += ptr[k].num_partners;
                                P_avg_num_partners_count ++;


                                if (ptr[k].num_partners==0)
                                    P_distrib_num_partners_temp[0]++;
                                else if (ptr[k].num_partners==1)
                                    P_distrib_num_partners_temp[1]++;
                                else if (ptr[k].num_partners==2)
                                    P_distrib_num_partners_temp[2]++;
                                else if (ptr[k].num_partners==3)
                                    P_distrib_num_partners_temp[3]++;
                                else if (ptr[k].num_partners>=4)
                                    P_distrib_num_partners_temp[4]++;

                                P_distrib_num_partners_count ++;
                            }
                        }

                    }
                }

                if (X_avg_num_partners_count > 0)
                {
                    X_avg_num_partners += (float)X_avg_num_partners_temp/X_avg_num_partners_count;
                    time_count_X_avg_num_partners ++;
                }
                if (M_avg_num_partners_count > 0)
                {
                    M_avg_num_partners += (float)M_avg_num_partners_temp/M_avg_num_partners_count;
                    time_count_M_avg_num_partners ++;
                }
                if (P_avg_num_partners_count > 0)
                {
                    P_avg_num_partners += (float)P_avg_num_partners_temp/P_avg_num_partners_count;
                    time_count_P_avg_num_partners ++;
                }

                for (k = 0 ; k < 5 ; k ++)
                {
                    if (X_distrib_num_partners_temp[k] > 0)
                    {
                        X_distrib_num_partners[k] += (float)X_distrib_num_partners_temp[k]/X_distrib_num_partners_count;
                        time_count_X_distrib_num_partners++;
                    }
                    if (M_distrib_num_partners_temp[k] > 0)
                    {
                        M_distrib_num_partners[k] += (float)M_distrib_num_partners_temp[k]/M_distrib_num_partners_count;
                        time_count_M_distrib_num_partners++;
                    }
                    if (P_distrib_num_partners_temp[k] > 0)
                    {
                        P_distrib_num_partners[k] += (float)P_distrib_num_partners_temp[k]/P_distrib_num_partners_count;
                        time_count_P_distrib_num_partners++;
                    }
                }
            }

            /*******************************************************************************************************/
            /*******************************************************************************************************/
            /*******************************************************************************************************/
            /*******************************************************************************************************/
            /*          Then, if disease has been introduced, compute average statistics for other variables       */
            /*******************************************************************************************************/
            /*******************************************************************************************************/
            /*******************************************************************************************************/
            /*******************************************************************************************************/

            if (t > disease_intro_time)
            {
                /****************************************/
                /* Initialize all counters and averages */
                /****************************************/

                infertility_rate_X = 0;
                infertility_rate_M = 0;
                infertility_rate_P = 0;

                num_infertile_X = 0;
                num_infertile_M = 0;
                num_infertile_P = 0;

                num_X_men=0;
                num_M_men=0;
                num_P_men=0;

                num_X = 0;
                num_M = 0;
                num_P = 0;

                num_X_infected = 0;
                num_M_infected = 0;
                num_P_infected = 0;

                num_X_groups=0;
                num_M_groups=0;
                num_P_groups=0;
                num_groups=0;

                num_infected = 0;
                num_individuals = 0;

                num_X_infected_in_X_group = 0;
                num_X_infected_in_M_group = 0;
                num_X_infected_in_P_group = 0;
                num_M_infected_in_X_group = 0;
                num_M_infected_in_M_group = 0;
                num_M_infected_in_P_group = 0;
                num_P_infected_in_X_group = 0;
                num_P_infected_in_M_group = 0;
                num_P_infected_in_P_group = 0;

                num_X_in_X_group = 0;
                num_X_in_M_group = 0;
                num_X_in_P_group = 0;
                num_M_in_X_group = 0;
                num_M_in_M_group = 0;
                num_M_in_P_group = 0;
                num_P_in_X_group = 0;
                num_P_in_M_group = 0;
                num_P_in_P_group = 0;

                X_group_size_temp = 0;
                M_group_size_temp = 0;
                P_group_size_temp = 0;
                total_group_size_temp = 0;

                X_group_size_counter = 0;
                M_group_size_counter = 0;
                P_group_size_counter = 0;
                total_group_size_counter = 0;

                X_avg_fitness_temp = 0;
                M_avg_fitness_temp = 0;
                P_avg_fitness_temp = 0;

                X_avg_fitness_count = 0;
                M_avg_fitness_count = 0;
                P_avg_fitness_count = 0;

                /***************************************************/
                /* go through each group and update group counters */
                /***************************************************/

                for (j = 0 ; j < 50 ; j ++)
                {
                    if (num_X_in_group(group_ptr, ptr, j) > num_P_in_group(group_ptr, ptr, j) &&  num_X_in_group(group_ptr, ptr, j) > num_M_in_group(group_ptr, ptr, j))
                    {
                        num_X_groups++;

                        X_group_size_temp += group_ptr[j].size;
                        X_group_size_counter ++;

                        total_group_size_temp += group_ptr[j].size;
                        total_group_size_counter++;
                        num_groups ++;


                    }
                    else if (num_P_in_group(group_ptr, ptr, j) > num_X_in_group(group_ptr, ptr, j) &&  num_P_in_group(group_ptr, ptr, j) > num_M_in_group(group_ptr, ptr, j))
                    {
                        num_P_groups++;

                        P_group_size_temp += group_ptr[j].size;
                        P_group_size_counter ++;

                        total_group_size_temp += group_ptr[j].size;
                        total_group_size_counter++;
                        num_groups ++;

                    }
                    else if (num_M_in_group(group_ptr, ptr, j) > num_X_in_group(group_ptr, ptr, j) &&  num_M_in_group(group_ptr, ptr, j) > num_P_in_group(group_ptr, ptr, j))
                    {
                        num_M_groups++;

                        M_group_size_temp += group_ptr[j].size;
                        M_group_size_counter ++;

                        total_group_size_temp += group_ptr[j].size;
                        total_group_size_counter++;
                        num_groups ++;

                    }

                    num_X += num_X_in_group(group_ptr, ptr, j);
                    num_M += num_M_in_group(group_ptr, ptr, j);
                    num_P += num_P_in_group(group_ptr, ptr, j);
                }

                /*************************************/
                /*       X, M, P Group Sizes         */
                /*************************************/

                if (t > numsteps - 1000*12)
                {
                if (X_group_size_counter > 0)
                {
                    X_group_size += (float)X_group_size_temp/X_group_size_counter;
                    time_count_X_group_size ++;
                }
                if (M_group_size_counter > 0)
                {
                    M_group_size += (float)M_group_size_temp/M_group_size_counter;
                    time_count_M_group_size ++;
                }
                if (P_group_size_counter > 0)
                {
                    P_group_size += (float)P_group_size_temp/P_group_size_counter;
                    time_count_P_group_size ++;
                }
                if (total_group_size_counter > 0)
                {
                    total_group_size += (float)total_group_size_temp/total_group_size_counter;
                    time_count_total_group_size ++;
                }
                }

                /****************************************************/
                /* Then, go through each person and update counters */
                /****************************************************/

                for (k = 0 ; k < N ; k ++)
                {
                    if (ptr[k].active)
                    {
                        num_individuals++;

                        if (ptr[k].strategy=='X' && ptr[k].gender=='m')
                        {
                            num_X_men++;
                            if (ptr[k].fertile==0)
                                num_infertile_X++;
                        }
                        else if (ptr[k].strategy=='M' && ptr[k].gender=='m')
                        {
                            num_M_men++;
                            if (ptr[k].fertile==0)
                                num_infertile_M++;
                        }
                        else if (ptr[k].strategy=='P' && ptr[k].gender=='m')
                        {
                            num_P_men++;
                            if (ptr[k].fertile==0)
                                num_infertile_P++;
                        }

                        current_group_ID = ptr[k].group;

                        if (num_X_in_group(group_ptr, ptr, current_group_ID) > num_P_in_group(group_ptr, ptr, current_group_ID) && num_X_in_group(group_ptr, ptr, current_group_ID) > num_M_in_group(group_ptr, ptr, current_group_ID))
                        {
                            if (ptr[k].strategy=='X')
                            {
                                num_X_in_X_group ++;
                                if (ptr[k].status=='i' || ptr[k].status=='a')
                                    num_X_infected_in_X_group++;
                            }
                            else if (ptr[k].strategy=='P')
                            {
                                num_P_in_X_group ++;
                                if (ptr[k].status=='i' || ptr[k].status=='a')
                                    num_P_infected_in_X_group++;
                            }
                            else if (ptr[k].strategy=='M')
                            {
                                num_M_in_X_group ++;
                                if (ptr[k].status=='i' || ptr[k].status=='a')
                                    num_M_infected_in_X_group++;
                            }
                        }
                        else if (num_P_in_group(group_ptr, ptr, current_group_ID) > num_X_in_group(group_ptr, ptr, current_group_ID) && num_P_in_group(group_ptr, ptr, current_group_ID) > num_M_in_group(group_ptr, ptr, current_group_ID))
                        {
                            if (ptr[k].strategy=='X')
                            {
                                num_X_in_P_group ++;
                                if (ptr[k].status=='i' || ptr[k].status=='a')
                                    num_X_infected_in_P_group++;
                            }
                            else if (ptr[k].strategy=='P')
                            {
                                num_P_in_P_group ++;
                                if (ptr[k].status=='i' || ptr[k].status=='a')
                                    num_P_infected_in_P_group++;
                            }
                            else if (ptr[k].strategy=='M')
                            {
                                num_M_in_P_group ++;
                                if (ptr[k].status=='i' || ptr[k].status=='a')
                                    num_M_infected_in_P_group++;
                            }
                        }
                        else if (num_M_in_group(group_ptr, ptr, current_group_ID) > num_X_in_group(group_ptr, ptr, current_group_ID) && num_M_in_group(group_ptr, ptr, current_group_ID) > num_P_in_group(group_ptr, ptr, current_group_ID))
                        {
                            if (ptr[k].strategy=='X')
                            {
                                num_X_in_M_group ++;
                                if (ptr[k].status=='i' || ptr[k].status=='a')
                                    num_X_infected_in_M_group++;
                            }
                            else if (ptr[k].strategy=='P')
                            {
                                num_P_in_M_group ++;
                                if (ptr[k].status=='i' || ptr[k].status=='a')
                                    num_P_infected_in_M_group++;
                            }
                            else if (ptr[k].strategy=='M')
                            {
                                num_M_in_M_group ++;
                                if (ptr[k].status=='i' || ptr[k].status=='a')
                                    num_M_infected_in_M_group++;
                            }
                        }


                        if (ptr[k].status=='i' || ptr[k].status=='a')
                        {
                            num_infected ++;
                            if (ptr[k].strategy=='X')
                                num_X_infected++;
                            else if (ptr[k].strategy=='M')
                                num_M_infected++;
                            else if (ptr[k].strategy=='P')
                                num_P_infected++;
                        }

                        if (ptr[k].gender=='m')
                        {
                            if (ptr[k].strategy=='X')
                            {
                                X_avg_fitness_temp += ptr[k].fitness;
                                X_avg_fitness_count ++;

                            }
                            else if  (ptr[k].strategy=='M')
                            {
                                M_avg_fitness_temp += ptr[k].fitness;
                                M_avg_fitness_count ++;

                            }
                            else if  (ptr[k].strategy=='P')
                            {
                                P_avg_fitness_temp += ptr[k].fitness;
                                P_avg_fitness_count ++;
                            }
                        }
                    }
                }

                /**************************************/
                /* Start computing average statistics */
                /**************************************/

                if (num_individuals==0)
                    num_individuals=1;

                if (X_avg_fitness_count > 0)
                {
                    X_avg_fitness += (float)X_avg_fitness_temp/X_avg_fitness_count;
                    time_count_X_fitness ++;
                }
                if (M_avg_fitness_count > 0)
                {
                    M_avg_fitness += (float)M_avg_fitness_temp/M_avg_fitness_count;
                    time_count_M_fitness ++;
                }
                if (P_avg_fitness_count > 0)
                {
                    P_avg_fitness += (float)P_avg_fitness_temp/P_avg_fitness_count;
                    time_count_P_fitness ++;
                }

                if (num_X_men==0)
                    infertility_rate_X=-1;
                else
                    infertility_rate_X = (float)num_infertile_X/num_X_men;

                if (num_M_men==0)
                    infertility_rate_M=-1;
                else
                    infertility_rate_M = (float)num_infertile_M/num_M_men;

                if (num_P_men==0)
                    infertility_rate_P=-1;
                else
                    infertility_rate_P = (float)num_infertile_P/num_P_men;

                /*********************************************************************/
                /* Print out time series of number of groups, number of infected ... */
                /*********************************************************************/

                fprintf(f4,"%d || %d %d %d || %f %f %f || %f %f %f || %d %d \n",t,num_X_groups,num_M_groups,num_P_groups,(float)num_X_infected/num_X,(float)num_M_infected/num_M,(float)num_P_infected/num_P,infertility_rate_X,infertility_rate_M,infertility_rate_P,num_infected,num_individuals);

                fprintf(f3,"%d, %f, %f, %f, %f \n",t,(float)t/12,(float)num_X_infected/num_X,(float)num_M_infected/num_M,(float)num_P_infected/num_P);

                /*********************************************************/
                /* Prevalence in X, M, P individuals across all groups */
                /*********************************************************/

                if (t > numsteps - 1000*12)
                {
                if (num_X > 0)
                {
                    X_prevalence += (float)num_X_infected/num_X;
                    time_count_X_prevalence ++;
                }
                if (num_M > 0)
                {
                    M_prevalence += (float)num_M_infected/num_M;
                    time_count_M_prevalence ++;
                }
                if (num_P > 0)
                {
                    P_prevalence += (float)num_P_infected/num_P;
                    time_count_P_prevalence ++;
                }
                if (num_X + num_M + num_P > 0)
                {
                    total_prevalence += (float)(num_X_infected + num_M_infected + num_P_infected)/(num_X + num_M + num_P);
                    time_count_total_prevalence ++;
                }
                }

                /*******************************************************/
                /* Prevalence in X, M, P individuals in X, M, P groups */
                /*******************************************************/

                if (t > numsteps - 1000*12)
                {
                if (num_X_in_X_group>0)
                {
                    X_prevalence_in_X_group += (float)num_X_infected_in_X_group/num_X_in_X_group;
                    time_count_prev_X_in_X ++;
                }
                if (num_M_in_X_group>0)
                {
                    M_prevalence_in_X_group += (float)num_M_infected_in_X_group/num_M_in_X_group;
                    time_count_prev_M_in_X ++;
                }
                if (num_P_in_X_group>0)
                {
                    P_prevalence_in_X_group += (float)num_P_infected_in_X_group/num_P_in_X_group;
                    time_count_prev_P_in_X ++;
                }
                if (num_X_in_X_group + num_M_in_X_group + num_P_in_X_group > 0)
                {
                    prevalence_in_X_group += ((float)num_X_infected_in_X_group + (float)num_M_infected_in_X_group + (float)num_P_infected_in_X_group)/(num_X_in_X_group + num_M_in_X_group + num_P_in_X_group);
                    time_count_prev_in_X ++;
                }

                if (num_X_in_M_group>0)
                {
                    X_prevalence_in_M_group += (float)num_X_infected_in_M_group/num_X_in_M_group;
                    time_count_prev_X_in_M ++;
                }
                if (num_M_in_M_group>0)
                {
                    M_prevalence_in_M_group += (float)num_M_infected_in_M_group/num_M_in_M_group;
                    time_count_prev_M_in_M ++;
                }
                if (num_P_in_M_group>0)
                {
                    P_prevalence_in_M_group += (float)num_P_infected_in_M_group/num_P_in_M_group;
                    time_count_prev_P_in_M ++;
                }
                if (num_X_in_M_group + num_M_in_M_group + num_P_in_M_group > 0)
                {
                    prevalence_in_M_group += ((float)num_X_infected_in_M_group + (float)num_M_infected_in_M_group + (float)num_P_infected_in_M_group)/(num_X_in_M_group + num_M_in_M_group + num_P_in_M_group);
                    time_count_prev_in_M ++;
                }

                if (num_X_in_P_group>0)
                {
                    X_prevalence_in_P_group += (float)num_X_infected_in_P_group/num_X_in_P_group;
                    time_count_prev_X_in_P ++;
                }
                if (num_M_in_P_group>0)
                {
                    M_prevalence_in_P_group += (float)num_M_infected_in_P_group/num_M_in_P_group;
                    time_count_prev_M_in_P ++;
                }
                if (num_P_in_P_group>0)
                {
                    P_prevalence_in_P_group += (float)num_P_infected_in_P_group/num_P_in_P_group;
                    time_count_prev_P_in_P ++;
                }
                if (num_X_in_P_group + num_M_in_P_group + num_P_in_P_group > 0)
                {
                    prevalence_in_P_group += ((float)num_X_infected_in_P_group + (float)num_M_infected_in_P_group + (float)num_P_infected_in_P_group)/(num_X_in_P_group + num_M_in_P_group + num_P_in_P_group);
                    time_count_prev_in_P ++;
                }
                }
            }
            time_count ++;
        }
    }

    /******************************/
    /******************************/
    /* close main simulation loop */
    /******************************/
    /******************************/

    /******************************/
	/*************************/
	/* print out final state */
	/*************************/
    /******************************/

	//		fprintf(f2,"node, active, num_ptnrs, gender, status, group, strategy, fitness, partner1, partner2, partner3, partner4, partner5, partner6, partner7, partner8, partner9, partner10 \n");

	//		for (k = 0 ; k < N ; k ++)
	//		{
	//			printf("node=%d, active=%d, num_ptnrs=%d || gen=%c status=%c || gp=%d || str=%c || %d %d %d %d %d %d %d %d %d %d \n",k,ptr[k].active,ptr[k].num_partners,ptr[k].gender,ptr[k].status,ptr[k].group,ptr[k].strategy,ptr[k].partner[0],ptr[k].partner[1],ptr[k].partner[2],ptr[k].partner[3],ptr[k].partner[4],ptr[k].partner[5],ptr[k].partner[6],ptr[k].partner[7],ptr[k].partner[8],ptr[k].partner[9]);
	//			fprintf(f2,"%d, %d, %d, %c, %c, %d, %c, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d  \n",k,ptr[k].active,ptr[k].num_partners,ptr[k].gender,ptr[k].status,ptr[k].group,ptr[k].strategy,ptr[k].fitness,ptr[k].partner[0],ptr[k].partner[1],ptr[k].partner[2],ptr[k].partner[3],ptr[k].partner[4],ptr[k].partner[5],ptr[k].partner[6],ptr[k].partner[7],ptr[k].partner[8],ptr[k].partner[9]);
	//		}

	/********************************************/
	/* compute average fitness by strategy type */
	/********************************************/

	average_X_fitness=0;
	average_M_fitness=0;
	average_P_fitness=0;

	num_X = num_M = num_P = 0;

	stdev_X_fitness=0;
	stdev_M_fitness=0;
	stdev_P_fitness=0;

	for (k = 0 ; k < N ; k ++)
	{
		if (ptr[k].active)
		{
			if (ptr[k].strategy=='X')
			{
				average_X_fitness += ptr[k].fitness;
				num_X ++;
			}
			else if (ptr[k].strategy=='M')
			{
				average_M_fitness += ptr[k].fitness;
				num_M ++;
			}
			else if (ptr[k].strategy=='P')
			{
				average_P_fitness += ptr[k].fitness;
				num_P ++;
			}
		}
	}

	for (k = 0 ; k < N ; k ++)
	{
		if (ptr[k].active)
		{
			if (ptr[k].strategy=='X')
			{
				stdev_X_fitness += (ptr[k].fitness-average_X_fitness/num_X)*(ptr[k].fitness-average_X_fitness/num_X);
			}
			else if (ptr[k].strategy=='M')
			{
				stdev_M_fitness += (ptr[k].fitness-average_M_fitness/num_M)*(ptr[k].fitness-average_M_fitness/num_M);
			}
			else if (ptr[k].strategy=='P')
			{
				stdev_P_fitness += (ptr[k].fitness-average_P_fitness/num_P)*(ptr[k].fitness-average_P_fitness/num_P);
			}
		}
	}

    fprintf(ftemp,"%f, ",total_group_size/time_count);

    fprintf(f4,"average number of partners of X individuals at beginning = %f \n",X_avg_num_partners/time_count_X_avg_num_partners);
    fprintf(f4,"average number of partners of M individuals at beginning = %f \n",M_avg_num_partners/time_count_M_avg_num_partners);
    fprintf(f4,"average number of partners of P individuals at beginning = %f \n",P_avg_num_partners/time_count_P_avg_num_partners);

    for (k=1; k<=4; k++)
    {
        X_part_distrib_output[k] = 0;
        M_part_distrib_output[k] = 0;
        P_part_distrib_output[k] = 0;
    }
    for (k=1; k<=4; k++)
    {
        X_part_distrib_output[k] = X_distrib_num_partners[k]/(X_distrib_num_partners[1]+X_distrib_num_partners[2]+X_distrib_num_partners[3]+X_distrib_num_partners[4]);
        M_part_distrib_output[k] = M_distrib_num_partners[k]/(M_distrib_num_partners[1]+M_distrib_num_partners[2]+M_distrib_num_partners[3]+M_distrib_num_partners[4]);
        P_part_distrib_output[k] = P_distrib_num_partners[k]/(P_distrib_num_partners[1]+P_distrib_num_partners[2]+P_distrib_num_partners[3]+P_distrib_num_partners[4]);
    }

    fprintf(f4,"distribution of num partners of X families at beginning = %f %f %f %f %f \n",X_part_distrib_output[0],X_part_distrib_output[1],X_part_distrib_output[2],X_part_distrib_output[3],X_part_distrib_output[4]);
    fprintf(f4,"distribution of num partners of M families at beginning = %f %f %f %f %f \n",M_part_distrib_output[0],M_part_distrib_output[1],M_part_distrib_output[2],M_part_distrib_output[3],M_part_distrib_output[4]);
    fprintf(f4,"distribution of num partners of P families at beginning = %f %f %f %f %f \n",P_part_distrib_output[0],P_part_distrib_output[1],P_part_distrib_output[2],P_part_distrib_output[3],P_part_distrib_output[4]);

    fprintf(f4,"average X fitness at end = %f, st. dev = %f \n",average_X_fitness/num_X,sqrt(stdev_X_fitness/num_X));
    fprintf(f4,"average M fitness at end = %f, st. dev = %f  \n",average_M_fitness/num_M,sqrt(stdev_M_fitness/num_M));
    fprintf(f4,"average P fitness at end = %f, st. dev = %f  \n",average_P_fitness/num_P,sqrt(stdev_P_fitness/num_P));

    fprintf(f4,"average X fitness throughout = %f \n",X_avg_fitness/time_count_X_fitness);
    fprintf(f4,"average M fitness throughout = %f \n",M_avg_fitness/time_count_M_fitness);
    fprintf(f4,"average P fitness throughout = %f \n",P_avg_fitness/time_count_P_fitness);

    fprintf(f4,"average total prevalence throughout = %f\n", total_prevalence/time_count_total_prevalence);
	fprintf(f4,"average X prevalence throughout = %f\n", X_prevalence/time_count_X_prevalence);
	fprintf(f4,"average M prevalence throughout = %f\n", M_prevalence/time_count_M_prevalence);
	fprintf(f4,"average P prevalence throughout = %f\n", P_prevalence/time_count_P_prevalence);

	fprintf(f4,"average total group size throughout = %f \n", total_group_size/time_count_total_group_size);
	fprintf(f4,"average X group size throughout = %f \n", X_group_size/time_count_X_group_size);
	fprintf(f4,"average M group size throughout = %f \n", M_group_size/time_count_M_group_size);
	fprintf(f4,"average P group size throughout = %f \n", P_group_size/time_count_P_group_size);

	fprintf(f4,"average prevalence of X individuals in X groups throughout = %f \n",X_prevalence_in_X_group/time_count_prev_X_in_X);
	fprintf(f4,"average prevalence of M individuals in X groups throughout = %f \n",M_prevalence_in_X_group/time_count_prev_M_in_X);
	fprintf(f4,"average prevalence of P individuals in X groups throughout = %f \n",P_prevalence_in_X_group/time_count_prev_P_in_X);
	fprintf(f4,"average prevalence in X groups throughout = %f \n",prevalence_in_X_group/time_count_prev_in_X);
	fprintf(f4,"average prevalence of X individuals in M groups throughout = %f \n",X_prevalence_in_M_group/time_count_prev_X_in_M);
	fprintf(f4,"average prevalence of M individuals in M groups throughout = %f \n",M_prevalence_in_M_group/time_count_prev_M_in_M);
	fprintf(f4,"average prevalence of P individuals in M groups throughout = %f \n",P_prevalence_in_M_group/time_count_prev_P_in_M);
	fprintf(f4,"average prevalence in M groups throughout = %f \n",prevalence_in_M_group/time_count_prev_in_M);
	fprintf(f4,"average prevalence of X individuals in P groups throughout = %f \n",X_prevalence_in_P_group/time_count_prev_X_in_P);
	fprintf(f4,"average prevalence of M individuals in P groups throughout = %f \n",M_prevalence_in_P_group/time_count_prev_M_in_P);
	fprintf(f4,"average prevalence of P individuals in P groups throughout = %f \n",P_prevalence_in_P_group/time_count_prev_P_in_P);
	fprintf(f4,"average prevalence in P groups throughout = %f \n",prevalence_in_P_group/time_count_prev_in_P);

	fprintf(f4,"group,     X,     M,     P,   NUM,   INF, X fit, M fit, P fit\n");
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f \n",0, num_X_in_group(group_ptr, ptr, 0), num_M_in_group(group_ptr, ptr, 0), num_P_in_group(group_ptr, ptr, 0), num_in_group(group_ptr, ptr, 0),  num_infected_in_group(group_ptr, ptr, 0), group_X_fitness(ptr,group_ptr,0), group_M_fitness(ptr,group_ptr,0), group_P_fitness(ptr,group_ptr,0));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",1, num_X_in_group(group_ptr, ptr, 1), num_M_in_group(group_ptr, ptr, 1), num_P_in_group(group_ptr, ptr, 1), num_in_group(group_ptr, ptr, 1),  num_infected_in_group(group_ptr, ptr, 1), group_X_fitness(ptr,group_ptr,1), group_M_fitness(ptr,group_ptr,1), group_P_fitness(ptr,group_ptr,1));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",2, num_X_in_group(group_ptr, ptr, 2), num_M_in_group(group_ptr, ptr, 2), num_P_in_group(group_ptr, ptr, 2), num_in_group(group_ptr, ptr, 2),  num_infected_in_group(group_ptr, ptr, 2), group_X_fitness(ptr,group_ptr,2), group_M_fitness(ptr,group_ptr,2), group_P_fitness(ptr,group_ptr,2));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",3, num_X_in_group(group_ptr, ptr, 3), num_M_in_group(group_ptr, ptr, 3), num_P_in_group(group_ptr, ptr, 3), num_in_group(group_ptr, ptr, 3),  num_infected_in_group(group_ptr, ptr, 3), group_X_fitness(ptr,group_ptr,3), group_M_fitness(ptr,group_ptr,3), group_P_fitness(ptr,group_ptr,3));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",4, num_X_in_group(group_ptr, ptr, 4), num_M_in_group(group_ptr, ptr, 4), num_P_in_group(group_ptr, ptr, 4), num_in_group(group_ptr, ptr, 4),  num_infected_in_group(group_ptr, ptr, 4), group_X_fitness(ptr,group_ptr,4), group_M_fitness(ptr,group_ptr,4), group_P_fitness(ptr,group_ptr,4));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",5, num_X_in_group(group_ptr, ptr, 5), num_M_in_group(group_ptr, ptr, 5), num_P_in_group(group_ptr, ptr, 5), num_in_group(group_ptr, ptr, 5),  num_infected_in_group(group_ptr, ptr, 5), group_X_fitness(ptr,group_ptr,5), group_M_fitness(ptr,group_ptr,5), group_P_fitness(ptr,group_ptr,5));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",6, num_X_in_group(group_ptr, ptr, 6), num_M_in_group(group_ptr, ptr, 6), num_P_in_group(group_ptr, ptr, 6), num_in_group(group_ptr, ptr, 6),  num_infected_in_group(group_ptr, ptr, 6), group_X_fitness(ptr,group_ptr,6), group_M_fitness(ptr,group_ptr,6), group_P_fitness(ptr,group_ptr,6));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",7, num_X_in_group(group_ptr, ptr, 7), num_M_in_group(group_ptr, ptr, 7), num_P_in_group(group_ptr, ptr, 7), num_in_group(group_ptr, ptr, 7),  num_infected_in_group(group_ptr, ptr, 7), group_X_fitness(ptr,group_ptr,7), group_M_fitness(ptr,group_ptr,7), group_P_fitness(ptr,group_ptr,7));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",8, num_X_in_group(group_ptr, ptr, 8), num_M_in_group(group_ptr, ptr, 8), num_P_in_group(group_ptr, ptr, 8), num_in_group(group_ptr, ptr, 8),  num_infected_in_group(group_ptr, ptr, 8), group_X_fitness(ptr,group_ptr,8), group_M_fitness(ptr,group_ptr,8), group_P_fitness(ptr,group_ptr,8));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",9, num_X_in_group(group_ptr, ptr, 9), num_M_in_group(group_ptr, ptr, 9), num_P_in_group(group_ptr, ptr, 9), num_in_group(group_ptr, ptr, 9),  num_infected_in_group(group_ptr, ptr, 9), group_X_fitness(ptr,group_ptr,9), group_M_fitness(ptr,group_ptr,9), group_P_fitness(ptr,group_ptr,9));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",10, num_X_in_group(group_ptr, ptr, 10), num_M_in_group(group_ptr, ptr, 10), num_P_in_group(group_ptr, ptr, 10), num_in_group(group_ptr, ptr, 10),  num_infected_in_group(group_ptr, ptr, 10), group_X_fitness(ptr,group_ptr,10), group_M_fitness(ptr,group_ptr,10), group_P_fitness(ptr,group_ptr,10));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",11, num_X_in_group(group_ptr, ptr, 11), num_M_in_group(group_ptr, ptr, 11), num_P_in_group(group_ptr, ptr, 11), num_in_group(group_ptr, ptr, 11),  num_infected_in_group(group_ptr, ptr, 11), group_X_fitness(ptr,group_ptr,11), group_M_fitness(ptr,group_ptr,11), group_P_fitness(ptr,group_ptr,11));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",12, num_X_in_group(group_ptr, ptr, 12), num_M_in_group(group_ptr, ptr, 12), num_P_in_group(group_ptr, ptr, 12), num_in_group(group_ptr, ptr, 12),  num_infected_in_group(group_ptr, ptr, 12), group_X_fitness(ptr,group_ptr,12), group_M_fitness(ptr,group_ptr,12), group_P_fitness(ptr,group_ptr,12));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",13, num_X_in_group(group_ptr, ptr, 13), num_M_in_group(group_ptr, ptr, 13), num_P_in_group(group_ptr, ptr, 13), num_in_group(group_ptr, ptr, 13),  num_infected_in_group(group_ptr, ptr, 13), group_X_fitness(ptr,group_ptr,13), group_M_fitness(ptr,group_ptr,13), group_P_fitness(ptr,group_ptr,13));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",14, num_X_in_group(group_ptr, ptr, 14), num_M_in_group(group_ptr, ptr, 14), num_P_in_group(group_ptr, ptr, 14), num_in_group(group_ptr, ptr, 14),  num_infected_in_group(group_ptr, ptr, 14), group_X_fitness(ptr,group_ptr,14), group_M_fitness(ptr,group_ptr,14), group_P_fitness(ptr,group_ptr,14));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",15, num_X_in_group(group_ptr, ptr, 15), num_M_in_group(group_ptr, ptr, 15), num_P_in_group(group_ptr, ptr, 15), num_in_group(group_ptr, ptr, 15),  num_infected_in_group(group_ptr, ptr, 15), group_X_fitness(ptr,group_ptr,15), group_M_fitness(ptr,group_ptr,15), group_P_fitness(ptr,group_ptr,15));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",16, num_X_in_group(group_ptr, ptr, 16), num_M_in_group(group_ptr, ptr, 16), num_P_in_group(group_ptr, ptr, 16), num_in_group(group_ptr, ptr, 16),  num_infected_in_group(group_ptr, ptr, 16), group_X_fitness(ptr,group_ptr,16), group_M_fitness(ptr,group_ptr,16), group_P_fitness(ptr,group_ptr,16));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",17, num_X_in_group(group_ptr, ptr, 17), num_M_in_group(group_ptr, ptr, 17), num_P_in_group(group_ptr, ptr, 17), num_in_group(group_ptr, ptr, 17),  num_infected_in_group(group_ptr, ptr, 17), group_X_fitness(ptr,group_ptr,17), group_M_fitness(ptr,group_ptr,17), group_P_fitness(ptr,group_ptr,17));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",18, num_X_in_group(group_ptr, ptr, 18), num_M_in_group(group_ptr, ptr, 18), num_P_in_group(group_ptr, ptr, 18), num_in_group(group_ptr, ptr, 18),  num_infected_in_group(group_ptr, ptr, 18), group_X_fitness(ptr,group_ptr,18), group_M_fitness(ptr,group_ptr,18), group_P_fitness(ptr,group_ptr,18));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",19, num_X_in_group(group_ptr, ptr, 19), num_M_in_group(group_ptr, ptr, 19), num_P_in_group(group_ptr, ptr, 19), num_in_group(group_ptr, ptr, 19),  num_infected_in_group(group_ptr, ptr, 19), group_X_fitness(ptr,group_ptr,19), group_M_fitness(ptr,group_ptr,19), group_P_fitness(ptr,group_ptr,19));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",20, num_X_in_group(group_ptr, ptr, 20), num_M_in_group(group_ptr, ptr, 20), num_P_in_group(group_ptr, ptr, 20), num_in_group(group_ptr, ptr, 20),  num_infected_in_group(group_ptr, ptr, 20), group_X_fitness(ptr,group_ptr,20), group_M_fitness(ptr,group_ptr,20), group_P_fitness(ptr,group_ptr,20));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",21, num_X_in_group(group_ptr, ptr, 21), num_M_in_group(group_ptr, ptr, 21), num_P_in_group(group_ptr, ptr, 21), num_in_group(group_ptr, ptr, 21),  num_infected_in_group(group_ptr, ptr, 21), group_X_fitness(ptr,group_ptr,21), group_M_fitness(ptr,group_ptr,21), group_P_fitness(ptr,group_ptr,21));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",22, num_X_in_group(group_ptr, ptr, 22), num_M_in_group(group_ptr, ptr, 22), num_P_in_group(group_ptr, ptr, 22), num_in_group(group_ptr, ptr, 22),  num_infected_in_group(group_ptr, ptr, 22), group_X_fitness(ptr,group_ptr,22), group_M_fitness(ptr,group_ptr,22), group_P_fitness(ptr,group_ptr,22));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",23, num_X_in_group(group_ptr, ptr, 23), num_M_in_group(group_ptr, ptr, 23), num_P_in_group(group_ptr, ptr, 23), num_in_group(group_ptr, ptr, 23),  num_infected_in_group(group_ptr, ptr, 23), group_X_fitness(ptr,group_ptr,23), group_M_fitness(ptr,group_ptr,23), group_P_fitness(ptr,group_ptr,23));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",24, num_X_in_group(group_ptr, ptr, 24), num_M_in_group(group_ptr, ptr, 24), num_P_in_group(group_ptr, ptr, 24), num_in_group(group_ptr, ptr, 24),  num_infected_in_group(group_ptr, ptr, 24), group_X_fitness(ptr,group_ptr,24), group_M_fitness(ptr,group_ptr,24), group_P_fitness(ptr,group_ptr,24));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",25, num_X_in_group(group_ptr, ptr, 25), num_M_in_group(group_ptr, ptr, 25), num_P_in_group(group_ptr, ptr, 25), num_in_group(group_ptr, ptr, 25),  num_infected_in_group(group_ptr, ptr, 25), group_X_fitness(ptr,group_ptr,25), group_M_fitness(ptr,group_ptr,25), group_P_fitness(ptr,group_ptr,25));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",26, num_X_in_group(group_ptr, ptr, 26), num_M_in_group(group_ptr, ptr, 26), num_P_in_group(group_ptr, ptr, 26), num_in_group(group_ptr, ptr, 26),  num_infected_in_group(group_ptr, ptr, 26), group_X_fitness(ptr,group_ptr,26), group_M_fitness(ptr,group_ptr,26), group_P_fitness(ptr,group_ptr,26));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",27, num_X_in_group(group_ptr, ptr, 27), num_M_in_group(group_ptr, ptr, 27), num_P_in_group(group_ptr, ptr, 27), num_in_group(group_ptr, ptr, 27),  num_infected_in_group(group_ptr, ptr, 27), group_X_fitness(ptr,group_ptr,27), group_M_fitness(ptr,group_ptr,27), group_P_fitness(ptr,group_ptr,27));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",28, num_X_in_group(group_ptr, ptr, 28), num_M_in_group(group_ptr, ptr, 28), num_P_in_group(group_ptr, ptr, 28), num_in_group(group_ptr, ptr, 28),  num_infected_in_group(group_ptr, ptr, 28), group_X_fitness(ptr,group_ptr,28), group_M_fitness(ptr,group_ptr,28), group_P_fitness(ptr,group_ptr,28));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",29, num_X_in_group(group_ptr, ptr, 29), num_M_in_group(group_ptr, ptr, 29), num_P_in_group(group_ptr, ptr, 29), num_in_group(group_ptr, ptr, 29),  num_infected_in_group(group_ptr, ptr, 29), group_X_fitness(ptr,group_ptr,29), group_M_fitness(ptr,group_ptr,29), group_P_fitness(ptr,group_ptr,29));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",30, num_X_in_group(group_ptr, ptr, 30), num_M_in_group(group_ptr, ptr, 30), num_P_in_group(group_ptr, ptr, 30), num_in_group(group_ptr, ptr, 30),  num_infected_in_group(group_ptr, ptr, 30), group_X_fitness(ptr,group_ptr,30), group_M_fitness(ptr,group_ptr,30), group_P_fitness(ptr,group_ptr,30));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",31, num_X_in_group(group_ptr, ptr, 31), num_M_in_group(group_ptr, ptr, 31), num_P_in_group(group_ptr, ptr, 31), num_in_group(group_ptr, ptr, 31),  num_infected_in_group(group_ptr, ptr, 31), group_X_fitness(ptr,group_ptr,31), group_M_fitness(ptr,group_ptr,31), group_P_fitness(ptr,group_ptr,31));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",32, num_X_in_group(group_ptr, ptr, 32), num_M_in_group(group_ptr, ptr, 32), num_P_in_group(group_ptr, ptr, 32), num_in_group(group_ptr, ptr, 32),  num_infected_in_group(group_ptr, ptr, 32), group_X_fitness(ptr,group_ptr,32), group_M_fitness(ptr,group_ptr,32), group_P_fitness(ptr,group_ptr,32));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",33, num_X_in_group(group_ptr, ptr, 33), num_M_in_group(group_ptr, ptr, 33), num_P_in_group(group_ptr, ptr, 33), num_in_group(group_ptr, ptr, 33),  num_infected_in_group(group_ptr, ptr, 33), group_X_fitness(ptr,group_ptr,33), group_M_fitness(ptr,group_ptr,33), group_P_fitness(ptr,group_ptr,33));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",34, num_X_in_group(group_ptr, ptr, 34), num_M_in_group(group_ptr, ptr, 34), num_P_in_group(group_ptr, ptr, 34), num_in_group(group_ptr, ptr, 34),  num_infected_in_group(group_ptr, ptr, 34), group_X_fitness(ptr,group_ptr,34), group_M_fitness(ptr,group_ptr,34), group_P_fitness(ptr,group_ptr,34));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",35, num_X_in_group(group_ptr, ptr, 35), num_M_in_group(group_ptr, ptr, 35), num_P_in_group(group_ptr, ptr, 35), num_in_group(group_ptr, ptr, 35),  num_infected_in_group(group_ptr, ptr, 35), group_X_fitness(ptr,group_ptr,35), group_M_fitness(ptr,group_ptr,35), group_P_fitness(ptr,group_ptr,35));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",36, num_X_in_group(group_ptr, ptr, 36), num_M_in_group(group_ptr, ptr, 36), num_P_in_group(group_ptr, ptr, 36), num_in_group(group_ptr, ptr, 36),  num_infected_in_group(group_ptr, ptr, 36), group_X_fitness(ptr,group_ptr,36), group_M_fitness(ptr,group_ptr,36), group_P_fitness(ptr,group_ptr,36));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",37, num_X_in_group(group_ptr, ptr, 37), num_M_in_group(group_ptr, ptr, 37), num_P_in_group(group_ptr, ptr, 37), num_in_group(group_ptr, ptr, 37),  num_infected_in_group(group_ptr, ptr, 37), group_X_fitness(ptr,group_ptr,37), group_M_fitness(ptr,group_ptr,37), group_P_fitness(ptr,group_ptr,37));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",38, num_X_in_group(group_ptr, ptr, 38), num_M_in_group(group_ptr, ptr, 38), num_P_in_group(group_ptr, ptr, 38), num_in_group(group_ptr, ptr, 38),  num_infected_in_group(group_ptr, ptr, 38), group_X_fitness(ptr,group_ptr,38), group_M_fitness(ptr,group_ptr,38), group_P_fitness(ptr,group_ptr,38));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",39, num_X_in_group(group_ptr, ptr, 39), num_M_in_group(group_ptr, ptr, 39), num_P_in_group(group_ptr, ptr, 39), num_in_group(group_ptr, ptr, 39),  num_infected_in_group(group_ptr, ptr, 39), group_X_fitness(ptr,group_ptr,39), group_M_fitness(ptr,group_ptr,39), group_P_fitness(ptr,group_ptr,39));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",40, num_X_in_group(group_ptr, ptr, 40), num_M_in_group(group_ptr, ptr, 40), num_P_in_group(group_ptr, ptr, 40), num_in_group(group_ptr, ptr, 40),  num_infected_in_group(group_ptr, ptr, 40), group_X_fitness(ptr,group_ptr,40), group_M_fitness(ptr,group_ptr,40), group_P_fitness(ptr,group_ptr,40));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",41, num_X_in_group(group_ptr, ptr, 41), num_M_in_group(group_ptr, ptr, 41), num_P_in_group(group_ptr, ptr, 41), num_in_group(group_ptr, ptr, 41),  num_infected_in_group(group_ptr, ptr, 41), group_X_fitness(ptr,group_ptr,41), group_M_fitness(ptr,group_ptr,41), group_P_fitness(ptr,group_ptr,41));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",42, num_X_in_group(group_ptr, ptr, 42), num_M_in_group(group_ptr, ptr, 42), num_P_in_group(group_ptr, ptr, 42), num_in_group(group_ptr, ptr, 42),  num_infected_in_group(group_ptr, ptr, 42), group_X_fitness(ptr,group_ptr,42), group_M_fitness(ptr,group_ptr,42), group_P_fitness(ptr,group_ptr,42));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",43, num_X_in_group(group_ptr, ptr, 43), num_M_in_group(group_ptr, ptr, 43), num_P_in_group(group_ptr, ptr, 43), num_in_group(group_ptr, ptr, 43),  num_infected_in_group(group_ptr, ptr, 43), group_X_fitness(ptr,group_ptr,43), group_M_fitness(ptr,group_ptr,43), group_P_fitness(ptr,group_ptr,43));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",44, num_X_in_group(group_ptr, ptr, 44), num_M_in_group(group_ptr, ptr, 44), num_P_in_group(group_ptr, ptr, 44), num_in_group(group_ptr, ptr, 44),  num_infected_in_group(group_ptr, ptr, 44), group_X_fitness(ptr,group_ptr,44), group_M_fitness(ptr,group_ptr,44), group_P_fitness(ptr,group_ptr,44));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",45, num_X_in_group(group_ptr, ptr, 45), num_M_in_group(group_ptr, ptr, 45), num_P_in_group(group_ptr, ptr, 45), num_in_group(group_ptr, ptr, 45),  num_infected_in_group(group_ptr, ptr, 45), group_X_fitness(ptr,group_ptr,45), group_M_fitness(ptr,group_ptr,45), group_P_fitness(ptr,group_ptr,45));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",46, num_X_in_group(group_ptr, ptr, 46), num_M_in_group(group_ptr, ptr, 46), num_P_in_group(group_ptr, ptr, 46), num_in_group(group_ptr, ptr, 46),  num_infected_in_group(group_ptr, ptr, 46), group_X_fitness(ptr,group_ptr,46), group_M_fitness(ptr,group_ptr,46), group_P_fitness(ptr,group_ptr,46));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",47, num_X_in_group(group_ptr, ptr, 47), num_M_in_group(group_ptr, ptr, 47), num_P_in_group(group_ptr, ptr, 47), num_in_group(group_ptr, ptr, 47),  num_infected_in_group(group_ptr, ptr, 47), group_X_fitness(ptr,group_ptr,47), group_M_fitness(ptr,group_ptr,47), group_P_fitness(ptr,group_ptr,47));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",48, num_X_in_group(group_ptr, ptr, 48), num_M_in_group(group_ptr, ptr, 48), num_P_in_group(group_ptr, ptr, 48), num_in_group(group_ptr, ptr, 48),  num_infected_in_group(group_ptr, ptr, 48), group_X_fitness(ptr,group_ptr,48), group_M_fitness(ptr,group_ptr,48), group_P_fitness(ptr,group_ptr,48));
	fprintf(f4,"%5d, %5d, %5d, %5d, %5d, %5d, %5.3f, %5.3f, %5.3f  \n",49, num_X_in_group(group_ptr, ptr, 49), num_M_in_group(group_ptr, ptr, 49), num_P_in_group(group_ptr, ptr, 49), num_in_group(group_ptr, ptr, 49),  num_infected_in_group(group_ptr, ptr, 49), group_X_fitness(ptr,group_ptr,49), group_M_fitness(ptr,group_ptr,49), group_P_fitness(ptr,group_ptr,49));

	percent_X_wins = percent_M_wins = percent_P_wins = 0;

	for (k = 0 ; k < initial_num_groups ; k ++)
	{
		if (num_X_in_group(group_ptr, ptr, k) > num_M_in_group(group_ptr, ptr, k) && num_X_in_group(group_ptr, ptr, k) > num_P_in_group(group_ptr, ptr, k))
			percent_X_wins ++ ;
		else if (num_M_in_group(group_ptr, ptr, k) > num_X_in_group(group_ptr, ptr, k) && num_M_in_group(group_ptr, ptr, k) > num_P_in_group(group_ptr, ptr, k) )
			percent_M_wins ++ ;
		else if (num_P_in_group(group_ptr, ptr, k) > num_X_in_group(group_ptr, ptr, k) && num_P_in_group(group_ptr, ptr, k) > num_M_in_group(group_ptr, ptr, k) )
			percent_P_wins ++ ;
	}

	fprintf(f4,"percent X wins at end = %f \n",(float)percent_X_wins/(percent_X_wins+percent_M_wins+percent_P_wins));
	fprintf(f4,"percent M wins at end = %f \n",(float)percent_M_wins/(percent_X_wins+percent_M_wins+percent_P_wins));
	fprintf(f4,"percent P wins at end = %f \n\n\n",(float)percent_P_wins/(percent_X_wins+percent_M_wins+percent_P_wins));

	fprintf(f5,"Simulation %d: \n",loop_count1+1);
	fprintf(f5," percent X wins at end = %f \n",(float)percent_X_wins/(percent_X_wins+percent_M_wins+percent_P_wins));
	fprintf(f5," percent M wins at end = %f \n",(float)percent_M_wins/(percent_X_wins+percent_M_wins+percent_P_wins));
	fprintf(f5," percent P wins at end = %f \n\n",(float)percent_P_wins/(percent_X_wins+percent_M_wins+percent_P_wins));

	num_infected = 0;
	num_individuals = 0;

	for (k = 0 ; k < N ; k ++)
	{
		if (ptr[k].active)
		{
			num_individuals++;
			if (ptr[k].status=='i' || ptr[k].status=='a')
				num_infected ++;
		}
	}
	if (num_individuals==0)
		num_individuals=1;

	fprintf(f6," percent infected=%f \n ",(float)num_infected/num_individuals);
	fprintf(f6," shrink_factor=%f \n", shrink_factor);
	fprintf(f6," numruns=%d \n",numruns);
	fprintf(f6," numsteps=%d \n",numsteps);
	fprintf(f6," inject_infection=%d \n",inject_infection);
	fprintf(f6," case_import_probability=%f \n",case_import_probability);
	fprintf(f6," transmission_probability=%f, \n",transmission_probability);
	fprintf(f6," recovery_probability=%f \n",recovery_probability);
	fprintf(f6," theta=%f \n",theta);
	fprintf(f6," disease_death_probability=%f \n",disease_death_probability);
	fprintf(f6," natural_death_probability=%f \n",natural_death_probability);
	fprintf(f6," mean_birth_probability=%f \n",mean_birth_probability);
	fprintf(f6," SD_birth_probability=%f \n",SD_birth_probability);
	fprintf(f6," breakup_probability=%f \n",breakup_probability);
	fprintf(f6," formation_probability=%f \n",formation_probability);
	fprintf(f6," error_term=%f \n",error_term);
	fprintf(f6," exogamy=%f \n",exogamy);
	fprintf(f6," mate_exponent=%f \n",mate_exponent);
	fprintf(f6," baseline_carrying_capacity=%d \n",baseline_carrying_capacity);
	fprintf(f6," strategy_adoption_parameter=%d \n",strategy_adoption_parameter);
	fprintf(f6," cost_paid=%f \n",cost_paid);
	fprintf(f6," cost_imposed=%f \n",cost_imposed);
	fprintf(f6," initial_pop_size=%d \n",initial_pop_size);
	fprintf(f6," initial_num_groups=%d \n",initial_num_groups);
	fprintf(f6," initial_M_strategists=%d \n",initial_M_strategists);
	fprintf(f6," initial_X_strategists=%d \n",initial_X_strategists);
	fprintf(f6," ----------------------------------------------------------------------------------- \n ");
	fprintf(f6," percent X wins = %f \n",(float)percent_X_wins/(percent_X_wins+percent_M_wins+percent_P_wins));
	fprintf(f6," percent M wins = %f \n",(float)percent_M_wins/(percent_X_wins+percent_M_wins+percent_P_wins));
	fprintf(f6," percent P wins = %f \n",(float)percent_P_wins/(percent_X_wins+percent_M_wins+percent_P_wins));
	fprintf(f6," *********************************************************************************** \n");
	fprintf(f6," *********************************************************************************** \n");
	fprintf(f6," *********************************************************************************** \n\n");

	printf("P_group_wins = %d, X_group_wins = %d \n",P_group_wins,X_group_wins);

	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
	fclose(f5);
	fclose(f6);
	fclose(fparam);
	fclose(ftemp);

	fclose(fg1);
	fclose(fg2);
	fclose(fg3);
	fclose(fg4);
	fclose(fg5);
	fclose(fg6);
	fclose(fg7);
	fclose(fg8);
	fclose(fg9);
	fclose(fg10);
	fclose(fg11);
	fclose(fg12);
	fclose(fg13);
	fclose(fg14);
	fclose(fg15);
	fclose(fg16);
	fclose(fg17);
	fclose(fg18);
	fclose(fg19);
	fclose(fg20);
	fclose(fg21);
	fclose(fg22);
	fclose(fg23);
	fclose(fg24);
	fclose(fg25);
	fclose(fg26);
	fclose(fg27);
	fclose(fg28);
	fclose(fg29);
	fclose(fg30);
	fclose(fg31);
	fclose(fg32);
	fclose(fg33);
	fclose(fg34);
	fclose(fg35);
	fclose(fg36);
	fclose(fg37);
	fclose(fg38);
	fclose(fg39);
	fclose(fg40);
	fclose(fg41);
	fclose(fg42);
	fclose(fg43);
	fclose(fg44);
	fclose(fg45);
	fclose(fg46);
	fclose(fg47);
	fclose(fg48);
	fclose(fg49);
	fclose(fg50);
}
