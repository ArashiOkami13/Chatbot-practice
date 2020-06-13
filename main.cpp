/*************************************************************
Name: Raul Fosselman, William Nelson
Username: cssc2104
Class: CS570 Summer 2020
Project: CS-570 Assignment 1
File: main.cpp
Desc: This file encompasses the entire project, upon running 7
threads write to the file quote.txt safely with the use of semaphores
*************************************************************/

#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#define NUM_THREADS     7
std::ofstream myFile;
std::string evenQuote = "Controlling complexity is the essence of computer programming.--Brian Kernigan\n";
std::string oddQuote = "Computer science is no more about computers than astronomy is about telescopes --Edsger Dijkstra\n";
sem_t FLAG;

void * printHello(void * tid){
    //Let each thread print their output 8 times
    for (int i = 0; i < 9; i++)
    {
        //Sleep 2 or 3 seconds
        sleep(2 + ((long) tid % 2));

        //Decrement semaphore (lock)
        sem_wait(&FLAG);
        
        //Open file and append a quote to it
        myFile.open("quote.txt", std::ios_base::app);
        if( (long) tid % 2 == 0){
            myFile << "Thread " <<  (long) tid << " is running " << evenQuote << "\r\n";
        }
        else{
            myFile << "Thread " << (long) tid << " is running " << oddQuote << "\r\n";
        }
        myFile.close();
        //Increment semaphore (unlock)
        sem_post(&FLAG);
    }
}

int main (int argc, char *argv[]) {
    std::cout << "Running ... " << "\n";

    //Open the txt file, write the Process ID to it and close it
    myFile.open ("quote.txt");
    myFile << "process id: " << getpid() << "\r\n";
    myFile.close();

    //Initialize Semaphore to 1
    sem_init(&FLAG, 0, 1);
    
    pthread_t threads[NUM_THREADS];

    //Create the threads
    for(int i = 0; i <= NUM_THREADS; i++){
        int returnCode = pthread_create(&threads[i], NULL, &printHello, (void *) i);
        if(returnCode) exit(1);
    }
    //Join threads so they dont get killed by the main  thread before they finish
    for (int i = 0; i <= NUM_THREADS; i++)
       pthread_join(threads[i], NULL);

    sem_destroy(&FLAG);

    std::cout << "Finished, check quote.txt for output " << "\n";

    return 0;
}