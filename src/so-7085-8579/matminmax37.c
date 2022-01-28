/* SO 7085-8579 */
#include <assert.h>
#include <stdio.h>

static void print_matrix(const char *tag, size_t n, size_t m, const int matrix[n][m]);

/*
** When quadrant is 0, it corresponds to the N quadrant; when it is 1,
** to the W quadrant; 2, to the E quadrant; when it is 3, to the S
** quadrant.  Note that this condition assumes that the diagonal
** elements are not tested; the assertion ensures that. 
*/
static inline size_t quadrant(size_t r, size_t c, size_t N)
{
    assert(r != c && r + c != N - 1);
    return ((r < c) ? 0 : 1) + ((r + c < N - 1) ? 0 : 2);
}

static void matminmax(size_t n, const int matrix[n][n], int min[4], int max[4])
{
    min[0] = max[0] = matrix[0][1];
    min[1] = max[1] = matrix[1][0];
    min[2] = max[2] = matrix[1][n-1];
    min[3] = max[3] = matrix[n-1][1];
    for (size_t r = 0; r < n; r++)
    {
        for (size_t c = 0; c < n; c++)
        {
            if (r == c || r + c == n - 1)
                continue;
            size_t q = quadrant(r, c, n);
            if (matrix[r][c] > max[q])
                max[q] = matrix[r][c];
            if (matrix[r][c] < min[q])
                min[q] = matrix[r][c];
        }
    }
}

static void print_minmax(int min[4], int max[4])
{
    static const char quadname[] = "NWES";
    putchar('\n');
    for (size_t i = 0; i < 4; i++)
        printf("%c quadrant: min = %4d, max = %4d\n", quadname[i], min[i], max[i]);
    putchar('\n');
}

int main(void)
{
    /* Created by: gen_matrix -C -H 999 -L -999 -c 12 -r 12 -i -n mtx1 -w 4 */
    /* Random seed: 0xDB2DC719 */
    const int mtx1[12][12] =
    {
        {  688,  351, -309, -491, -200,  958, -699, -284, -638,  696, -427,   43, },
        { -621,  242,  913, -247, -293,  878,  538,  368, -861,  488, -568,  394, },
        { -646, -813, -943, -417, -697,  551,  325,   11, -234,   18,  348, -229, },
        {  436,  529, -994,  457, -270,  369,  318, -455, -918,  444, -821,  266, },
        {  544,   24,  398, -589, -779,   -2,  932,  810, -915, -591,  877,  865, },
        {   19,  879, -528, -483,  961,  478, -426,  528,  522, -403, -859,  -63, },
        {  830,  103, -662, -894,  -29,  875, -610,  244,  592,  -28, -206,  538, },
        {  231, -707, -303, -462,  683,  200,   -3, -707,  480,   -2, -920, -743, },
        {  981, -427, -793, -577, -296,  127,  823,  937,  -98, -405,  871, -221, },
        { -139,  841,  299, -415, -773,  403,   92, -474, -384, -219, -636,  -12, },
        {  -89,  -13, -679, -998, -567, -826,  705, -530,  658,  134,  871,  875, },
        { -475, -148, -275,  754,  399, -946,  -78, -469,  655,  -45,   81,  921, },
    };
    enum { MTX1_SIZE = sizeof(mtx1) / sizeof(mtx1[0]) };

    int min[4];
    int max[4];

    matminmax(MTX1_SIZE, mtx1, min, max);
    print_matrix("Matrix 1", MTX1_SIZE, MTX1_SIZE, mtx1);
    print_minmax(min, max);

    /* Created by: gen_matrix -C -H 999 -L -999 -c 13 -r 13 -i -n mtx2 -w 4 */
    /* Random seed: 0xD2A82AC2 */
    const int mtx2[13][13] =
    {
        {  208, -676,  374,  587,  -89, -485, -754,  286, -295, -826, -511, -797,  858, },
        {  991,  423,  404,  477, -449,  442, -860,  629,  437, -606,  974,  522,  885, },
        {  -54, -815, -124,   27,   68, -224,  -95,  430, -244, -941,  857, -843, -306, },
        {   92,  941, -613,  435,  222, -966,   -1,  292, -577,  597,  238,  527, -984, },
        {  978,  661,  315, -347, -747,  242,  711,   15, -922, -623, -533,  794,   65, },
        {  459, -195,  928, -325, -270, -703,   64,  -18, -219,   92,  831, -657,  945, },
        {  250, -102, -861,  -30, -603, -921, -229,  914,  164,  273, -133,  915,  565, },
        {  855, -607,  800, -137,  635, -216, -990, -432, -986, -650,  850,  456,  671, },
        { -393, -159, -685,  537,  598, -680,  241, -799, -821, -750, -559, -164,  103, },
        {  318,  679,  499,  980,  186,  841, -139,  878, -187,  818, -430,  904,  797, },
        { -496,   31, -606,   25, -244,   26, -558, -307, -656,  885,  327, -961, -742, },
        {  558,  592, -562,  148, -543, -995,  534, -519,  257,  784,  982,  508,  470, },
        {  -37,  289,  -94, -513, -115,  -51,  638,  633,   64, -701, -955, -575,  987, },
    };
    enum { MTX2_SIZE = sizeof(mtx2) / sizeof(mtx2[0]) };

    matminmax(MTX2_SIZE, mtx2, min, max);
    print_matrix("Matrix 2", MTX2_SIZE, MTX2_SIZE, mtx2);
    print_minmax(min, max);

    /* Created by: gen_matrix -C -H 999 -L -999 -c 3 -r 3 -i -n mtx3 -w 4 */
    /* Random seed: 0x238E2E67 */
    const int mtx3[3][3] =
    {
        { -703,  420,  896, },
        {  697, -581,  -38, },
        {  829,  878,  722, },
    };
    enum { MTX3_SIZE = sizeof(mtx3) / sizeof(mtx3[0]) };

    matminmax(MTX3_SIZE, mtx3, min, max);
    print_matrix("Matrix 3", MTX3_SIZE, MTX3_SIZE, mtx3);
    print_minmax(min, max);

    /* Created by: gen_matrix -C -H 999 -L -999 -c 4 -r 4 -i -n mtx4 -w 4 */
    /* Random seed: 0x9F26F797 */
    const int mtx4[4][4] =
    {
        { -726,  135,  216,  291, },
        { -628, -901, -594,  313, },
        { -315, -696,  274,  337, },
        {  499,  585, -148, -390, },
    };
    enum { MTX4_SIZE = sizeof(mtx4) / sizeof(mtx4[0]) };

    matminmax(MTX4_SIZE, mtx4, min, max);
    print_matrix("Matrix 4", MTX4_SIZE, MTX4_SIZE, mtx4);
    print_minmax(min, max);

    /* Created by: gen_matrix -C -H 999 -L -999 -c 5 -r 5 -i -n mtx5 -w 4 */
    /* Random seed: 0x10185C02 */
    const int mtx5[5][5] =
    {
        {  -73, -575, -606,  445, -714, },
        {  995, -839, -773,  240,  819, },
        {  132,  581,  956, -495, -914, },
        {  -10, -748,  328, -611, -475, },
        {  249,  249, -839,  152, -408, },
    };
    enum { MTX5_SIZE = sizeof(mtx5) / sizeof(mtx5[0]) };

    matminmax(MTX5_SIZE, mtx5, min, max);
    print_matrix("Matrix 5", MTX5_SIZE, MTX5_SIZE, mtx5);
    print_minmax(min, max);

    /* Created by: gen_matrix -C -H 999 -L -999 -c 6 -r 6 -i -n mtx6 -w 4 */
    /* Random seed: 0x875034FD */
    const int mtx6[6][6] =
    {
        { -814, -712, -938, -333,  123, -626, },
        {  621, -154,  835,  640,  575, -287, },
        { -720, -288, -563,  291,  182, -542, },
        {  132, -954, -404, -859, -796,  212, },
        { -506,  237, -828,  -37,  431,  399, },
        { -943,  151,  567, -414, -902,  959, },
    };
    enum { MTX6_SIZE = sizeof(mtx6) / sizeof(mtx6[0]) };

    matminmax(MTX6_SIZE, mtx6, min, max);
    print_matrix("Matrix 6", MTX6_SIZE, MTX6_SIZE, mtx6);
    print_minmax(min, max);

    /* Created by: gen_matrix -C -H 999 -L -999 -c 7 -r 7 -i -n mtx7 -w 4 */
    /* Random seed: 0x2574C5FF */
    const int mtx7[7][7] =
    {
        {  386, -560,  959, -485,  360,  278, -474, },
        {  440, -360,  617,  214,  -11,  300,  590, },
        { -285,   83, -568,  989, -117, -766,  411, },
        {  944,  598, -568,  414, -596, -882,  640, },
        { -544, -849,  167,  890,  474, -361,   52, },
        {  531,  544, -488,  569,  585, -816,  486, },
        { -542, -965, -758,  590, -314,  401,  964, },
    };
    enum { MTX7_SIZE = sizeof(mtx7) / sizeof(mtx7[0]) };

    matminmax(MTX7_SIZE, mtx7, min, max);
    print_matrix("Matrix 7", MTX7_SIZE, MTX7_SIZE, mtx7);
    print_minmax(min, max);


    return 0;
}

static int max_field_width(size_t n, const int matrix[n][n])
{
    int min_val = matrix[0][0];
    int max_val = matrix[0][0];
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (matrix[i][j] < min_val)
                min_val = matrix[i][j];
            if (matrix[i][j] > max_val)
                max_val = matrix[i][j];
        }
    }
    int fld_width = snprintf(0, 0, "%d", max_val);
    if (min_val < 0)
    {
        int min_width = snprintf(0, 0, "%d", min_val);
        if (min_width > fld_width)
            fld_width = min_width;
    }
    return fld_width;
}

static void print_matrix(const char *tag, size_t n, size_t m, const int matrix[n][m])
{
    printf("%s (%zux%zu):\n", tag, n, m);
    int w = max_field_width(n, matrix) + 1;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            printf("%*d", w, matrix[i][j]);
        }
        putchar('\n');
    }
}
