# Book-Delivery-Robot-Simulator

## Description
Imagine that our university library is planning to have one or more robots which will be used to
serve visitors that arrive to the library. There may be many visitors who come to the library, and
therefore these robots need to serve the visitors fairly. In this assignment, your task is to simulate the
robots serving the visitors to gather some statistics. These statistics will be used to check the
feasibility of having robots to serve visitors in the library. In overall, the main goal of this assignment
is to help you to practice queue and priority queue abstract data types.
In this library, there is a single queue and all visitors who request a book are located in a queue to
be served by the robot(s). There are three types of visitors in this library and they have a different
level of priority. Table 1 shows the visitor types with their priority values where the highest priority is
3 and the lowest priority is 1.
<p align="center">Table 1. Visitor Types</p>
<p align="center"><img src="https://i.ibb.co/gWCRkXT/Capture2.png"></p>

You will need to create and maintain a priority queue for the visitors. They will be served based on
their priority and also their arrival time. Let the following queue is the current queue of this robot.
<p align="center"><img src="https://i.ibb.co/JzPsStM/Capture.png"></p>
When a new manager visitor comes to the library and requests a book, s/he is located in the third
position of the queue (after the first two manager visitors) because his/her priority is higher than
lecturer and student visitors. Therefore, the queue will be as follows:
<p align="center"><img src="https://i.ibb.co/5KQHxjd/Capture3.png"></p>

First of all, you need to create a list of visitors that will request a book. For each visitor, you need to
keep the track of the following:
* Visitor type (M, L or S) – this will represent their priority;
* Arrival time (in minutes, such as at 15th minute) – this will represent when they requested a
book;
* Service time (in minutes) – this will represent how long it will take the robot to serve a book
which means the time the robot needs to collect a book and deliver it to the visitor;
Service start time (in minutes) – this will represent the actual time the robot will start to serve
this particular visitor;
* The ID of the robot who served the visitor (the ID of the first robot is 1, the ID of the second
robot is 2, … so) – This is to be able to represent the possibility that the library might have
more than one robots.
* The ISBN of the book requested (ISBN is 13 characters1).
The number of visitors, the number of robots, the maximum arrival time, and the maximum service
time should be provided as an input at the beginning of the program.

You need to name your program as robotSimulator and needs to run on a command line by
using the following format:
* robotSimulator noOfVisitors noOfRobots maxArrivalTime maxServiceTime
* robotSimulator 5 2 20 5

(An example of a visitor list created with the following input is shown in Table 2.)

Based on the given input, there are 5 visitors in the library and 2 robots. The maximum arrival time
is 20 and the maximum service time is 5. Once you get this input data from the user, then you need
to prepare your simulation data based on this given input. At the beginning, the fields of service
start time and robot ID are equal to 0, because you need to update these fields after the visitor is
served by a robot. Other fields will be prepared as follows: Since in the given example, you have
5 visitors, you need to prepare simulation data for 5 visitors based on the parameters given above.
Please see example data prepared in Table 2. You need to use a randomiser for arrival time and
service time generation. However, you need to remember that the arrival time needs to be less
than maximum arrival time given by the user and the service time needs to be less than the
maximum service time. You also need to randomly generate a type for your customers which can
be Manager Visitor (M), Lecturer Visitor (L) and Student Visitor (B). Finally, assume that the library
has a database of 10 books which is defined as follows:

char *ISBN-DB[13]={"9780534390808", "9781438253275", "9780198099307", "9789352655915",
"9780131997462", "9780131997462", "9780929306407", "9780201591187", "9780201498400",
"9781430264002"};

Based on this database, you need to randomly assign a book that a visitor can request from this
list (Hint: you can generate a random number up to the size of the array and use that as your index
to retrieve the relevant book ISBN). Assume that we have a sufficient number of copies for each
book. You can see an example data in Table 2 which is prepared based on the input above.
<p align="center">Table 2. An example of a visitor list</p>
<p align="center"><img src="https://i.ibb.co/tQPrLqW/Capture4.png"></p>

When your visitor list is ready, you need to create an empty queue and also an integer array to
keep the availability of the robots (0: Busy, 1: Available). For example, if there are two robots, you
need to have an array of 2 integers. As these robots are available at the beginning, you need to
initialise the array with 1s.
Once these are ready then you need to start processing the visitors which are prepared in the
visitors’ list. When a visitor comes to the library at his/her arrival time (note that you generated them
randomly), you need to check the current state of the queue.
* If nobody is waiting in the queue, you need to randomly assign the visitor to one of the
robots to be served and you need to make the availability of that robot "Busy" and then
update the service start time for the visitor.
* If the queue is not empty, you need to locate the visitor in the appropriate position in the
queue (see an example above).
When a visitor is served by a particular robot, the robot ID should be updated for the visitor. After
that, the availability of the robot should be converted to "Available". When a robot is available for
next visitor and there is another visitor in the queue, the visitor should be assigned to that robot.
When more than one robot are available at the same time, you need to randomly assign the first
visitor in the queue to one of the available robots. When all the visitors are served, the simulation
will be completed.
You will also need to maintain a simulated clock which keeps the time of the latest event handled.
There are three types of events which are as follows: (1) visitor arrival, (2) start service and (3)
complete service. At the beginning, the simulated clock should be equal to 0. Regarding the
simulated clock, two example of scenarios are given below.
* If the first event is "visitor arrival" at the 5th minute, then you need to advance the simulated
clock to 5.
* If the current clock is 21 and the nearest event is "complete service" at the 25th minute,
then you need to advance the simulated clock to 25.
When the simulation is completed, you need to report the following information/statistics:
* The number of robots: How many robots served the visitors? (This is already given to you by
the user)
* The number of visitors: How many visitors were served? (This is already given to you by the
user)
* The number of visitors for each robot: How many visitors were served by each robot?
* The completion time: How long did it take to complete the simulation?
* Average time spent in the queue: What was the average delay in the queue? You need
to calculate the total waiting time of all visitors in the queue and then divide this by the
number of visitors you have. This will give you the average waiting time in the queue.
* Maximum waiting time: What was the longest wait time in the queue? You need to find the
visitor who waited longest in the queue.
* Most popular book. This will display the book that is requested by most of the visitors.
When a customer is served by a robot, you need to put it back to the list of visitors that is created
at the beginning of the program. Then you need to use the list to provide the required
information/statistics.

## Programming Requirements
In this assignments, you are expected to write the following functions:
* parseInput: This function should parse the input and set the values of the number of
visitors, the number of robots, the maximum arrival time and the maximum service time.
* createVisitorList: This function should randomly create visitors based on the input (the
number of visitors, the number of robots, the maximum arrival time, the maximum service
time). The visitors should be stored in a linked list in ascending order based on their arrival
time.
* initialiseSimulator: This function should create an empty queue, and also an integer
array to keep the availability of the robots.
* newVisitor: This function takes a visitor from the visitor list based on the arrival time and
add him/her to the queue.
* serveVisitor: This function takes a visitor from the queue to be served by a robot.
* reportStatistics: This function reports the statistics, such as the average time spent in
the queue, maximum waiting time, etc. (see above).
* main: The main function is responsible to coordinate all the functions, simulated clock and
other required operations to run the simulator successfully.
