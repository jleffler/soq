### Stack Overflow Question 4511-1138

[SO 4511-1138](https://stackoverflow.com/q/45111138) &mdash;
How do I print cartesian plane with x and f(x) in C?

Now deleted - abandoned (10k only).

A moderately interesting looking graph.

[jschultz410](https://stackoverflow.com/users/4564515/jschultz410)
[noted](https://stackoverflow.com/questions/45111138/how-do-i-print-cartesian-plane-with-x-and-fx-in-c?noredirect=1#comment77196082_45111138)

> If you need to automatically scale the output to fit the min and max
> values and nicely space out the discrete points in between, then you
> likely need to run through the steps twice.
> The first time just to find the min and max points.
> The second time so you can print out the appropriately scaled output.
> Alternatively, you may be able to mathematically derive the min and
> max points based on the functions themselves -- maybe.

[David Bowling](https://stackoverflow.com/users/6879826/david-bowling)
[noted](https://stackoverflow.com/questions/45111138/how-do-i-print-cartesian-plane-with-x-and-fx-in-c?noredirect=1#comment77194766_45111138)

> Or perhaps, especially for cpu-intensive calculations, save the
> results (e.g., in an array), interpret and then display, doing
> calculations only once.

The `output.png` file is an image of the required output (the output
should not be a PNG file).

### Question text

And below the code I've written

int main() {

    int i,choice,a,b;
    double step = 0.0;
    float funcinc;
    while (choice != 0) {
        puts("Select a function to operate:\n");
        puts("  I. f(x) = x;");
        puts(" II. f(x) = -x;");
        puts("III. f(x) = x²;");
        puts(" IV. f(x) = - x³;");
        puts("  V. f(x) = (3*cos(x)-2*sin(4*x)-1)/2;\n");
        puts("0 to Exit the program");

        scanf("%d",&choice);

        printf("Selection: %d\n",choice);

        switch (choice) {
            case 1:
                funcinc = func1(step);
                printf("Function to print:f(x) = x\n");
                printf("From:");
                scanf("%d",&a);
                printf("To:");
                scanf("%d",&b);
                printf("Step:");
                scanf("%lf",&step);
                puts("    x           f(x)                ^-x");
                for (i=a; i<=b; i=i + step) {
                    printout(i,func1(i),step,a,b,funcinc);
                }
            case 2:
                funcinc = func2(step);
                printf("Function to print:f(x) = -x\n");
                printf("From:");
                scanf("%d",&a);
                printf("To:");
                scanf("%d",&b);
                printf("Step:");
                scanf("%lf",&step);
                puts("    x           f(x)                ^-x");
                for (i=a; i<=b; i=i + step) {
                    printout(i,func2(i),step,a,b,funcinc);
                }
            case 3:
                funcinc = func3(step);
                printf("Function to print:f(x) = x²\n");
                printf("From:");
                scanf("%d",&a);
                printf("To:");
                scanf("%d",&b);
                printf("Step:");
                scanf("%lf",&step);
                puts("    x           f(x)                ^-x");
                for (i=a; i<=b; i = i + step) {
                    printout(i,func3(i),step,a,b,funcinc);
                }
            case 4:
                funcinc = func4(step);
                printf("Function to print:f(x) = - x³\n");
                printf("From:");
                scanf("%d",&a);
                printf("To:");
                scanf("%d",&b);
                printf("Step:");
                scanf("%lf",&step);
                puts("    x           f(x)                ^-x");
                for (i=a; i<=b; i=i + step) {
                    printout(i,func1(i),step,a,b,funcinc);
                }
            case 5:
                funcinc = func5(step);
                printf("Function to print:f(x) = (3*cos(x)-2*sin(4*x)-1)/2\n");
                printf("From:");
                scanf("%d",&a);
                printf("To:");
                scanf("%d",&b);
                printf("Step:");
                scanf("%lf",&step);
                puts("    x           f(x)                ^-x");
                for (i=a; i<=b; i=i + step) {
                    printout(i,func5(i),step,a,b,funcinc);
                }
            case 0:
                puts("Terminated!\n");
                break;

            default:
                break;
        }
    }

    return 0;
} // end of main

double func1(double in){

    return in;
}
double func2(double in){

    return -1*in;
}
double func3(double in){

    return in*in;
}
double func4(double in){

    return (in*in)*(-1);
}
double func5(double in){

    return (3*cos(in)-2*sin(4*in)-1)/2;
}

I need to fix this function:

void printout(float x,float fx,float step, int strpt, int endpt, float inc){

    float absolute = fabsf(fx);

    printf("%10f  %10f",x,fx);

    while (x<0) {
        if (fx<0) {
            for (int i = strpt; i<absolute*strpt/30*(-1); i = i + inc) {
                printf(" ");
            }
            printf("*");
            for (int i = strpt; i<29-(absolute*strpt/30*(-1)); i = i + inc) {
                printf(" ");
            }
            printf("|");
            printf("\n");
        }
        if (fx>0) {
            for (int i = 0; i<30; i++) {
                printf(" ");
            }
            printf("|");
            for (int i = 0; i<absolute*endpt/30*(-1); i = i + inc) {
                printf(" ");
            }
            printf("*");
            printf("\n");
        }
    }
    if (x==0) {
        printf("------------------------------+--------------------------->");
    }
    while (x>0) {
        if (fx<0) {
            for (int i = strpt; i<absolute*strpt/30*(-1); i = i + inc) {
                printf(" ");
            }
            printf("*");
            for (int i = strpt; i<29-(absolute*strpt/30*(-1)); i = i + inc) {
                printf(" ");
            }
            printf("|");
            printf("\n");
        }
        if (fx>0) {
            for (int i = 0; i<30; i++) {
                printf(" ");
            }
            printf("|");
            for (int i = 0; i<absolute*endpt/30*(-1); i = i + inc) {
                printf(" ");
            }
            printf("*");
            printf("\n");
        }
    }
    }

