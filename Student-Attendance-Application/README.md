# Student-Attendance-Application

## Overview
The office of international student affairs is hosting a seminar to acquaint newcomers with the rules and regulations and the different facilities METU NCC has to offer. However, due to Covid restrictions, the office intends to make a "signup to attend" application to know the number of attending students in advance so a suitable venue can be picked. In this assignment, you will develop said application.
<p align="left">You will first need to define a data structure to contain the student information in the table below.</p>
<p align="center"><img src="https://i.ibb.co/RDf4rc2/Capture.png"></p>

The registration application shall be able to perform the following functionalities:
1. Add a student.
2. Search for a student using ID.
3. Print Table.

The application shall create a hash table in which the user decides what open addressing technique to be used: If the user enters (1) then the table will use double hashing (where f(i) = i * hash2(x)), but if they enter (2), then quadratic probing (where f(i) = i2) will be used.

The initial size of the hash table should be 11. If the load factor λ (The total number of students in a hash table / the size of the hash table) becomes larger than 0.5, then the size of the hash table should be doubled and rounded to the next prime number, and then re-hashing should be performed.
The hash functions to be used:

    key = ASCII (studentid[0]) – 65 + studentid[1] + studentid[2]
    h1(key) = (2 * key) mod hashtablesize
    h2(key) = 7 – (key mod 7)

## Process Model
You can find the process model illustrated in Figure 1 below. The user will first pick whether double hashing or quadratic probing will be used to resolve collisions. After the choice is made, there is no going back on it unless the program is restarted. Then, the user will be presented with the following options:
1. **Add a student:** The operation will ask for all the necessary information. It will then create a student structure and place it in an appropriate position in the hash table. If the load factor of the hash table becomes more than 0.5, and then rehashing will be performed as mentioned above. An example is provided below where the input is shown in bold. If the id is not unique, then the application should print "Id should be unique!" and go back to the functionalities menu.
<p align="center"><img src="https://i.ibb.co/3pt5LP3/image-2022-09-10-212116283.png" width="700px"></p>
    
    Enter unique identifier: A69
    Enter name: Peter Holland
    Enter department: CNG
    Peter Holland has been registered.

2. **Search a student:** The operation will ask for a student id and then try to find the student in the hash table and then print their details if found. An example is provided below where the input is shown in bold. If the student is not found, then the application should print "Student is not found!" and go back to the main menu.

        Enter unique identifier: A69
        Name: Peter Holland
        Department: CNG

3. **Print Table:** This function will simply print the contents of the hash table in the order they are placed. As seen in the output below, if there is no element at a certain index, then the function will show nothing. You can find below examples of the output when either double hashing or quadratic probing are used. The input in the example is added in the order:
C12 Salley Bates CHM -> A56 Ashley Norman MEC -> A69 Peter Holland -> A00 George Martin ASE -> U11 Molly Eleanor PSY
<p align="center"><img src="https://i.ibb.co/Cskqxjx/Capture.png"></p>
