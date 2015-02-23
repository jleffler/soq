/* SO 28667734 */
//Knight's tour problem 

#include <stdio.h>
#include <stdlib.h>


int** init(int Height,int Width)
{
    int i = 0;

    int **Matrix = (int**)calloc(Height,sizeof(int*));
    for (i = 0; i < Width; i++)
        Matrix[i] = (int*)calloc(Width,sizeof(int));

    return Matrix;
}
void Clean_that_table(int** Matrix,int Height)// free Matrix
{
    int w = 0;
    for (w = 0; w < Height*Height; w++)
        free(Matrix[w]);
    free(Matrix);
}
void show(int** Matrix,int Height, int Width){ // show field
    int i = 0;

    for (i = 0; i < Height;i++)
    {
        int j = 0;
        for (j = 0; j < Width; j++)
        {
            printf("%d ",Matrix[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}
int check(int** Matrix,int x,int y,int Height,int Width) // check the position
{
    if ( x >= 0  && y >= 0 && x < Width && y < Height)
        return -1;
    else
        return 0;
}
int move(int** Matrix,int x,int y,int Height,int Width,int count)// recursive function 
{
    if ((count - 1)== Height*Width)
    {
        show(Matrix,Height,Width);
        Clean_that_table(Matrix,Height);
        printf("Uspeh\n");
        return -1;
    }
    if (-1 == check(Matrix,x+1,y-2,Height,Width) && Matrix[x+1][y-2] == 0)
    {
        Matrix[x+1][y-2] = count;
        move(Matrix,x+1,y-2,Height,Width,count+1);  
    }
    if (-1 == check(Matrix,x-1,y-2,Height,Width) && Matrix[x-1][y-2] == 0 )
    {
        Matrix[x-1][y-2] = count;
        move(Matrix,x-1,y-2,Height,Width,count+1);
    }
    if (-1 == check(Matrix,x+2,y-1,Height,Width) && Matrix[x+2][y-1] == 0)
    {
        Matrix[x+2][y-1] = count;
        move(Matrix,x+2,y-1,Height,Width,count+1);
    }
    if (-1 == check(Matrix,x+2,y+1,Height,Width) && Matrix[x+2][y+1] == 0)
    {
        Matrix[x+2][y+1] = count;
        move(Matrix,x+2,y+1,Height,Width,count+1);
    }
    if (-1 == check(Matrix,x+1,y+2,Height,Width) && Matrix[x+1][y+2] == 0)
    {
        Matrix[x+1][y+2] = count;
        move(Matrix,x+1,y+2,Height,Width,count+1);
    }
    if(-1 == check(Matrix,x-1,y+2,Height,Width) && Matrix[x-1][y+2] == 0)
    {
        Matrix[x-1][y+2] = count;
        move(Matrix,x-1,y+2,Height,Width,count+1);
    }
    if(-1 == check(Matrix,x-2,y+1,Height,Width) && Matrix[x-2][y+1] == 0)
    {
        Matrix[x-2][y+1] = count;
        move(Matrix,x-2,y+1,Height,Width,count+1);
    }
    if(-1 == check(Matrix,x-2,y-1,Height,Width) && Matrix[x-2][y-1] == 0)
    {
        Matrix[x-2][y-1] = count;
        move(Matrix,x-2,y-1,Height,Width,count+1);
    }
   if ((count - 1) == Height*Width)
   {
        show(Matrix,Height,Width);
        Clean_that_table(Matrix,Height);
        printf("Uspeh\n");
        return -1;
   }
   Matrix[x][y] = 0;
   return 0;
}
int main()
{
    int Height = 0;
    int Width = 0;
    int x = 0;
    int y = 0;
    int count = 2;
    int** Matrix = NULL;

    printf("Enter size of Matrix ");
    scanf("%d %d",&Height,&Width);

    Matrix = init(Height,Width);

    printf("Enter position(x,y) ");
    scanf("%d %d",&x,&y);

    if (x >= Height || y >= Width || y < 0 || x < 0)
    {
        printf("U kidding me?");
        return -1;
    }

    Matrix[x][y] = 1;
    move(Matrix,x,y,Height,Width,count);
    printf("1");
    /// return 0;
}
