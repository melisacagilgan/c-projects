#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Functions that I am going to use to build the game*/
int roll_a_dice();
int play_computer();
int computer_strategy_decider();
int play_user();
void scoresheet(int, int);
int isConsecutive(int, int, int, int, int, int);
int isAllSame(int, int, int, int, int, int);
int isThreeOfaKind(int, int, int, int, int, int);

int main()
{
    srand(time(NULL));
    int player_startDie = 0, computer_startDie = 0;
    int num_round = 0, counter;
    char player_answer;
    int player_sum = 0, computer_sum = 0;

    printf("Welcome to the Zonk game.\n");
    printf("How many rounds would you like to play? ");
    scanf("%d", &num_round);
    printf("OK, lets get started!\n\n");
    do
    {
        computer_startDie = roll_a_dice();
        printf("I have rolled the dice and got %d!\n", computer_startDie);
        printf("Are you ready to Zonk! Shall I roll the dice for you (Y/N)? ");
        scanf(" %c", &player_answer);
        while (player_answer != 'Y' && player_answer != 'y' && player_answer != 'N' &&
               player_answer != 'n') /*Error check*/
        {
            printf("You entered a wrong option.Please try again!\n");
            printf("Are you ready to Zonk! Shall I roll the dice for you (Y/N)? ");
            scanf(" %c", &player_answer);
        }
        if (player_answer == 'Y' || player_answer == 'y')
        {
            player_startDie = roll_a_dice();
            printf("I have rolled the dice for you and you got %d!\n", player_startDie);
        }
    } while (player_startDie == computer_startDie); /*To eliminate the draw condition*/
    for (counter = 0; counter < num_round; counter++)
    {
        if (player_startDie > computer_startDie)
        {
            player_sum += play_user();
            computer_sum += play_computer();
        }
        else
        {
            computer_sum += play_computer();
            player_sum += play_user();
        }
    }
    if (counter == num_round)
    {
        scoresheet(computer_sum, player_sum);
    }
    return 0;
}
/*Functions that I used to build the game*/
int roll_a_dice()
{
    return rand() % 6 + 1;
}
int play_user()
{
    int dice1, dice2, dice3, dice4, dice5, dice6;
    char player_answer, reroll;
    int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;
    int cumulative_sum = 0, valid = 1, line;
    static player_score = 0;
    int zonk = 0;
    dice1 = roll_a_dice();
    dice2 = roll_a_dice();
    dice3 = roll_a_dice();
    dice4 = roll_a_dice();
    dice5 = roll_a_dice();
    dice6 = roll_a_dice();
    printf("\n\nYour Turn:\n");
    for (line = 0; line < 40; line++)
    {
        printf("=");
    }
    printf("\n");
    printf("You got --> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d [Dice 6]: %d\n", dice1, dice2,
           dice3, dice4, dice5, dice6);
    if ((isConsecutive(dice1, dice2, dice3, dice4, dice5, dice6) == 0) &&
        (isAllSame(dice1, dice2, dice3, dice4, dice5, dice6) == 0) &&
        (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 0) &&
        (isOnes(dice1, dice2, dice3, dice4, dice5, dice6) == 0) &&
        (isFives(dice1, dice2, dice3, dice4, dice5, dice6) == 0))
    {
        zonk = 1; /*ZONK*/
        player_score = 0;
    }
    if (zonk != 1)
    {
        do
        {
            printf("Do you want to continue (Y/N)? ");
            scanf(" %c", &player_answer);
            while (player_answer != 'Y' && player_answer != 'y' && player_answer != 'N' &&
                   player_answer != 'n') /*Error check*/
            {
                printf("You entered a wrong option.Please try again!\n");
                printf("Do you want to continue (Y/N)? ");
                scanf(" %c", &player_answer);
            }
            if (player_answer == 'N' || player_answer == 'n')
            {
                if (isConsecutive(dice1, dice2, dice3, dice4, dice5, dice6) == 1) /*Checking strategies*/
                {
                    player_score += 1500;
                }
                else if (isAllSame(dice1, dice2, dice3, dice4, dice5, dice6) == 1)
                {
                    player_score += 1000;
                }
                else
                {
                    if (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 1)
                    {
                        player_score += 1000;
                    }
                    if ((isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 2) ||
                        (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 3) ||
                        (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 4) ||
                        (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 5) ||
                        (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 6))
                    {
                        player_score += (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6)) * 100;
                    }
                    if (isOnes(dice1, dice2, dice3, dice4, dice5, dice6) != 0)
                    {
                        player_score += isOnes(dice1, dice2, dice3, dice4, dice5, dice6) * 100;
                    }
                    if (isFives(dice1, dice2, dice3, dice4, dice5, dice6) != 0)
                    {
                        player_score += isFives(dice1, dice2, dice3, dice4, dice5, dice6) * 50;
                    }
                }
            }
            if (player_answer == 'Y' || player_answer == 'y')
            {
                printf("Which ones you want to roll again? ");
                scanf(" %c", &reroll); /*I need to keep one of the dices*/
                while (reroll != 10)
                {
                    if ((reroll - '0') == 1)
                    {
                        d1 = 1;
                        cumulative_sum += d1; /*Error check - to avoid to be entered more than 5 dices*/
                    }
                    else if ((reroll - '0') == 2)
                    {
                        d2 = 2;
                        cumulative_sum += d2;
                    }
                    else if ((reroll - '0') == 3)
                    {
                        d3 = 3;
                        cumulative_sum += d3;
                    }
                    else if ((reroll - '0') == 4)
                    {
                        d4 = 4;
                        cumulative_sum += d4;
                    }
                    else if ((reroll - '0') == 5)
                    {
                        d5 = 5;
                        cumulative_sum += d5;
                    }
                    else if ((reroll - '0') == 6)
                    {
                        d6 = 6;
                        cumulative_sum += d6;
                    }
                    else if ((reroll - '0') == 7)
                    {
                        cumulative_sum += 7;
                    }
                    else if ((reroll - '0') == 8)
                    {
                        cumulative_sum += 8;
                    }
                    else if ((reroll - '0') == 9)
                    {
                        cumulative_sum += 9;
                    }
                    scanf("%c", &reroll);
                }
                if (cumulative_sum >= 21)
                {
                    valid = 0;
                    printf("You need to keep at least 1 dice.");
                }
                if (valid == 1)
                {
                    printf("Kept Dice ");
                    if (d1 == 0)
                    {
                        printf("1 ");
                    }
                    if (d2 == 0)
                    {
                        printf("2 ");
                    }
                    if (d3 == 0)
                    {
                        printf("3 ");
                    }
                    if (d4 == 0)
                    {
                        printf("4 ");
                    }
                    if (d5 == 0)
                    {
                        printf("5 ");
                    }
                    if (d6 == 0)
                    {
                        printf("6 ");
                    }
                    printf("and rolled ");
                    if (d1 != 0)
                    {
                        printf("1 ");
                    }
                    if (d2 != 0)
                    {
                        printf("2 ");
                    }
                    if (d3 != 0)
                    {
                        printf("3 ");
                    }
                    if (d4 != 0)
                    {
                        printf("4 ");
                    }
                    if (d5 != 0)
                    {
                        printf("5 ");
                    }
                    if (d6 != 0)
                    {
                        printf("6 ");
                    }
                    printf("\nYou got -->");
                    if (d1 != 0)
                    {
                        dice1 = roll_a_dice();
                        if (dice1 != 1 && dice1 != 5)
                        {
                            player_score = 0;
                            zonk = 1; /*ZONK*/
                        }
                        printf("[Dice 1]: %d ", dice1);
                    }
                    if (d2 != 0)
                    {
                        dice2 = roll_a_dice();
                        if (dice2 != 1 && dice2 != 5)
                        {
                            player_score = 0;
                            zonk = 1;
                        }
                        printf("[Dice 2]: %d ", dice2);
                    }
                    if (d3 != 0)
                    {
                        dice3 = roll_a_dice();
                        if (dice3 != 1 && dice3 != 5)
                        {
                            player_score = 0;
                            zonk = 1;
                        }
                        printf("[Dice 3]: %d ", dice3);
                    }
                    if (d4 != 0)
                    {
                        dice4 = roll_a_dice();
                        if (dice4 != 1 && dice4 != 5)
                        {
                            player_score = 0;
                            zonk = 1;
                        }
                        printf("[Dice 4]: %d ", dice4);
                    }
                    if (d5 != 0)
                    {
                        dice5 = roll_a_dice();
                        if (dice5 != 1 && dice5 != 5)
                        {
                            player_score = 0;
                            zonk = 1;
                        }
                        printf("[Dice 5]: %d ", dice5);
                    }
                    if (d6 != 0)
                    {
                        dice6 = roll_a_dice();
                        if (dice6 != 1 && dice6 != 5)
                        {
                            player_score = 0; /*To avoid the unnecessary adding*/
                            zonk = 1;
                        }
                        printf("[Dice 6]: %d ", dice6);
                    }
                    cumulative_sum = 0; /*To reset the conditions in the loop*/
                    printf("\n");
                }
            }
        } while (player_answer == 'Y' || player_answer == 'y');
    }
    if (zonk == 1)
    {
        player_score = 0;
        printf("ZONK!!!Your Score: Z\n\n");
    }
    if (player_answer == 'N' || player_answer == 'n')
    {
        printf("Your Score: %d\n\n", player_score);
    }
    return player_score;
}

int play_computer()
{
    int dice1, dice2, dice3, dice4, dice5, dice6;
    int reroll = 0, line;
    int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;
    static computer_score = 0;
    int zonk = 0;
    dice1 = roll_a_dice(); /*Rolling dices*/
    dice2 = roll_a_dice();
    dice3 = roll_a_dice();
    dice4 = roll_a_dice();
    dice5 = roll_a_dice();
    dice6 = roll_a_dice();
    printf("\nMy Turn:\n");
    for (line = 0; line < 40; line++)
    {
        printf("=");
    }
    printf("\n");
    printf("I got --> [Dice 1]: %d [Dice 2]: %d [Dice 3]: %d [Dice 4]: %d [Dice 5]: %d [Dice 6]: %d\n", dice1, dice2,
           dice3, dice4, dice5, dice6);
    if ((isConsecutive(dice1, dice2, dice3, dice4, dice5, dice6) == 0) &&
        (isAllSame(dice1, dice2, dice3, dice4, dice5, dice6) == 0) &&
        (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 0) &&
        (isOnes(dice1, dice2, dice3, dice4, dice5, dice6) == 0) &&
        (isFives(dice1, dice2, dice3, dice4, dice5, dice6) == 0))
    {
        zonk = 1; /*ZONK*/
    }
    else
    {
        if (isConsecutive(dice1, dice2, dice3, dice4, dice5, dice6) == 1) /*To calculate the computer_score*/
        {
            computer_score += 1500;
        }
        else
        {
            if (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 1)
            {
                computer_score += 1000;
            }
            if ((isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 2) ||
                (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 3) ||
                (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 4) ||
                (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 5) ||
                (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6) == 6))
            {
                computer_score += (isThreeOfaKind(dice1, dice2, dice3, dice4, dice5, dice6)) * 100;
            }
        }
        if ((isOnes(dice1, dice2, dice3, dice4, dice5, dice6)) != 0)
        {
            computer_score += isOnes(dice1, dice2, dice3, dice4, dice5, dice6) * 100;
        }
        if (isFives(dice1, dice2, dice3, dice4, dice5, dice6) != 0)
        {
            computer_score += isFives(dice1, dice2, dice3, dice4, dice5, dice6) * 50;
        }
    }
    if (zonk == 1)
    {
        computer_score = 0;
        printf("ZONK!!!My Score: Z\n\n");
    }
    else if (computer_score < 350)
    {
        if (computer_strategy_decider(dice1, dice2, dice3, dice4, dice5, dice6) == 0)
        {
            computer_score = 0;
            printf("ZONK!!!My Score: Z\n\n");
        }
        else
        {
            computer_score += computer_strategy_decider(dice1, dice2, dice3, dice4, dice5, dice6);
            printf("My Score: %d\n\n", computer_score);
        }
    }
    else if (computer_score >= 350)
    {
        printf("My Score: %d\n\n", computer_score);
    }
    return computer_score;
}

int computer_strategy_decider(int a, int b, int c, int d, int e, int f)
{
    int computer_score = 0;
    int kept = 0, kept1 = 0, kept2 = 0, kept3 = 0, kept4 = 0, kept5 = 0, kept6 = 0;
    printf("Kept Dice ");
    if ((isConsecutive(a, 0, 0, 0, 0, 0) != 0) || (isAllSame(a, 0, 0, 0, 0, 0) != 0) ||
        (isThreeOfaKind(a, 0, 0, 0, 0, 0) != 0) || (isOnes(a, 0, 0, 0, 0, 0) != 0) ||
        (isFives(a, 0, 0, 0, 0, 0) != 0)) /*To check whether there is a plus point or not.If there is a plus point,
                                             computer should keep it instead of rolling*/
    {
        printf("1 ");
        kept1 = 1;
    }
    if ((isConsecutive(0, b, 0, 0, 0, 0) != 0) || (isAllSame(0, b, 0, 0, 0, 0) != 0) ||
        (isThreeOfaKind(0, b, 0, 0, 0, 0) != 0) || (isOnes(0, b, 0, 0, 0, 0) != 0) || (isFives(0, b, 0, 0, 0, 0) != 0))
    {
        printf("2 ");
        kept2 = 1;
    }
    if ((isConsecutive(0, 0, c, 0, 0, 0) != 0) || (isAllSame(0, 0, c, 0, 0, 0) != 0) ||
        (isThreeOfaKind(0, 0, c, 0, 0, 0) != 0) || (isOnes(0, 0, c, 0, 0, 0) != 0) || (isFives(0, 0, c, 0, 0, 0) != 0))
    {
        printf("3 ");
        kept3 = 1;
    }
    if ((isConsecutive(0, 0, 0, d, 0, 0) != 0) || (isAllSame(0, 0, 0, d, 0, 0) != 0) ||
        (isThreeOfaKind(0, 0, 0, d, 0, 0) != 0) || (isOnes(0, 0, 0, d, 0, 0) != 0) || (isFives(0, 0, 0, d, 0, 0) != 0))
    {
        printf("4 ");
        kept4 = 1;
    }
    if ((isConsecutive(0, 0, 0, 0, e, 0) != 0) || (isAllSame(0, 0, 0, 0, e, 0) != 0) ||
        (isThreeOfaKind(0, 0, 0, 0, e, 0) != 0) || (isOnes(0, 0, 0, 0, e, 0) != 0) || (isFives(0, 0, 0, 0, e, 0) != 0))
    {
        printf("5 ");
        kept5 = 1;
    }
    if ((isConsecutive(0, 0, 0, 0, 0, f) != 0) || (isAllSame(0, 0, 0, 0, 0, f) != 0) ||
        (isThreeOfaKind(0, 0, 0, 0, 0, f) != 0) || (isOnes(0, 0, 0, 0, 0, f) != 0) || (isFives(0, 0, 0, 0, 0, f) != 0))
    {
        printf("6 ");
        kept6 = 1;
    }
    printf("and rolled ");
    if (kept1 == 0)
    {
        printf("1 ");
    }
    if (kept2 == 0)
    {
        printf("2 ");
    }
    if (kept3 == 0)
    {
        printf("3 ");
    }
    if (kept4 == 0)
    {
        printf("4 ");
    }
    if (kept5 == 0)
    {
        printf("5 ");
    }
    if (kept6 == 0)
    {
        printf("6 ");
    }
    printf("\nI got -->");
    if (kept1 == 0) /*Rolling the dices that are not kept*/
    {
        a = roll_a_dice();
        if (a == 1)
            computer_score += 100;
        else if (a == 5)
            computer_score += 50;
        else
            computer_score = 0;
        printf("[Dice 1]: %d ", a);
    }
    if (kept2 == 0)
    {
        b = roll_a_dice();
        if (b == 1)
            computer_score += 100;
        else if (b == 5)
            computer_score += 50;
        else
            computer_score = 0;
        printf("[Dice 2]: %d ", b);
    }
    if (kept3 == 0)
    {
        c = roll_a_dice();
        if (c == 1)
            computer_score += 100;
        else if (c == 5)
            computer_score += 50;
        else
            computer_score = 0;
        computer_score += 50;
        printf("[Dice 3]: %d ", c);
    }
    if (kept4 == 0)
    {
        d = roll_a_dice();
        if (d == 1)
            computer_score += 100;
        else if (d == 5)
            computer_score += 50;
        else
            computer_score = 0;
        printf("[Dice 4]: %d ", d);
    }
    if (kept5 == 0)
    {
        e = roll_a_dice();
        if (e == 1)
            computer_score += 100;
        else if (e == 5)
            computer_score += 50;
        else
            computer_score = 0;
        printf("[Dice 5]: %d ", e);
    }
    if (kept6 == 0)
    {
        f = roll_a_dice();
        if (f == 1)
            computer_score += 100;
        else if (f == 5)
            computer_score += 50;
        else
            computer_score = 0;
        printf("[Dice 6]: %d ", f);
    }
    printf("\n");
    return computer_score;
}

/*Strategies*/
int isConsecutive(int a, int b, int c, int d, int e, int f)
{
    int i = 0;
    int count = 0;
    for (i = 1; i <= 6; i++)
    {
        if (a == i)
        {
            count++;
            continue;
        }
        if (b == i)
        {
            count++;
            continue;
        }
        if (c == i)
        {
            count++;
            continue;
        }
        if (d == i)
        {
            count++;
            continue;
        }
        if (e == i)
        {
            count++;
            continue;
        }
        if (f == i)
        {
            count++;
            continue;
        }
    }
    if (count == 6)
    {
        return 1; /*Consecutive*/
    }
    else
    {
        return 0; /*Not Consecutive*/
    }
}

int isAllSame(int a, int b, int c, int d, int e, int f)
{
    if (a == b && b == c && c == d && d == e && e == f)
    {
        return 1; /*All are the same*/
    }
    else
    {
        return 0; /*All are not the same*/
    }
}

int isThreeOfaKind(int a, int b, int c, int d, int e, int f)
{
    int i, count, threes = 0;
    for (i = 1; i <= 6; i++)
    {
        count = 0;
        if (a == i)
        {
            count++;
        }
        if (b == i)
        {
            count++;
        }
        if (c == i)
        {
            count++;
        }
        if (d == i)
        {
            count++;
        }
        if (e == i)
        {
            count++;
        }
        if (f == i)
        {
            count++;
        }
        if (count >= 3)
        {
            threes = 1;
            return i; /*ThreeOfaKind*/
        }
    }
    if (threes == 0)
    {
        return 0; /*Not ThreeOfaKind*/
    }
}

int isOnes(int a, int b, int c, int d, int e, int f)
{
    int count = 0;
    if (a == 1)
    {
        count++;
    }
    if (b == 1)
    {
        count++;
    }
    if (c == 1)
    {
        count++;
    }
    if (d == 1)
    {
        count++;
    }
    if (e == 1)
    {
        count++;
    }
    if (f == 1)
    {
        count++;
    }
    if (count == 0)
    {
        return 0;
    }
    if (count >= 3)
    {
        count -= 3;
        return count; /*To count the number of ones except from the ones that are three of a kind*/
    }
    else
    {
        return count;
    }
}

int isFives(int a, int b, int c, int d, int e, int f)
{
    int count = 0;
    if (a == 5)
    {
        count++;
    }
    if (b == 5)
    {
        count++;
    }
    if (c == 5)
    {
        count++;
    }
    if (d == 5)
    {
        count++;
    }
    if (e == 5)
    {
        count++;
    }
    if (f == 5)
    {
        count++;
    }
    if (count == 0)
    {
        return 0;
    }
    if (count >= 3)
    {
        count -= 3;
        return count; /*To count the number of fives except from the fives that are three of a kind*/
    }
    else
    {
        return count;
    }
}

void scoresheet(int computer_sum, int player_sum)
{
    int line;
    printf("\n\n\nOur scoresheet:\n");
    for (line = 0; line < 40; line++)
    {
        printf("=");
    }
    printf("\n");
    if (computer_sum == 0) /*Zonk Condition for Computer*/
    {
        printf("My score\t\tYour score\n");
        printf("Z\t\t\t%d\n\n\n", player_sum);
    }
    else if (player_sum == 0) /*Zonk Condition for Player*/
    {
        printf("My score\t\tYour score\n");
        printf("%d\t\t\tZ\n\n\n", computer_sum);
    }
    else if (player_sum == 0 && computer_sum == 0) /*Zonk Condition for Both Computer&Player*/
    {
        printf("My score\t\tYour score\n");
        printf("Z\t\t\tZ\n\n\n");
    }
    else
    {
        printf("My score\t\tYour score\n");
        printf("%d\t\t\t%d\n\n\n", computer_sum, player_sum);
    }
}
