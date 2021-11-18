#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define numOfThreads 5
#define iterations 5000
#define usingMutex 0
#define amplifyRaceConditionRisk 1
int balance = 0;
pthread_mutex_t lock;


void deposit(int value){
    if (usingMutex){
        pthread_mutex_lock(&lock);
    }
    balance = balance + value;
    if (amplifyRaceConditionRisk){
        sleep(0.01);
    }
    if (usingMutex){
        pthread_mutex_unlock(&lock);
    }
}

void withdraw(int value){
    if (usingMutex){
        pthread_mutex_lock(&lock);
    }
    balance = balance - value;
    if (amplifyRaceConditionRisk){
        sleep(0.01);
    }

    if (usingMutex){
        pthread_mutex_unlock(&lock);
    }
}

void *myThreadFun(int* myThreadId)
{
    time_t seconds = time(NULL);
    srand(*myThreadId+seconds);
    int amount = rand() % 100;
    printf("My threadId: %d\nAmount: %d\n",*myThreadId,amount);

    for (int i =0; i< iterations; i++){
        if (i%2 == 0){
            deposit(amount);
        } else {
            withdraw(amount);
        }
    }

}

int main()
{
    pthread_t thread_ids[numOfThreads];

    int x = 10;
    //Start all threads
    for (int i = 0; i < numOfThreads; i++){
        pthread_create(&thread_ids[i], NULL, myThreadFun, &thread_ids[i]);
    }

    //Join all threads
    for (int i = 0; i < numOfThreads; i++){
        pthread_join(thread_ids[i], NULL);
    }
    printf("\nExpected balance is 0\nActual balance is: %d\n",balance);
    return 0;
}
