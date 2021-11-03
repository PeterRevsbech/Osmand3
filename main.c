#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define numOfThreads 5
int balance = 0;
pthread_mutex_t lock;


void deposit(int value){
    pthread_mutex_lock(&lock);
    balance = balance + value;
    pthread_mutex_unlock(&lock);
}

void withdraw(int value){
    pthread_mutex_lock(&lock);
    balance = balance - value;
    pthread_mutex_unlock(&lock);
}

void *myThreadFun(int* myThreadId)
{
    srand(*myThreadId);
    int amount = rand() % 100;
    printf("My threadId: %d\nAmount: %d\n",*myThreadId,amount);

    for (int i =0; i< 10; i++){
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

    printf("Balance: %d\n",balance);
    return 0;
}
