# Turkish-Basketball-League-Score-Board-BSL

## Purpose
The main purpose of this programming assignment is to revise the topics of the fundamentals of C programming, conditional statements, repetitive statements, functions, arrays, pointers, dynamic memory allocation, files, strings etc.

## Description
You will write a program to computerize the score board of the Turkish basketball league for a season and calculate certain statistics for a given team. During a season, a lot of statistics are kept about a basketball team. In this programming assignment, you will write a program that reads some statistics about a list of teams from a file and allows the user to process these statistics. Typically a lot of statistics are kept but In this assignment, you will use a simplified version. As usual don't try to compile your entire program in one "big bang". Compile it piece by piece. Test each piece that you have compiled to make sure it works correctly before you add the next piece.

## Programming Requirements
You will read the team records from a file which includes a table of records as follows:

From this table, you can compute the following additional values for these teams:
       
1. Total win = WH + WA
2. Total lost = LH + LA
3. Total Points = 2*totalWin + totalLost
       
Define a structure type to represent one row of this score board table. The structure will include a string to represent the name of the team, it will store the total games played (G), win home (WH), Lost home (LH), Win away (WA), Lost away (LA), total win (as calculated above), total lost (as calculaeted above) and total points (as calculated above). Write a program to implement the following steps to process such score board as follows.

<p align="center"><img src="https://i.ibb.co/NWhSVkC/Capture.png"></p>

1. Load the table 1 from a file into an array of structures called scoreboard_table.
2. Define and call the following functions.

**Load_Scoreboard_Table -** Takes as parameters the name of the input file and the scoreboard_table array. Function opens the file, fills the scoreboard_table array, and closes the file. Then it returns the actual array size as the function result. Please note that you cannot make an assumption about the number of rows in the given table. When you load the data from the file, you also need to compute the total win, total lost and also the total points.

**Display_Scoreboard_Table -** Takes the scoreboard_table array and its size as the parameter and displays the table on the screen. If the file has not been loaded (and thus the array is empty) then appropriate error message should be displayed to the user.

**Search -** Takes as parameters the scoreboard_table array, its actual size, and a string representing the name of the team. If the entered name is found then this function returns the position of this record in the array otherwise it returns -1 if that team is not found.

**Interactive_board –** Takes as parameters the scoreboard_table array, its actual size, and depending on the input from the user reorders the records of the teams. The user can sort the data based on the total games played and total points.
