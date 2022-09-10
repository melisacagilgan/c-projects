#include "Header.h"

int main(int argc, char **argv)
{
    Queue myQueue;
    List myList;
    Robot myRobots;
    srand(time(NULL));

    char *ISBN[13] = {"9780534390808", "9781438253275", "9780198099307", "9789352655915", "9780131997462",
                      "9780131997467", "9780929306407", "9780201591187", "9780201498400", "9781430264002"};
    int intISBN[10] = {0};
    int noOfVisitors;
    int noOfRobots;
    int maxArrivalTime;
    int maxServiceTime;
    int counter = 0;
    int clock = 0;     // To keep the global time
    int maxTime = 0;   // To keep the max time
    int totalTime = 0; // To keep the total time

    if (argc < 5)
    {
        printf("Too little arguments. Exitting...\n");
        system("PAUSE");
        return 0;
    }

    parseInput(argv, &noOfVisitors, &noOfRobots, &maxArrivalTime,
               &maxServiceTime); // To parse the input taking from the command line

    myList = createVisitorList(myList, noOfVisitors, noOfRobots, maxArrivalTime, maxServiceTime,
                               ISBN); // To initialize myList, myQueue, myRobots
    myQueue = initialiseSimulatorQueue(myQueue);
    myRobots = initialiseSimulatorRobots(myRobots, noOfRobots);

    while (counter < noOfVisitors)
    {
        newVisitor(myList, myQueue, ISBN, intISBN);
        counter++;
    }
    counter = 0;
    while (counter < noOfVisitors)
    {
        counter += serveVisitor(myList, myQueue, myRobots, clock, &maxTime, &totalTime);
        clock++;
    }

    reportStatistics(myList, myRobots, noOfVisitors, noOfRobots, clock, intISBN, ISBN, maxTime, totalTime);

    system("PAUSE");
    return 0;
}
