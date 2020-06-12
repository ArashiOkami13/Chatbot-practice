#include <unistd.h>
#include <semaphore.h>
#include <iostream>
#include <fstream>
#define NUM_THREADS     7
std::ofstream myFile;
std::string evenQuote = "Controlling complexity is the essence of computer programming.--Brian Kernigan";
std::string oddQuote = "Computer science is no more about computers than astronomy is about telescopes --Edsger Dijkstra";
sem_t FLAG;

void * printHello(void * threadID){
    for(int i = 0; i < NUM_THREADS; i++){
        long tid = 2;
        // long tid = (long) threadID;
        std::cout << tid;
        sem_wait(&FLAG); // Decrement, lock the semaphore
        myFile.open("quote.txt", std::ios::ate);
        if( tid % 2 == 0){
            // sleep(2);
            myFile << "Thread " << threadID << " is  running " << evenQuote << "\r\n";
        }
        else{
            // sleep(3);
            myFile << "Thread " << threadID << " is  running " << evenQuote << "\r\n";
        }
        myFile.close();
        sem_post(&FLAG); //increment, unlock the semaphore
    }
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    //Open the txt file, write to it and close it
    myFile.open ("quote.txt");
    myFile << getpid() <<"\r\n";
    myFile.close();

    //Initialize Semaphore to 1
    sem_init(&FLAG, 0, 1);
    
    pthread_t threads[NUM_THREADS];
    std::cout<< "do we lock here?";
    for(int i = 0; i < NUM_THREADS; i++){
        int returnCode = pthread_create(&threads[i], NULL, &printHello, (void *)i);
        if(returnCode) std::cout << "error";
    }

    pthread_exit(NULL);
    return 0;
}