/*
 *  polygyny14.h
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUMPARTNERS 8

#define N 15000

#define MAXNUMGROUPS 60

#define MAXGROUPSIZE 305

long int idummy;

typedef struct node_data
{
    int active;                             /* N is a max population size, so a node is active only if active=1 (otherwise, active=0 means node is not alive and active) */

    char status;                            /* infection status: 's' = susceptible, 'i'=detected infection, 'a'=undetected infection */
    char gender;                            /* 'm' or 'f' */
    int group;                              /* group number of which individual is a member */
    char strategy;                          /* M, P or X (or F if they are female) */
    float birth_probability;                /* birth_probability (wealth), for males */

    int partner[MAXNUMPARTNERS];            /* node index of the i'th (casual) partner of the node, equals -1 if no casual partner */
    int num_partners;                       /* number of casual partners of the node (counter for casual_partner array is always one less since it starts from 0) */

    int fitness;                            /* lifetime number of offspring */

    int fertile;

    int virgin;

    /* not in use: */

    int steady_partner;                    /* node index of the node's steady partner (-1 if node has no steady partner) */
    int pairS01;                           /* S01 pair index of the S01 pair of which the node is a member (-1 if no steady, or if not S01) */
    int pairS;                             /* S pair index of the S pair of which the node is a member (-1 if no steady) */
    int pairC[MAXNUMPARTNERS];              /* C pair index of the C pair formed between the node and the node's i'th partner (equals -1 if no partner) */
    int pairC01[MAXNUMPARTNERS];            /* C01 pair index of the C01 pair formed by the node and the node's i'th partner (equals -1 if no partner or if not C01) */
    double timeinf;                           /* time at which infection occurred, in years (equals -1 if currently susceptible) */
    double duration1;                         /* duration of infectiousness of stage 1, in years, drawn from erlang distribution */
} node;

typedef struct group_data
{
    int carrying_capacity;
    int member[MAXGROUPSIZE];
    int size;
    int active;
} group;

/* Declarations before use */
static int room_in_group(struct group_data *group_ptr, int groupID);

#define IA 16807
#define IM 2147483647
#define AM (1.0 / IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1 + (IM - 1) / NTAB)
#define EPS 1.2e-7
#define RNMX (1.0 - EPS)

static float ran1(long *idum)
{
    int j;
    long k;
    static long iy = 0;
    static long iv[NTAB];
    float Temp;

    if (*idum <= 0 || !iy)
    {
        if (-(*idum) < 1)
            *idum = 1;
        else
            *idum = -(*idum);
        for (j = NTAB + 7; j >= 0; j--)
        {
            k = (*idum) / IQ;
            *idum = IA * (*idum - k * IQ) - IR * k;
            if (*idum < 0)
                *idum += IM;
            if (j < NTAB)
                iv[j] = *idum;
        }
        iy = iv[0];
    }
    k = (*idum) / IQ;
    *idum = IA * (*idum - k * IQ) - IR * k;
    if (*idum < 0)
        *idum += IM;
    j = iy / NDIV;
    iy = iv[j];
    iv[j] = *idum;
    if ((Temp = AM * iy) > RNMX)
        return RNMX;
    else
        return Temp;
}

#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

static float gasdev(long *idum)
{
    static int iset = 0;
    static float gset;
    float fac, rsq, v1, v2;

    if  (iset == 0)
    {
        do
        {
            v1 = 2.0 * ran1(idum) - 1.0;
            v2 = 2.0 * ran1(idum) - 1.0;
            rsq = v1 * v1 + v2 * v2;
        } while (rsq >= 1.0 || rsq == 0.0);
        fac = sqrt(-2.0 * log(rsq) / rsq);
        gset = v1 * fac;
        iset = 1;
        return v2 * fac;
    }
    else
    {
        iset = 0;
        return gset;
    }
}

static double kyrand(void)   /* returns random number between 0 and 1 */
{
    /* int maxnumber = 2147483647l; */ /* 2^31 - 1 */
    double answer;
    answer = (double)rand() / RAND_MAX;
    return(answer);
}

#ifdef DEFINE_UNUSED_FUNCTIONS
static float fac(int k)    /* factorial function */
{
    int i;
    float answer = 1;
    if (k == 0)
        answer = 1;
    else
    {
        for (i = 1; i <= k; i++)
        {
            answer = i * answer;
        }
    }
    return answer;
}
#endif /* DEFINE_UNUSED_FUNCTIONS */

static int not_yet_partners(struct node_data *ptr, int a, int b)
{
    int c;
    int answer = 1;

    for (c = 0; c < MAXNUMPARTNERS; c++)
    {
        if (ptr[a].partner[c] == b)
            answer = 0;
    }
    return answer;
}

static int same_gender(struct node_data *ptr, int a, int b)
{
    if (ptr[a].gender == 'm' && ptr[b].gender == 'm')
        return 1;
    else if (ptr[a].gender == 'f' && ptr[b].gender == 'f')
        return 1;
    else
        return 0;
}

static void
make_partners(struct node_data *ptr, int a, int b)
{
    int i;

    for (i = 0; i < MAXNUMPARTNERS; i++)
    {
        if (ptr[a].partner[i] == -1)
        {
            ptr[a].partner[i] = b;
            break;
        }
    }

    for (i = 0; i < MAXNUMPARTNERS; i++)
    {
        if (ptr[b].partner[i] == -1)
        {
            ptr[b].partner[i] = a;
            break;
        }
    }

    ptr[a].num_partners++;
    ptr[b].num_partners++;

    if (ptr[a].virgin == 1)
        ptr[a].virgin = 0;
    if (ptr[b].virgin == 1)
        ptr[b].virgin = 0;
}

static int num_P_in_group(struct group_data *group_ptr, struct node_data *ptr, int current_group)
{
    int j, k;
    int number_of_P = 0;

    for (j = 0; j < MAXGROUPSIZE; j++)
    {
        if (group_ptr[current_group].member[j] != -1)
        {
            k = group_ptr[current_group].member[j];
            if (ptr[k].active && ptr[k].strategy == 'P')
            {
                number_of_P++;
            }
        }
    }

    return number_of_P;
}

static int num_M_in_group(struct group_data *group_ptr, struct node_data *ptr, int current_group)
{
    int j, k;
    int number_of_M = 0;

    for (j = 0; j < MAXGROUPSIZE; j++)
    {
        if (group_ptr[current_group].member[j] != -1)
        {
            k = group_ptr[current_group].member[j];
            if (ptr[k].active && ptr[k].strategy == 'M')
            {
                number_of_M++;
            }
        }
    }

    return number_of_M;
}

static int num_in_group(struct group_data *group_ptr, struct node_data *ptr, int current_group)
{
    int j, k;
    int number_in_group = 0;

    for (j = 0; j < MAXGROUPSIZE; j++)
    {
        if (group_ptr[current_group].member[j] != -1)
        {
            k = group_ptr[current_group].member[j];
            if (ptr[k].active)
            {
                number_in_group++;
            }
        }
    }

    return number_in_group;
}

#ifdef DEFINE_UNUSED_FUNCTIONS
static int num_groups(struct group_data *group_ptr, struct node_data *ptr)
{
    int k, number_of_groups = 0;

    for (k = 0; k < MAXNUMGROUPS; k++)
    {
        if (num_in_group(group_ptr, ptr, k) > 0)
            number_of_groups++;
    }

    return number_of_groups;
}
#endif /* DEFINE_UNUSED_FUNCTIONS */

static int num_infected_in_group(struct group_data *group_ptr, struct node_data *ptr, int current_group)
{
    int j, k;
    int number_of_infected = 0;

    for (j = 0; j < MAXGROUPSIZE; j++)
    {
        if (group_ptr[current_group].member[j] != -1)
        {
            k = group_ptr[current_group].member[j];
            if (ptr[k].active && (ptr[k].status == 'i' || ptr[k].status == 'a'))
            {
                number_of_infected++;
            }
        }
    }

    return number_of_infected;
}

static int num_X_in_group(struct group_data *group_ptr, struct node_data *ptr, int current_group)
{
    int j, k;
    int number_of_X = 0;

    for (j = 0; j < MAXGROUPSIZE; j++)
    {
        if (group_ptr[current_group].member[j] != -1)
        {
            k = group_ptr[current_group].member[j];
            if (ptr[k].active && ptr[k].strategy == 'X')
            {
                number_of_X++;
            }
        }
    }

    return number_of_X;
}

#ifdef DEFINE_UNUSED_FUNCTIONS
static float
his_penalty(struct group_data *group_ptr, struct node_data *ptr, int male,
            float cost_paid, float cost_imposed, float punishing_threshold)
{
    int current_group;
    float penalty;
    int threshold_exceeded;

    current_group = ptr[male].group;

    if ((float)num_X_in_group(group_ptr, ptr, current_group) / (num_X_in_group(group_ptr, ptr, current_group) + num_M_in_group(group_ptr, ptr, current_group) + num_P_in_group(group_ptr, ptr, current_group)) > punishing_threshold)
        threshold_exceeded = 1;
    else
        threshold_exceeded = 0;

    if (ptr[male].strategy == 'X')
    {
        if (cost_imposed * num_X_in_group(group_ptr, ptr, current_group) > 1)
        {
            if (threshold_exceeded)
                penalty = (1.0 / num_X_in_group(group_ptr, ptr, current_group)) * num_P_in_group(group_ptr, ptr, current_group);
            else
                penalty = 0;
        }
        else
        {
            if (threshold_exceeded)
                penalty = cost_paid * num_P_in_group(group_ptr, ptr, current_group);
            else
                penalty = 0;
        }

        if (penalty > 1)
            penalty = 1;
        else if (penalty < 0)
            penalty = 0;

        return 1 - penalty;
    }
    else if (ptr[male].strategy == 'P')
    {
        if (threshold_exceeded)
            penalty = cost_imposed * num_X_in_group(group_ptr, ptr, current_group);
        else
            penalty = 0;

        if (penalty > 1)
            penalty = 1;
        else if (penalty < 0)
            penalty = 0;

        return 1 - penalty;
    }
    else if (ptr[male].strategy == 'M')
    {
        return 1;
    }
    assert(0);
    exit(1);
}
#endif /* DEFINE_UNUSED_FUNCTIONS */

static float
her_partners_penalty(struct group_data *group_ptr, struct node_data *ptr,
                     int female, float cost_paid, float cost_imposed,
                     float punishing_threshold)
{
    int j, current_partner, current_group;
    int partner_flag = 0;
    float penalty;
    int threshold_exceeded;

    for (j = 0; j < MAXNUMPARTNERS; j++)
    {
        if (ptr[female].partner[j] != -1)
        {
            current_partner = ptr[female].partner[j];
            if (ptr[current_partner].active)
            {
                partner_flag = 1;
                break;
            }
        }
    }

    if (partner_flag == 1)
    {
        current_group = ptr[female].group;

        if ((float)num_X_in_group(group_ptr, ptr, current_group) / (num_X_in_group(group_ptr, ptr, current_group) + num_M_in_group(group_ptr, ptr, current_group) + num_P_in_group(group_ptr, ptr, current_group)) > punishing_threshold)
            threshold_exceeded = 1;
        else
            threshold_exceeded = 0;

        if (ptr[current_partner].strategy == 'X')
        {
            if (cost_imposed * num_X_in_group(group_ptr, ptr, current_group) > 1)
            {
                if (threshold_exceeded)
                    penalty = (1.0 / num_X_in_group(group_ptr, ptr, current_group)) * num_P_in_group(group_ptr, ptr, current_group);
                else
                    penalty = 0;
            }
            else
            {
                if (threshold_exceeded)
                    penalty = cost_paid * num_P_in_group(group_ptr, ptr, current_group);
                else
                    penalty = 0;
            }

            if (penalty > 1)
                penalty = 1;
            else if (penalty < 0)
                penalty = 0;

            return 1 - penalty;
        }
        else if (ptr[current_partner].strategy == 'P')
        {
            if (threshold_exceeded)
                penalty = cost_imposed * num_X_in_group(group_ptr, ptr, current_group);
            else
                penalty = 0;

            if (penalty > 1)
                penalty = 1;
            else if (penalty < 0)
                penalty = 0;

            return 1 - penalty;
        }
        else if (ptr[current_partner].strategy == 'M')
        {
            return 1;
        }
        assert(0);
        exit(1);
    }
    else
    {
        return 1;
    }
}

static int her_current_partner(struct node_data *ptr, int female)
{
    int j, current_partner;
    int partner_flag = 0;

    for (j = 0; j < MAXNUMPARTNERS; j++)
    {
        if (ptr[female].partner[j] != -1)
        {
            current_partner = ptr[female].partner[j];
            if (ptr[current_partner].active)
            {
                partner_flag = 1;
                break;
            }
        }
    }

    if (partner_flag == 1)
        return current_partner;
    else
    {
        printf("serious error in her_current_partner function... partner count suggests she has a partner, but function could not find him. Exiting.\n");
        exit(0);
    }
}

static void
kill_group(struct group_data *group_ptr, struct node_data *ptr, int winning_group, int vanquished_group)
{
    int j, k, q, h;
    int group_count = 0;
    int current_partner;

    /* first, kill vanquished group */

    for (j = 0; j < MAXGROUPSIZE; j++)
    {
        if (group_ptr[vanquished_group].member[j] != -1)
        {
            k = group_ptr[vanquished_group].member[j];

            ptr[k].active = 0;
            ptr[k].fitness = 0;
            ptr[k].num_partners = 0;
            ptr[k].group = -1;
            ptr[k].fertile = 1;
            ptr[k].virgin = 1;

            for (q = 0; q < MAXNUMPARTNERS; q++)
            {
                ptr[k].partner[q] = -1;
            }
        }
        group_ptr[vanquished_group].member[j] = -1;
    }
    group_ptr[vanquished_group].size = 0;

    /* then, put half of victorious group into vanquished group */

    for (j = 0; j < MAXGROUPSIZE; j++)
    {
        if (group_ptr[winning_group].member[j] != -1)
        {
            k = group_ptr[winning_group].member[j];
            if (ptr[k].active)
            {
                if (ptr[k].gender == 'm')
                {
                    if (kyrand() < 0.5) /* moves male to new group with 50% chance, along with his partners */
                    {
                        ptr[k].group = vanquished_group;
                        group_ptr[winning_group].member[j] = -1;
                        group_ptr[vanquished_group].member[group_count] = k;
                        group_ptr[winning_group].size--;
                        group_ptr[vanquished_group].size++;
                        group_count++;

                        for (q = 0; q < MAXNUMPARTNERS; q++)
                        {
                            if (ptr[k].partner[q] != -1)
                            {
                                current_partner = ptr[k].partner[q];

                                if (ptr[current_partner].active)
                                {
                                    ptr[current_partner].group = vanquished_group;

                                    for (h = 0; h < MAXGROUPSIZE; h++)
                                    {
                                        if (group_ptr[winning_group].member[h] == current_partner)
                                        {
                                            group_ptr[winning_group].member[h] = -1;
                                            break;
                                        }
                                    }
                                    group_ptr[vanquished_group].member[group_count] = current_partner;
                                    group_ptr[winning_group].size--;
                                    group_ptr[vanquished_group].size++;
                                    group_count++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

static void
split_group(struct group_data *group_ptr, struct node_data *ptr, int mother_group, int initial_num_groups)
{
    int j, k, q, h;
    int daughter_group;
    int group_count = 0;
    int current_partner;
    int num_of_searches = 0;

    /* find a new daughter group to move to */

    do
    {
        daughter_group = (int)(kyrand() * initial_num_groups);
        num_of_searches++;
    } while (num_in_group(group_ptr, ptr, daughter_group) != 0 && num_of_searches < 100);

    if (num_of_searches < 100)
    {
        //printf("group %d (size %d) is splitting and taking over spot of group %d. ",mother_group,num_in_group(group_ptr, ptr, mother_group),daughter_group);

        /* make sure daughter group is initialized */

        for (j = 0; j < MAXGROUPSIZE; j++)
        {
            group_ptr[daughter_group].member[j] = -1;
        }
        group_ptr[daughter_group].size = 0;

        /* move members over to daughter group */

        for (j = 0; j < MAXGROUPSIZE; j++)
        {
            if (group_ptr[mother_group].member[j] != -1)
            {
                k = group_ptr[mother_group].member[j];
                if (ptr[k].active)
                {
                    if (ptr[k].gender == 'm')
                    {
                        if (kyrand() < 0.5) /* moves male to new group with 50% chance, along with his partners */
                        {
                            ptr[k].group = daughter_group;
                            group_ptr[mother_group].member[j] = -1;
                            group_ptr[daughter_group].member[group_count] = k;
                            group_ptr[mother_group].size--;
                            group_ptr[daughter_group].size++;
                            group_count++;

                            for (q = 0; q < MAXNUMPARTNERS; q++)
                            {
                                if (ptr[k].partner[q] != -1)
                                {
                                    current_partner = ptr[k].partner[q];

                                    if (ptr[current_partner].active)
                                    {
                                        ptr[current_partner].group = daughter_group;

                                        for (h = 0; h < MAXGROUPSIZE; h++)
                                        {
                                            if (group_ptr[mother_group].member[h] == current_partner)
                                            {
                                                group_ptr[mother_group].member[h] = -1;
                                                break;
                                            }
                                        }
                                        group_ptr[daughter_group].member[group_count] = current_partner;
                                        group_ptr[mother_group].size--;
                                        group_ptr[daughter_group].size++;
                                        group_count++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //printf("mother group is now size %d and daughter group is now size %d.\n",num_in_group(group_ptr, ptr, mother_group),num_in_group(group_ptr, ptr, daughter_group));
    }
}

#ifdef DEFINE_UNUSED_FUNCTIONS
static void
seek_partnership_inside(struct node_data *ptr, struct group_data *group_ptr, int b, int n)
{
    int a, ID, partner_flag = 0;
    int members_checked[MAXGROUPSIZE];
    int number_checked = 0;
    int k;
    int suitable;

    for (k = 0; k < MAXGROUPSIZE; k++)
        members_checked[k] = 0;

    suitable = 0;
    do
    {
        ID = (int)(kyrand() * MAXGROUPSIZE);
        if (members_checked[ID] == 0)
        {
            members_checked[ID] = 1;
            number_checked++;

            a = group_ptr[n].member[ID];

            if (a != -1)
            {
                if (ptr[a].active)
                {
                    if (same_gender(ptr, a, b) || ptr[a].num_partners == MAXNUMPARTNERS)
                    {
                        suitable = 0;
                    }
                    else
                    {
                        if (ptr[a].strategy == 'P')
                        {
                            suitable = 1;
                        }
                        else if ((ptr[a].strategy == 'M' || ptr[a].strategy == 'X') && ptr[a].num_partners == 0)
                        {
                            suitable = 1;
                        }
                        else
                        {
                            suitable = 0;
                        }
                    }
                }
                else
                {
                    suitable = 0;
                }
            }
            else
            {
                suitable = 0;
            }
        }
    } while (number_checked < MAXGROUPSIZE && suitable == 0);

    if (suitable && not_yet_partners(ptr, a, b))
    {
        make_partners(ptr, a, b);
        partner_flag = 1;
    }
}
#endif /* DEFINE_UNUSED_FUNCTIONS */

/* in this version of ths function, the female ranks males and simply picks the male in the group with the highest ratio of wealth/(wives+1) */
static void
seek_partnership_inside_ranked(struct node_data *ptr, struct group_data *group_ptr,
                               int b, int n, double mate_exponent,
                               double fertility_penalty, double cost_paid,
                               double cost_imposed, double punishing_threshold)
{
    int a, ID, partner_flag = 0;
    int suitable;
    int most_desirable = -1;
    float highest_desirability = -1;
    float desirability;
    float polygyny_penalty;

    suitable = 0;

    for (ID = 0; ID < MAXGROUPSIZE; ID++)
    {
        a = group_ptr[n].member[ID];

        if (a != -1)
        {
            if (ptr[a].active)
            {
                if (!(same_gender(ptr, a, b) || ptr[a].num_partners == MAXNUMPARTNERS))
                {
                    if (ptr[a].strategy == 'P')
                    {
                        suitable = 1;

                        polygyny_penalty = 1.0 / (fertility_penalty * (ptr[a].num_partners + 1) + (1 - fertility_penalty)); /* THX1138 */

                        desirability = pow(ptr[a].birth_probability, mate_exponent) * polygyny_penalty;
                        //desirability = pow(ptr[a].birth_probability,mate_exponent)*polygyny_penalty*his_penalty(group_ptr, ptr, a, cost_paid, cost_imposed, punishing_threshold);
                        //desirability = ptr[a].birth_probability*polygyny_penalty*his_penalty(group_ptr, ptr, a, cost_paid, cost_imposed, punishing_threshold);

                        if (desirability > highest_desirability)
                        {
                            most_desirable = a;
                            highest_desirability = desirability;
                        }
                        //printf("P: %14.13f %14.13f %d\n",desirability,highest_desirability,most_desirable);
                    }
                    else if ((ptr[a].strategy == 'M' || ptr[a].strategy == 'X') && ptr[a].num_partners == 0)
                    {
                        suitable = 1;

                        desirability = pow(ptr[a].birth_probability, mate_exponent);
                        //desirability = pow(ptr[a].birth_probability,mate_exponent)*his_penalty(group_ptr, ptr, a, cost_paid, cost_imposed, punishing_threshold);
                        //desirability = ptr[a].birth_probability*his_penalty(group_ptr, ptr, a, cost_paid, cost_imposed, punishing_threshold);

                        if (desirability > highest_desirability)
                        {
                            most_desirable = a;
                            highest_desirability = desirability;
                        }
                        //printf("MX: %14.13f %14.13f %d\n",desirability,highest_desirability,most_desirable);
                    }
                }
            }
        }
    }

    if (most_desirable != -1)
    {
        a = most_desirable;
        if (suitable && not_yet_partners(ptr, a, b))
        {
            make_partners(ptr, a, b);
            partner_flag = 1;
        }
    }
}

#ifdef DEFINE_UNUSED_FUNCTIONS
static int current_pop_size(struct node_data *ptr)
{
    int k, number = 0;

    for (k = 0; k < N; k++)
    {
        if (ptr[k].active)
            number++;
    }

    return number;
}
#endif /* DEFINE_UNUSED_FUNCTIONS */

static void
seek_partnership_outside(struct node_data *ptr, struct group_data *group_ptr,
                         int b, int n, double mate_exponent,
                         double fertility_penalty, double cost_paid,
                         double cost_imposed, double punishing_threshold)
{
    int a, ID, partner_flag = 0, group_flag;
    int k, j, l = 0;
    int chosen_group;
    int check_factor = 100;
    int suitable;
    int most_desirable = -1;
    float highest_desirability = -1;
    float desirability;
    float polygyny_penalty;

    /* look for another group to check for partners in */

    for (k = 0; k < MAXNUMGROUPS * check_factor; k++)
    {
        chosen_group = (int)(kyrand() * MAXNUMGROUPS);

        if (chosen_group != n && group_ptr[chosen_group].active)
            break;
    }

    /* if could not find a group, let user know.  otherwise, proceed to look for partner in that group */

    if (k == MAXNUMGROUPS * check_factor)
    {
        for (j = 0; j < MAXNUMGROUPS; j++)
        {
            if (group_ptr[j].active)
                l++;
        }
        if (l >= 2)
        {
            printf("checked %d times and could not find active group for exogamous female, even though there are %d groups left in the simulation!\n", MAXNUMGROUPS * check_factor, l);
        }
    }
    else
    {
        /* first check that group is not already at maximal size or at carrying capacity and that there is space for the female */

        group_flag = 0;
        for (j = 0; j < MAXGROUPSIZE; j++)
            if (group_ptr[chosen_group].member[j] == -1 && room_in_group(group_ptr, chosen_group))
            {
                group_flag = 1;
                break;
            }

        /* and if there is space, proceed with looking for a partner */

        if (group_flag == 1)
        {
            suitable = 0;

            for (ID = 0; ID < MAXGROUPSIZE; ID++)
            {
                a = group_ptr[chosen_group].member[ID];

                if (a != -1)
                {
                    if (ptr[a].active)
                    {
                        if (!(same_gender(ptr, a, b) || ptr[a].num_partners == MAXNUMPARTNERS))
                        {
                            if (ptr[a].strategy == 'P')
                            {
                                suitable = 1;

                                polygyny_penalty = 1.0 / (fertility_penalty * (ptr[a].num_partners + 1) + (1 - fertility_penalty)); /* THX1138 */

                                desirability = pow(ptr[a].birth_probability, mate_exponent) * polygyny_penalty;
                                //desirability = pow(ptr[a].birth_probability,mate_exponent)*polygyny_penalty*his_penalty(group_ptr, ptr, a, cost_paid, cost_imposed, punishing_threshold);
                                //desirability = ptr[a].birth_probability*polygyny_penalty*his_penalty(group_ptr, ptr, a, cost_paid, cost_imposed, punishing_threshold);

                                if (desirability > highest_desirability)
                                {
                                    most_desirable = a;
                                    highest_desirability = desirability;
                                }
                            }
                            else if ((ptr[a].strategy == 'M' || ptr[a].strategy == 'X') && ptr[a].num_partners == 0)
                            {
                                suitable = 1;

                                desirability = pow(ptr[a].birth_probability, mate_exponent);
                                //desirability = pow(ptr[a].birth_probability,mate_exponent)*his_penalty(group_ptr, ptr, a, cost_paid, cost_imposed, punishing_threshold);
                                //desirability = ptr[a].birth_probability*his_penalty(group_ptr, ptr, a, cost_paid, cost_imposed, punishing_threshold);

                                if (desirability > highest_desirability)
                                {
                                    most_desirable = a;
                                    highest_desirability = desirability;
                                }
                            }
                        }
                    }
                }
            }

            if (most_desirable != -1)
            {
                a = most_desirable;
                if (suitable && not_yet_partners(ptr, a, b))
                {
                    make_partners(ptr, a, b);
                    partner_flag = 1;
                }
            }

            /* then, move the female b to the other group, if a suitable partner was found */

            if (partner_flag == 1)
            {
                ptr[b].group = chosen_group;

                for (k = 0; k < MAXGROUPSIZE; k++)
                {
                    if (group_ptr[n].member[k] == b)
                    {
                        group_ptr[n].member[k] = -1;
                        group_ptr[n].size--;
                        break;
                    }
                }

                for (k = 0; k < MAXGROUPSIZE; k++)
                {
                    if (group_ptr[chosen_group].member[k] == -1)
                    {
                        group_ptr[chosen_group].member[k] = b;
                        group_ptr[chosen_group].size++;
                        break;
                    }
                }
            }
        }
    }
}

static void break_partnership(struct node_data *ptr, int a, int b)
{
    int i;

    for (i = 0; i < MAXNUMPARTNERS; i++)
    {
        if (ptr[a].partner[i] == b)
        {
            ptr[a].partner[i] = -1;
        }
    }

    for (i = 0; i < MAXNUMPARTNERS; i++)
    {
        if (ptr[b].partner[i] == a)
        {
            ptr[b].partner[i] = -1;
        }
    }

    ptr[a].num_partners--;
    ptr[b].num_partners--;
}

#ifdef DEFINE_UNUSED_FUNCTIONS
static int her_partner_not_with_detected_infection(struct node_data *ptr, int female)
{
    int j, current_partner;
    int partner_flag = 0;

    for (j = 0; j < MAXNUMPARTNERS; j++)
    {
        if (ptr[female].partner[j] != -1)
        {
            current_partner = ptr[female].partner[j];
            if (ptr[current_partner].active)
            {
                partner_flag = 1;
                break;
            }
        }
    }

    if (partner_flag == 1)
    {
        if (ptr[current_partner].status == 'i')
            return 0;
        else
            return 1;
    }
    else
    {
        printf("serious error in her_partner_not_with_detected_infection function... partner count suggests she has a partner, but function could not find him. Exiting.\n");
        exit(0);
    }
}
#endif /* DEFINE_UNUSED_FUNCTIONS */

static int her_partner_fertile(struct node_data *ptr, int female)
{
    int j, current_partner;
    int partner_flag = 0;

    for (j = 0; j < MAXNUMPARTNERS; j++)
    {
        if (ptr[female].partner[j] != -1)
        {
            current_partner = ptr[female].partner[j];
            if (ptr[current_partner].active)
            {
                partner_flag = 1;
                break;
            }
        }
    }

    if (partner_flag == 1)
    {
        if (ptr[current_partner].fertile == 0)
            return 0;
        else if (ptr[current_partner].fertile == 1)
            return 1;
        assert(0);
        exit(1);
    }
    else
    {
        printf("serious error in her_partner_not_with_detected_infection function... partner count suggests she has a partner, but function could not find him. Exiting.\n");
        exit(0);
    }
}

static void individual_dies(struct node_data *ptr, struct group_data *group_ptr, int n)
{
    int k, l, group, partner;

    /* make individual inactive */

    ptr[n].active = 0;

    /* adjust group characteristics */

    group = ptr[n].group;

    group_ptr[group].size--;
    for (k = 0; k < MAXGROUPSIZE; k++)
    {
        if (group_ptr[group].member[k] == n)
        {
            group_ptr[group].member[k] = -1;
            break;
        }
    }

    /* remove individual from other individuals' partner lists */

    for (k = 0; k < MAXNUMPARTNERS; k++)
    {
        partner = ptr[n].partner[k];
        if (partner != -1)
        {
            for (l = 0; l < MAXNUMPARTNERS; l++)
            {
                if (ptr[partner].partner[l] == n)
                {
                    ptr[partner].partner[l] = -1;
                    ptr[partner].num_partners--;
                }
            }
        }
    }

    for (k = 0; k < MAXNUMPARTNERS; k++)
    {
        ptr[n].partner[k] = -1;
    }

    ptr[n].num_partners = 0;
    ptr[n].virgin = 1;
    ptr[n].fertile = 1;
}

static float strategy_function(float parameter, float role_model_fitness, float average_male_fitness_in_group)
{
    float difference;

    difference = role_model_fitness - average_male_fitness_in_group;

    if (difference > 0)
        return (difference) / (parameter + difference);
    else
        return 0;
}

static float average_group_fitness(struct group_data *group_ptr, struct node_data *ptr, int groupID)
{
    int j, k;
    float avg_group_fitness = 0;
    int num_males = 0;

    for (j = 0; j < MAXGROUPSIZE; j++)
    {
        k = group_ptr[groupID].member[j];

        if (ptr[k].active)
        {
            if (ptr[k].gender == 'm')
            {
                avg_group_fitness += ptr[k].fitness;
                num_males++;
            }
        }
    }

    for (j = 0; j < MAXGROUPSIZE; j++)
    {
        k = group_ptr[groupID].member[j];
    }

    if (num_males > 0)
        return(avg_group_fitness / num_males);
    else
        return 0;
}

static void
individual_born(struct node_data *ptr, struct group_data *group_ptr,
                int mother, float error_term, float parameter,
                float mean_birth_probability, float SD_birth_probability)
{
    int k, n, a, j, mothers_group, group_flag, role_model, ID;
    int members_checked[MAXGROUPSIZE];
    int number_checked = 0;
    int suitable, mothers_partner;
    float random_number;
    int strategy_not_chosen = 1;
    int not_checked_error = 1;
    int check_count = 0;

    /* look for an empty space in population array */

    for (k = 0; k < N; k++)
    {
        if (ptr[k].active == 0)
            break;
    }

    if (k == N)
    {
        printf("Population size has hit the maximum allowable value N, so no more births are possible\n");
    }
    else
    {
        /* figure out identity of mother's group */

        mothers_group = ptr[mother].group;

        /* first check whether there is room in the mother's group for another birth (either due to array entry availability or group carrying capacity), and if so, add the new member... */

        group_flag = 0;
        for (j = 0; j < MAXGROUPSIZE; j++)
            if (group_ptr[mothers_group].member[j] == -1 && group_flag == 0 && room_in_group(group_ptr, mothers_group))
            {
                group_ptr[mothers_group].member[j] = k;
                group_ptr[mothers_group].size++;

                group_flag = 1;
            }

        /* ... and then proceed with updating the fitness scores of the parents... */

        if (group_flag == 1)
        {
            mothers_partner = her_current_partner(ptr, mother);

            ptr[mothers_partner].fitness++;
            ptr[mother].fitness++;
        }

        /* ... and defining state of the new individual */

        if (group_flag == 1)
        {
            ptr[k].group = mothers_group;
            ptr[k].active = 1;
            ptr[k].status = 's';
            ptr[k].num_partners = 0;
            ptr[k].fitness = 0;
            ptr[k].fertile = 1;
            ptr[k].virgin = 1;

            for (n = 0; n < MAXNUMPARTNERS; n++)
                ptr[k].partner[n] = -1;

            if (kyrand() < 0.5)
            {
                ptr[k].gender = 'm';
            }
            else
            {
                ptr[k].gender = 'f';
            }

            /* randomly sample a male in the group to look for a strategy to adopt, and keep looking until strategy has been adopted */

            if (ptr[k].gender == 'f')
            {
                ptr[k].strategy = '-';
                ptr[k].birth_probability = 0;
            }
            else
            {
                do
                {
                    for (j = 0; j < MAXGROUPSIZE; j++)
                        members_checked[j] = 0;
                    number_checked = 0;

                    suitable = 0;
                    do
                    {
                        ID = (int)(kyrand() * MAXGROUPSIZE);
                        if (members_checked[ID] == 0)
                        {
                            members_checked[ID] = 1;
                            number_checked++;

                            a = group_ptr[mothers_group].member[ID];

                            if (a != -1)
                            {
                                if (ptr[a].active && ptr[a].gender == 'm')
                                {
                                    suitable = 1;
                                    role_model = a;
                                }
                            }
                        }
                    } while (number_checked < MAXGROUPSIZE && suitable == 0);

                    check_count++;

                    if (kyrand() < error_term && not_checked_error)
                    {
                        random_number = kyrand();

                        if (random_number < 1.0 / 3)
                            ptr[k].strategy = 'X';
                        else if (random_number < 2.0 / 3)
                            ptr[k].strategy = 'M';
                        else
                            ptr[k].strategy = 'P';

                        strategy_not_chosen = 0;
                    }
                    else if (suitable)
                    {
                        if (ptr[role_model].fitness >= average_group_fitness(group_ptr, ptr, mothers_group))
                        {
                            if (kyrand() < strategy_function(parameter, ptr[role_model].fitness, average_group_fitness(group_ptr, ptr, mothers_group)))
                            {
                                ptr[k].strategy = ptr[role_model].strategy;
                                strategy_not_chosen = 0;
                            }
                        }
                    }
                    not_checked_error = 0;
                } while (strategy_not_chosen && check_count < MAXGROUPSIZE * 10);

                if (strategy_not_chosen)
                {
                    random_number = kyrand();

                    if (random_number < 1.0 / 3)
                        ptr[k].strategy = 'X';
                    else if (random_number < 2.0 / 3)
                        ptr[k].strategy = 'M';
                    else
                        ptr[k].strategy = 'P';
                }

                ptr[k].birth_probability = exp(mean_birth_probability + SD_birth_probability * gasdev(&idummy));
                //ptr[k].birth_probability = mean_birth_probability;
                //printf("born %f\n",ptr[k].birth_probability);
            }
        }
    }
}

static int room_in_group(struct group_data *group_ptr, int groupID)
{
    int k, group_size = 0;

    for (k = 0; k < MAXGROUPSIZE; k++)
    {
        if (group_ptr[groupID].member[k] != -1)
            group_size++;
    }

    if (group_size < group_ptr[groupID].carrying_capacity)
        return 1;
    else
        return 0;
}

static float population_X_fitness(struct node_data *ptr)
{
    int k;
    float average_X_fitness = 0;
    int num_X = 0;

    for (k = 0; k < N; k++)
    {
        if (ptr[k].active)
        {
            if (ptr[k].strategy == 'X')
            {
                average_X_fitness += ptr[k].fitness;
                num_X++;
            }
        }
    }
    if (num_X > 0)
    {
        return average_X_fitness / num_X;
    }
    else
    {
        return 0;
    }
}

static float population_M_fitness(struct node_data *ptr)
{
    int k;
    float average_M_fitness = 0;
    int num_M = 0;

    for (k = 0; k < N; k++)
    {
        if (ptr[k].active)
        {
            if (ptr[k].strategy == 'M')
            {
                average_M_fitness += ptr[k].fitness;
                num_M++;
            }
        }
    }
    if (num_M > 0)
    {
        return average_M_fitness / num_M;
    }
    else
    {
        return 0;
    }
}

static float population_P_fitness(struct node_data *ptr)
{
    int k;
    float average_P_fitness = 0;
    int num_P = 0;

    for (k = 0; k < N; k++)
    {
        if (ptr[k].active)
        {
            if (ptr[k].strategy == 'P')
            {
                average_P_fitness += ptr[k].fitness;
                num_P++;
            }
        }
    }
    if (num_P > 0)
    {
        return average_P_fitness / num_P;
    }
    else
    {
        return 0;
    }
}

static float group_X_fitness(struct node_data *ptr, struct group_data *group_ptr, int groupID)
{
    int k;
    float average_fitness = 0;
    int num = 0;
    int member;

    for (k = 0; k < MAXGROUPSIZE; k++)
    {
        if (group_ptr[groupID].member[k] != -1)
        {
            member = group_ptr[groupID].member[k];

            if (ptr[member].active && ptr[member].strategy == 'X')
            {
                average_fitness += ptr[member].fitness;
                num++;
            }
        }
    }

    if (num > 0)
    {
        return average_fitness / num;
    }
    else
    {
        return 0;
    }
}

static float group_M_fitness(struct node_data *ptr, struct group_data *group_ptr, int groupID)
{
    int k;
    float average_fitness = 0;
    int num = 0;
    int member;

    for (k = 0; k < MAXGROUPSIZE; k++)
    {
        if (group_ptr[groupID].member[k] != -1)
        {
            member = group_ptr[groupID].member[k];

            if (ptr[member].active && ptr[member].strategy == 'M')
            {
                average_fitness += ptr[member].fitness;
                num++;
            }
        }
    }

    if (num > 0)
    {
        return average_fitness / num;
    }
    else
    {
        return 0;
    }
}

static float group_P_fitness(struct node_data *ptr, struct group_data *group_ptr, int groupID)
{
    int k;
    float average_fitness = 0;
    int num = 0;
    int member;

    for (k = 0; k < MAXGROUPSIZE; k++)
    {
        if (group_ptr[groupID].member[k] != -1)
        {
            member = group_ptr[groupID].member[k];

            if (ptr[member].active && ptr[member].strategy == 'P')
            {
                average_fitness += ptr[member].fitness;
                num++;
            }
        }
    }

    if (num > 0)
    {
        return average_fitness / num;
    }
    else
    {
        return 0;
    }
}
