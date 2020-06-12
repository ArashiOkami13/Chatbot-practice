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

void * printHello(void * something){
    sem_wait(&FLAG);

    std::cout << "printing " << (long) something << "\n";
    myFile.open("quote.txt", std::ios_base::app);
    if( (long) something % 2 == 0){
        // sleep(2);
        myFile << "Thread " << std::to_string( (long) something ) << " is running " << evenQuote << "\r\n";
    }
    else{
        // sleep(3);
        myFile << "Thread " << std::to_string( (long) something ) << " is running " << oddQuote << "\r\n";
    }
    myFile.close();
    sem_post(&FLAG);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    //Open the txt file, write to it and close it
    myFile.open ("quote.txt");
    myFile << std::to_string( getpid() ) <<"\r\n";
    myFile.close();

    //Initialize Semaphore to 1
    sem_init(&FLAG, 0, 1);
    
    pthread_t threads[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++){
        int returnCode = pthread_create(&threads[i], NULL, &printHello, (void *) i);
        if(returnCode) std::cout << "error";
        std::cout << "nothing interesting " << "\n";
    }

    return 0;
}