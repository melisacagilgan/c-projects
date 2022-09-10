#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void ShowMenu();
void MakeSelection();
void ReturnChange();
void DisplayErrorMessage();
void Maintenance();

int main()
{
    double money, change_money;
    int item;
    float pricesArray[9] = {1, 1.2, 1.2, 1, 1.5, 0.95, 2.5, 1.5, 2};
    int product_amountArray[9] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
    int money_amountArray[5] = {10, 10, 10, 10, 10};
    ShowMenu(&pricesArray); // I defined almost all of my variables in the main function and sent other functions their
                            // addresses by using pointer declaration
    MakeSelection(&money, &change_money, &pricesArray, &product_amountArray, &money_amountArray, &item);
    if (money == (-1))
        Maintenance(&money, &product_amountArray, &money_amountArray, &pricesArray);
    return 0;
}

void ShowMenu(float *pricesArray)
{
    printf("\n\n");
    printf("1. Water %.2f TL\n", pricesArray[0]);
    printf("2. Coke %.2f TL\n", pricesArray[1]);
    printf("3. Diet Coke %.2f TL\n", pricesArray[2]);
    printf("4. Iced Tea %.2f TL\n", pricesArray[3]);
    printf("5. Swiss Chocolate %.2f TL\n", pricesArray[4]);
    printf("6. Candy %.2f TL\n", pricesArray[5]);
    printf("7. Chips %.2f TL\n", pricesArray[6]);
    printf("8. Bubble Gum %.2f TL\n", pricesArray[7]);
    printf("9. Turkish Delight %.2f TL\n", pricesArray[8]);
}
void MakeSelection(double *money, double *change_money, float *pricesArray, int *product_amountArray,
                   int *money_amountArray, int *item)
{
    int valid = 0;
    double **p_money; // These are pointer pointing to another pointer to keep adresses of my main variables
    double **p_change_money;
    float **p_pricesArray;
    int **p_product_amountArray;
    int **p_money_amountArray;
    int **p_item;
    p_money = &money;
    p_change_money = &change_money;
    p_pricesArray = &pricesArray;
    p_product_amountArray = &product_amountArray;
    p_money_amountArray = &money_amountArray;
    p_item = &item;
    do
    {
        printf("\n\nEnter amount of money:");
        scanf("%lf", money);
        if (*money == (-1)) // Maintenance condition check
        {
            break;
        }
        else
        {
            do
            {
                printf("Select an item:");
                scanf("%d", item);
                if ((*item) < 1 || (*item) > 9) // to check whether the selection is valid or not
                {
                    valid = 1;
                    DisplayErrorMessage(valid);
                }
                else
                {
                    valid = 0;
                }
            } while (valid == 1);
            if (pricesArray[*item - 1] > (*money)) // Error conditions
            {
                valid = 2;
                DisplayErrorMessage(valid);
                ShowMenu(pricesArray);
            }
            else if (product_amountArray[*item - 1] == 0)
            {
                valid = 3;
                DisplayErrorMessage(valid);
                ShowMenu(pricesArray);
            }
            else
            {
                ReturnChange(*p_money, *p_change_money, *p_pricesArray, *p_product_amountArray, *p_money_amountArray,
                             *p_item);
            }
        }
    } while (valid >= 0); // To maintain the order loop
}

void ReturnChange(double *money, double *change_money, float *pricesArray, int *product_amountArray,
                  int *money_amountArray, int *item)
{
    int i, count = 0, valid = 0;
    double change_money2;
    float moneyTypes[5] = {1, 0.5, 0.2, 0.1, 0.05}; // Keep types of money
    int changeArray[5] = {0, 0, 0, 0, 0};           // To specify the type and number of money that we need for change.
    int change_amountArray[5] = {0, 0, 0, 0, 0};    // To print the type of money that we used for change.
    *change_money = (*money) - (pricesArray[*item - 1]);
    change_money2 = (*change_money);
    (*change_money) *= 100;
    changeArray[0] = (*change_money) / 100;
    changeArray[1] = changeArray[0] * 2;
    changeArray[2] = changeArray[0] * 2 * 4;
    changeArray[3] = changeArray[0] * 10;
    changeArray[4] = changeArray[0] * 20;
    for (i = 0; i < 5; i++)
    {
        if (money_amountArray[i] == 0)
        {
            count++;
        }
    }
    if (count == 5)
    {
        valid = 4;
        DisplayErrorMessage(valid);
    }
    else if (change_money2 <= 18.5)
    {
        while (changeArray[0] > 0 && *change_money > 0) // To change 1 TL
        {
            if (money_amountArray[0] > 0)
            {
                valid = 2;
                money_amountArray[0]--;
                changeArray[0]--;
                *change_money -= 100;
            }
            else
            {
                valid = 1;
                if (money_amountArray[1] >= 2)
                {
                    change_amountArray[1] += 2;
                    money_amountArray[1] -= 2;
                    changeArray[0]--;
                    *change_money -= 100;
                }
                else if (money_amountArray[2] == 5 || money_amountArray[2] == 10)
                {
                    change_amountArray[2] += 5;
                    money_amountArray[2] -= 5;
                    changeArray[0]--;
                    *change_money -= 100;
                }
                else if (money_amountArray[3] == 10)
                {
                    change_amountArray[3] += 10;
                    money_amountArray[3] -= 10;
                    changeArray[0]--;
                    *change_money -= 100;
                }
                else
                {
                    valid = 4;
                    DisplayErrorMessage(valid);
                    break;
                }
            }
        }
        while (changeArray[1] > 0 && *change_money > 0 && valid != 4) // To change 50 Kurus
        {
            if (money_amountArray[1] > 0)
            {
                valid = 2;
                money_amountArray[1]--;
                changeArray[1]--;
                *change_money -= 50;
            }
            else
            {
                valid = 1;
                if (money_amountArray[2] >= 2 && money_amountArray[3] > 0)
                {
                    change_amountArray[2] += 2;
                    money_amountArray[2] -= 2;
                    change_amountArray[3]++;
                    money_amountArray[3]--;
                    changeArray[1]--;
                    *change_money -= 50;
                }
                else if (money_amountArray[3] == 5 || money_amountArray[3] == 10)
                {
                    change_amountArray[3] += 5;
                    money_amountArray[3] -= 5;
                    changeArray[1]--;
                    *change_money -= 50;
                }
                else if (money_amountArray[4] == 10)
                {
                    change_amountArray[4] += 10;
                    money_amountArray[4] -= 10;
                    changeArray[1]--;
                    *change_money -= 50;
                }
                else
                {
                    valid = 4;
                    DisplayErrorMessage(valid);
                    break;
                }
            }
        }
        while (changeArray[2] > 0 && *change_money > 0 && valid != 4) // To change 20 Kurus
        {
            if (money_amountArray[2] > 0)
            {
                valid = 2;
                money_amountArray[2]--;
                changeArray[2]--;
                *change_money -= 20;
            }
            else
            {
                valid = 1;
                if (money_amountArray[3] >= 2)
                {
                    change_amountArray[3] += 2;
                    money_amountArray[3] -= 2;
                    changeArray[2]--;
                    *change_money -= 20;
                }
                else if (money_amountArray[4] == 4 || money_amountArray[4] == 8)
                {
                    change_amountArray[4] += 5;
                    money_amountArray[4] -= 5;
                    changeArray[2]--;
                    *change_money -= 20;
                }
                else
                {
                    valid = 4;
                    DisplayErrorMessage(valid);
                    break;
                }
            }
        }
        while (changeArray[3] > 0 && *change_money > 0 && valid != 4) // To change 10 Kurus
        {
            if (money_amountArray[3] > 0)
            {
                valid = 2;
                money_amountArray[3]--;
                changeArray[3]--;
                *change_money -= 10;
            }
            else
            {
                valid = 1;
                if (money_amountArray[4] >= 2)
                {
                    change_amountArray[4] += 2;
                    money_amountArray[4] -= 2;
                    changeArray[3]--;
                    *change_money -= 20;
                }
                else
                {
                    valid = 4;
                    DisplayErrorMessage(valid);
                    break;
                }
            }
        }
        if (valid != 4)
        {
            printf("Get your item! Change: %.2fTL. ", change_money2);
            if (valid != 1)
            {
                ShowMenu(pricesArray);
            }
            if (valid == 1) // To print the amount and type of money that we used for change.
            {
                for (i = 0; i < 5; i++)
                {
                    if (change_amountArray[i] > 0)
                    {
                        printf("No %.2fTLs left, ", moneyTypes[i - 1]);
                        printf("%d %.2fTLs ", change_amountArray[i], moneyTypes[i]);
                    }
                }
                printf("are used. ");
                ShowMenu(pricesArray);
            }
            else if (valid != 1 && valid != 2) // Greedy Algorithm to find the minimum coin combination
            {

                change_money2 *= 100;
                while (change_money2 >= 0)
                {
                    if (change_money2 >= 100 && money_amountArray[0] > 0)
                    {
                        change_money2 -= 100;
                        money_amountArray[0]--;
                    }
                    else if (change_money2 >= 50 && money_amountArray[1] > 0)
                    {
                        change_money2 -= 50;
                        money_amountArray[1]--;
                    }
                    else if (change_money2 >= 20 && money_amountArray[2] > 0)
                    {
                        change_money2 -= 20;
                        money_amountArray[2]--;
                    }
                    else if (change_money2 >= 10 && money_amountArray[3] > 0)
                    {
                        change_money2 -= 10;
                        money_amountArray[3]--;
                    }
                    else if (change_money2 >= 5 && money_amountArray[4] > 0)
                    {
                        change_money2 -= 5;
                        money_amountArray[4]--;
                    }
                    else
                    {
                        product_amountArray[*item - 1]--; // To count the number of products sold
                        return;
                    }
                }
            }
            if (valid != 4)
            {
                product_amountArray[*item - 1]--; // To count the number of products sold except from the ones whose
                                                  // amount of money are calculated by greedy algorithm
            }
        }
    }
    else
    {
        valid = 4;
        DisplayErrorMessage(valid);
    }
}

void DisplayErrorMessage(int valid)
{
    if (valid == 1)
    {
        printf("Error! Invalid selection!\n");
    }
    else if (valid == 2)
    {
        printf("Error! Insufficient amount of money! Take your money back!\n");
    }
    else if (valid == 3)
    {
        printf("Error! Insufficient amount of product! Take your money back!\n");
    }
    else if (valid == 4)
    {
        printf("Error! Insufficient amount of money to return back in change! Take your money back!\n");
    }
}
void Maintenance(double *money, int *product_amountArray, int *money_amountArray, float *pricesArray)
{
    float net_income = 0;
    if (*money == (-1))
    {
        int i;
        int user_pin, pin_code = 1234;
        printf("Enter pin code:");
        scanf("%d", &user_pin);
        if (user_pin == pin_code)
        {
            printf("\n\nDAILY REPORT\n\n");
            printf("Number of items left:");
            printf("\n1. Water: %d", *(product_amountArray + 0));
            printf("\n2. Coke: %d", *(product_amountArray + 1));
            printf("\n3. Diet Coke: %d", *(product_amountArray + 2));
            printf("\n4. Iced Tea: %d", *(product_amountArray + 3));
            printf("\n5. Swiss Chocolate: %d", *(product_amountArray + 4));
            printf("\n6. Candy: %d", *(product_amountArray + 5));
            printf("\n7. Chips: %d", *(product_amountArray + 6));
            printf("\n8. Bubble Gum: %d", *(product_amountArray + 7));
            printf("\n9. Turkish Delight: %d", *(product_amountArray + 8));
            printf("\n\nNumber of coins left:\n");
            printf("1 TL: %d LEFT\n", *(money_amountArray + 0));
            printf("50 Kurus: %d LEFT\n", *(money_amountArray + 1));
            printf("20 Kurus: %d LEFT\n", *(money_amountArray + 2));
            printf("10 Kurus: %d LEFT\n", *(money_amountArray + 3));
            printf("5 Kurus: %d LEFT\n", *(money_amountArray + 4));
            for (i = 0; i < 9; i++) // To calculate the total amount of income
            {
                net_income += (10 - *(product_amountArray + i)) * (*(pricesArray + i));
            }
            for (i = 0; i < 9; i++) // Restocked
            {
                *(product_amountArray + i) = 10;
            }
            for (i = 0; i < 5; i++)
            {
                *(money_amountArray + i) = 10;
            }
            printf("\nNet Income:%.2f TL\n", net_income);
            printf("All items in the vending machine are restocked!\n");
        }
    }
}
