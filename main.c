/*
 * AUTHOR       :   Chance Johnson
 * DATE         :   13 November, 2017
 * COURSE       :   CSCI 415 Intro. to OSs
 * PROFESSOR    :   Dr. Vipin Menon
 * SCHOOL       :   McNeese State University
 * ASSIGNMENT   :   Project 2
 * FILE         :   main.c
 */


/*
 * This program simulates a CPU Priority Scheduler with the help of prime numbers.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

// Struct for the process control blocks
struct pcb {
    int processId;
    char processState[20];
    int processLocation;
    int processPriority;
    int processTime;
};

// This array of pcbs serves as our "Ready Queue"
struct pcb processControlBlocks[4];

// Output file
FILE *output;

void sortProcesses(struct pcb processControlBlocks[4]);

void readProcessControlBlocks();

int isPrime(int n);

int getNextPrimeNumberAfter(int n);

void priorityScheduler(struct pcb processControlBlocks[4]);


/*
 Main function
 */
int main() {

    output = fopen("output.txt", "a");
    if (output == NULL) {
        printf("\nError opening output file.");
    }

    printf("\nThis program simulates the Priority CPU Scheduler with the help of prime numbers.");
    fprintf(output, "This program simulates the Priority CPU Scheduler with the help of prime numbers.");
    printf("\nThere will be a total of 44,000 prime numbers printed after all processes have run.");
    fprintf(output, "\nThere will be a total of 44,000 prime numbers printed after all processes have run.");
    printf("\nPress any key to watch, wait, and see...");
    fprintf(output, "\nPress any key to watch, wait, and see...");
    getchar();
    printf("\nEnjoy the ride :)");
    fprintf(output, "\nEnjoy the ride :)\n\n");


    // Read in the processes from the text file
    readProcessControlBlocks();

    // Sort the PCBs according to priority
    sortProcesses(processControlBlocks);

    // Schedule and run the processes according to priority
    priorityScheduler(processControlBlocks);

    // Close the output text file
    fclose(output);


    getchar();
    getchar();

    return 0;
}


/*
 This function reads the text file to get information about the PCBs
 */
void readProcessControlBlocks() {

    // Point to the file containing the PCBs
    FILE *fp;


    int currentLine = 0;
    char tempLine[100]; // Temp variable used for reading in the PCBs

    //  Open our file containing the PCBs and read them
    if (fp = fopen("processes.txt", "r")) {

        while ((fgets(tempLine, sizeof(tempLine), fp) != EOF) && currentLine < 4) {
            sscanf(tempLine, "%d %s %d %d %d", &processControlBlocks[currentLine].processId,
                   processControlBlocks[currentLine].processState, &processControlBlocks[currentLine].processLocation,
                   &processControlBlocks[currentLine].processPriority, &processControlBlocks[currentLine].processTime);

            printf("\nProcess %s", tempLine);
            fprintf(output, "\nProcess %s", tempLine);
            currentLine++;
        }
    } else {
        printf("\nERROR: Could not open file.\n");
        fprintf(output, "\nERROR: Could not open file.\n");
        return;
    }

    fclose(fp);
}

/*
 * This function sorts the processes according to priority
 * using the simple Bubble Sort algorithm
 */
void sortProcesses(struct pcb processControlBlocks[4]) {

    int i;
    struct pcb temp;
    int j;

    for (i = 0; i < sizeof(processControlBlocks); i++) {

        for (j= 0; j < (sizeof(processControlBlocks) - i - 1); j++) {

            // If two processes have the same priority, the shortest job goes first
            if (processControlBlocks[j].processPriority == processControlBlocks[j+1].processPriority) {
                if ( processControlBlocks[j+1].processTime < processControlBlocks[j].processTime) {
                    temp = processControlBlocks[j];
                    processControlBlocks[j] = processControlBlocks[j+1];
                    processControlBlocks[j+1] = temp;
                }
            }
            else if (processControlBlocks[j].processPriority < processControlBlocks[j+1].processPriority) {

                temp = processControlBlocks[j];
                processControlBlocks[j] = processControlBlocks[j+1];
                processControlBlocks[j+1] = temp;
            }
        }
    }
}


/*
 This function checks to see if a number, n, is prime or not.
 */
int isPrime(int n) {
    int i; // loop variable

    if (n == 2){
        return 1;
    }

    if (n % 2 == 0) {
        return 0;
    }

    for (i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}


/*
 This function gets the next prime number after n.
 */
int getNextPrimeNumberAfter(int n) {
    int next = n + 1; // The number after n

    // If the next number is not prime, go to the next integer.
    while (isPrime(next) != 1) {
        next++;
    }

    return next; // There will always be a next prime number after n.
}


/*
 This function serves as our time slice. One unit of time in our case is 1,000 prime numbers.
 With our Priority Scheduling, we are using time slices of 4 units for each process.
 Therefore, this function will perform one time slice and print 4,000 prime numbers until there
 is no time left for the prioritized process.

 It will take in the last prime number that was printed and it will return
 the last prime number that it prints.
 */
int printPrimeNumbers(int lastPrimeNumberPrinted) {

    int numberOfPrimesPrinted;

    // Until we have printed 4,000 prime numbers, we need to keep getting
    // the next prime number and printing it.
    while (numberOfPrimesPrinted < 4000) {
        // Print the next prime number after the last printed prime number.
        printf("\n%5d", getNextPrimeNumberAfter(lastPrimeNumberPrinted));
        fprintf(output, "\n%5d", getNextPrimeNumberAfter(lastPrimeNumberPrinted));

        // The last printed prime number is now the prime number that was just printed
        // which is the next prime number after the last prime number printed.
        lastPrimeNumberPrinted = getNextPrimeNumberAfter(lastPrimeNumberPrinted);
        numberOfPrimesPrinted++;
    }
    return lastPrimeNumberPrinted;
}


/*
 * This function implements the Priority Scheduler Algorithm
 */
void priorityScheduler(struct pcb processControlBlocks[4]) {

    int lastPrimeNumberPrinted = 0;
    int completedProcesses = 0;
    int i;


    while (1) {
        for (i = 0; i <= 3; i++) {

            // While the prioritized process is ready and still has time remaining, run that process.
            while (processControlBlocks[i].processTime != 0) {
                // Run the process
                printf("\nPROCESS %d RUNS", processControlBlocks[i].processId);
                fprintf(output, "\nPROCESS %d RUNS", processControlBlocks[i].processId);
                // Keep track of the last printed prime number
                lastPrimeNumberPrinted = printPrimeNumbers(lastPrimeNumberPrinted);
                // Subtract a time slice from the process that just ran
                processControlBlocks[i].processTime = processControlBlocks[i].processTime - 4;
            }

            // Determine whether the process is finished or has more time to run
            if ((processControlBlocks[i].processTime == 0) &&
                (processControlBlocks[i].processState != "Terminated")) {
                // Process has no time left. It is finished running
                printf("\nPROCESS %d IS FINISHED", processControlBlocks[i].processId);
                fprintf(output, "\nPROCESS %d IS FINISHED", processControlBlocks[i].processId);
                // Change the process state from ready to terminated
                strcpy(processControlBlocks[i].processState, "Terminated");
                // Add one to the completed processes counter
                completedProcesses++;
            }

            /*
             * This would be used to pause the process. Because we are using priority scheduling,
             * we let the higher priority processes run until they are finished without pausing them.
             */
            /*
            else if (processControlBlocks[i].processTime > 0) {
                printf("\nPROCESS %d IS PAUSED", processControlBlocks[i].processId);
                fprintf(output, "\nPROCESS %d IS PAUSED", processControlBlocks[i].processId);
            }
             */

            // If all processes are complete. Exit the loop.
            if (completedProcesses == sizeof(processControlBlocks)) {
                break;
            }

        }
        // Our work here is done.
        printf("\nALL PROCESSES COMPLETE.");
        fprintf(output, "\nALL PROCESSES COMPLETE.");
        break;
    }
}
