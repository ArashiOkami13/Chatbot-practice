#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_THREAD 7
#define NUM_CYCLE 8

void *quote(void *id)
{
    FILE *filePtr = fopen("Quote.txt", "a");
    if(pthread_self() % 2)
    {
        sleep(3);
        fprintf(filePtr, "\"Computer science is no more about computers than astronomy is about telescopes.\" --Edsger Dijkstra\r\n");
    }
    else
    {
        sleep(2);
        fprintf(filePtr, "\"Controlling complexity is the essence of computer programming.\" --Brian Kernigan\r\n");
    }
    printf("Thread %d is running\n", pthread_self());
    fclose(filePtr);
}
int main()
{
    pthread_t thread[NUM_THREAD];
    int rc;

    FILE *filePtr = fopen("Quote.txt", "w");
    fprintf(filePtr, "pid: %d\r\n", getpid());
    fclose(filePtr);

    for(int i = 0; i < NUM_THREAD; i++)
    {
        rc = pthread_create(&thread, NULL, quote, (void *) i);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        pthread_join(i, NULL);
    }
    printf("Sequence completed");
    return 0;
}
