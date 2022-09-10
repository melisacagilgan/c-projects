#include <math.h>
#include <stdio.h>

int main()
{
    int option, base;
    int a, b, cin;
    int num, num2, bin = 0, i = 0;
    int valid, count;
    int sum, cout;
    char ch_num, ch_num2;
    int cumulative_sum = 0; /*Cumulative sum to store the entered number in base 16*/

    do /*My main loop is started here.*/
    {
        printf("Welcome to Full Adder!\n");
        printf("(1) Compute and Display the Outputs\n");
        printf("(2) Quit\nYou choose: ");
        scanf("%d", &option);
        printf("You have chosen option %d\n", option);
        if (option == 1)
        {
            printf("Which base will you use to enter data lines (base 16/8/2)?");
            scanf("%d", &base);
            if (base == 2)
            {
                do
                {
                    printf("Please enter input:");
                    scanf("%d", &num);
                    if (num > 999)
                    {
                        printf("This number does not consist of 3 digits. Please try again!\n"); /*Error message*/
                        valid = 0; /*My condition to check the validity of the number. Valid=1 for true, valid=0 for
                                      false condition.*/
                    }
                    else
                    {
                        /*Thanks to the following calculations, I found the num's digits one by one.*/
                        cin = num % 10;
                        b = (num / 10) % 10;
                        a = num / 100;
                        if ((a == 1 || a == 0) && (b == 1 || b == 0) && (cin == 1 || cin == 0))
                            valid = 1;
                        else
                        {
                            printf("This is not a valid number in base 2! Please try again!\n"); /*Error message*/
                            valid = 0;
                        }
                    }

                } while (valid == 0);
            }
            else if (base == 8)
            {
                do
                {
                    printf("Please enter input:");
                    scanf("%d", &num);
                    num2 = num;               /*To be able to print the original value to the screen at the end.*/
                    if (num >= 0 && num <= 7) /*All these values are valid in base 8 and their binary representations
                                                 are in 3 digits.*/
                    {
                        i = 0;
                        bin = 0;
                        valid = 1;
                        while (num > 0)
                        {
                            bin += num % 2 * pow(10, i);
                            num /= 2;
                            i++;
                        }
                        cin = bin % 10;
                        b = (bin / 10) % 10;
                        a = bin / 100;
                    }
                    else
                    {
                        i = 0;
                        valid = 0;
                        while (num > 0)
                        {
                            num /= 10; /*With this calculation,my program is able to check all the digits one by one to
                                          see whether it is invalid for base 8 or not.*/
                            if (num % 10 > 7)
                            {
                                count = 1;
                                break;
                            }
                            else
                                count = 0;
                        }
                        if (count == 1)
                        {
                            printf("This is not a valid number in base 8! Please try again!\n"); /*Error message*/
                        }
                        if (count == 0)
                        {
                            printf("Octal %d cannot be represented with 3 bits! Please try again!\n",
                                   num2); /*Error message*/
                        }
                    }

                } while (valid == 0);
            }
            else if (base == 16)
            {
                do
                {
                    printf("Please enter input:");
                    scanf(" %c", &ch_num);
                    while (1)
                    {
                        if (ch_num == 10) /*Enter is read*/
                        {
                            break; /*Exit the loop*/
                        }
                        else
                        {
                            if ((ch_num >= 65 && ch_num <= 70) || (ch_num >= 97 && ch_num <= 102)) /*Letter is read*/
                            {
                                count = 1;
                                valid = 0;
                                switch (ch_num)
                                {
                                case 'A':
                                case 'a':
                                    ch_num2 = 'A'; /*I stored the ch_num value here in order that I can print it out*/
                                    break;
                                case 'B':
                                case 'b':
                                    ch_num2 = 'B';
                                    break;
                                case 'C':
                                case 'c':
                                    ch_num2 = 'C';
                                    break;
                                case 'D':
                                case 'd':
                                    ch_num2 = 'D';
                                    break;
                                case 'E':
                                case 'e':
                                    ch_num2 = 'E';
                                    break;
                                case 'F':
                                case 'f':
                                    ch_num2 = 'F';
                                    break;
                                }
                            }
                            else if (ch_num > 70 && ch_num <= 90 || ch_num > 102 && ch_num <= 122)
                            {
                                count = 2;
                                printf("This is not a valid number in base 16! Please try again!\n"); /*Error message*/
                                valid = 0;
                            }
                            else if (ch_num >= 48 && ch_num <= 57) /*Digit is read*/
                            {
                                num = ch_num - '0';
                                cumulative_sum *=
                                    10; /*Multiply the cumulative sum in order to shift it to the left by one digit*/
                                cumulative_sum += num; /*Add the number to the last digit*/
                            }
                        }
                        scanf("%c", &ch_num);
                    }
                    if (cumulative_sum <= 7 && count != 1 && count != 2)
                    {
                        i = 0;
                        bin = 0;
                        valid = 1;
                        while (cumulative_sum > 0)
                        {
                            bin += cumulative_sum % 2 * pow(10, i);
                            cumulative_sum /= 2;
                            i++;
                        }
                        cin = bin % 10;
                        b = (bin / 10) % 10;
                        a = bin / 100;
                    }
                    else if (cumulative_sum > 7 && count != 1 && count != 2)
                    {
                        printf("Hexadecimal %d cannot be represented with 3 bits! Please try again!\n",
                               cumulative_sum); /*Error message*/
                        cumulative_sum = 0;
                        valid = 0;
                    }
                    else if (count == 1)
                    {
                        valid = 0;
                        if (cumulative_sum != 0)
                        {
                            printf("Hexadecimal %c%d cannot be represented with 3 bits! Please try again!\n", ch_num2,
                                   cumulative_sum);
                        }
                        else
                        {
                            printf("Hexadecimal %c cannot be represented with 3 bits! Please try again!\n", ch_num2);
                        }
                        cumulative_sum = 0;
                        count = 3; /*To reset the value of count. If I had not done this,there would occur a bug after
                                      user enters the invalid numbers(count would always be equal to 1)*/
                    }
                } while (valid == 0);
            }
            else
            {
                printf(
                    "You have chosen the wrong base. Please try again!\n"); /*Error message in case of choosing a wrong
                                                                               option to avoid a run time error.*/
            }
            if (valid == 1) /*To avoid printing the value of sum and c_out when the number is not a valid one.*/
            {
                /*Truth Table for a,b and cin to calculate sum and cout*/
                if ((a == b && cin == 1) || ((a != b) && cin == 0))
                {
                    sum = 1;
                }
                else
                {
                    sum = 0;
                }
                if ((a + b == 2) || (a + b == 1 && cin == 1))
                {
                    cout = 1;
                }
                else
                {
                    cout = 0;
                }

                printf("Sum is %d C_out is %d\n\n", sum, cout);
            }
        }
        else if (option == 2) /*Sentinel value for my main loop.*/
        {
            printf("Byee!!");
        }
        else
        {
            printf("You have chosen the wrong option. Please try again!\n"); /*Error message in case of choosing a wrong
                                                                                option to avoid a run time error.*/
        }

    } while (option != 2);
    return 0;
}
