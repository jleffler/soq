/* SO 4544-8840 Multithreaded C program - threads not terminating */
/* Original code as in the question */
/*
** This does ot compile under my standard options; indeed, GCC 7.1.0
** does not compile it warning free with no extra warning options
** activated.
*/
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

#define PERCENTAGE 0.25

pthread_mutex_t mutex; // protecting critical section
int scholarship = 4000,
                  total = 0;
void *A(void);
void *B(void);
void *C(void);
void totalCalc(void);

int main(void){

    pthread_t tid1,
              tid2,
              tid3;

    //pthread_setconcurrency(3);

    pthread_create(&tid1, NULL, (void *(*)(void *))A, NULL );
    pthread_create(&tid2, NULL, (void *(*)(void *))B, NULL );
    pthread_create(&tid3, NULL, (void *(*)(void *))C, NULL );
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);

    totalCalc();

    return 0;

}

void *A(void){
    float result;
    while(scholarship > 0){
        sleep(2);
        pthread_mutex_lock(&mutex);
        result = scholarship * PERCENTAGE;
        result = ceil(result);
        total = total + result;
        scholarship = scholarship - result;
        if( result >= 1){
            printf("A = ");
            printf("%.2f",result);
            printf("\n");
        }
        if( scholarship < 1){
            pthread_exit(0);
            printf("Thread A exited\n");
            return 0;
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

void *B(void){
    float result;
    while(scholarship > 0){
        sleep(1);
        pthread_mutex_lock(&mutex);
        result = scholarship * PERCENTAGE;
        result = ceil(result);
        total = total + result;
        scholarship = scholarship - result;
        if( result >= 1){
            printf("B = ");
            printf("%.2f",result);
            printf("\n");
        }
        if( scholarship < 1){
            pthread_exit(0);
            printf("Thread B exited\n");
            return 0;
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

void *C(void){
    float result;
    while(scholarship > 0){
        sleep(1);
        pthread_mutex_lock(&mutex);
        result = scholarship * PERCENTAGE;
        result = ceil(result);
        total = total + result;
        scholarship = scholarship - result;
        if( result >= 1){
            printf("C = ");
            printf("%.2f",result);
            printf("\n");
        }
        if( scholarship < 1){
            pthread_exit(0);
            printf("Thread C exited\n");
            return 0;
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

void totalCalc(void){
    printf("Total given out: ");
    printf("%d", total);
    printf("\n");
}
