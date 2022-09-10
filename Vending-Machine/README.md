# Vending-Machine

## Purpose
The main purpose of this programming assignment is to revise functions, pointers, pass by value vs. pass by reference, arrays.

## Description
In this programming assignment, you will be implementing a program that simulates a vending machine, i.e. the sale of items, coin counting and change giving. This vending machine will work as follows. A customer will first deposit an initial amount of money and then select an item from the vending machine. Your program must check that the customer makes a valid selection. If it is a valid selection, then the price of selected item will be deducted from the initial deposit and also the number of items in your vending machine will be updated accordingly. Once the customer has finished his/her selection, then your vending machine calculates the denominations of coins that are to be returned to the customer as change. Assume that only 1 TL, 0.5 TL, 0.20 TL, 0.10 TL and 0.05 TL coins are available for making change. With this vending machine, assume that the customer can select only one item at a time. There are 10 of each item at the beginning of each day. If a customer selects an item that is no longer available, then the vending machine will display an error message. Your vending machine starts when it is switched on and only stops when power is shut off. In this vending machine, the following selections are on offer:
1. Water 1.00 TL
2. Coke 1.20 TL
3. Diet Coke 1.20 TL
4. Iced Tea 1.00 TL
5. Swiss Chocolate 1.50 TL
6. Candy 0.95 TL
7. Chips 2.50 TL
8. Bubble Gum 1.50 TL
9. Turkish Delight 2.00 TL

## Programming Requirements
1. You must implement functions ShowMenu(), MakeSelection(), Maintenance(), ReturnChange(), and DisplayErrorMessage() with the appropriate parameters. These functions need to function as follows:

      **ShowMenu()** function will display the offered selections as given above.

      **MakeSelection()** function will get the deposit and selection from the user. The price of selected item will be deducted from the users’ initial deposit.

      **ReturnChange()** function returns 'change' equal to 'total' based on the 'coins' available. Sometimes enough coins may not be available to return correct change, in that case your program should check the next largest number of coins possible (see requirement 2)

      **DisplayErrorMessage()** function will display an error message at least for the following cases (if needed you can add more):
  
            I. If the selected item is not available.
    
            II. If the customer has deposited insufficient amount of cash.
    
            III. If the vending machine does not have enough cash to make return change
    
            IV. If the customer makes an invalid selection.
    
      **Maintenance()** -- As part of routine maintenance – when selection -1 is entered, the vending machine will expect a fixed pin code, which will be defined in the program, in order for maintenance to proceed; do not display this selection to the customer – all items in the vending machine are restocked. Also, the number of sales for each item, the total balance given and the net income for that day are displayed. So your function Maintenance() function should collect information about sales and restocks the vending machine.

2. Assume that the vending machine starts every morning with a 10 number of coins of each denomination and 10 items. If the vending machine has run out of a particular
coin, then alternate means for giving change must be found. For example, assume that user wants to buy water, pays 5 TL and the machine has run out of 1 TL left, then it gives 8 0.5 TL. Your program should check the next largest coin in order to give change to the customer. If no accurate change can be returned to the customer, then his/her current selection will be ignored. In that case, your vending machine should display an error message and give the deposit back to customer.
