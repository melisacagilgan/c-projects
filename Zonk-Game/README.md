# Zonk-Game

## Purpose
The main purpose of this programming assignment is to revise the topics that we have covered in the first six weeks including fundamentals of C programming, conditional statements, repetitive statements, and functions.

## Description
You will write a program for playing a simplified version of the Zonk game between a player and computer. Zonk is a dice game which was introduced in 1970s. This will give you practice with all three control constructs (sequence, selection and repetition). We are including some design constraints in the "programming task" section, so you will also use functions. This will give you the experience of decomposing a problem into parts, and then implementing each part in one highly cohesive, loosely coupled function. Don't try to compile your entire program in one "big bang". Compile it piece by piece. Test each piece that you have compiled to make sure it works correctly before you add the next piece.

## Rules
**Equipment:** 6 dices and a scoresheet

**Number of Players:** 2 players

**How to play:** At the beginning to decide who is going to start the game, each player rolls one die. Highest roll goes first and play proceeds with the other player. The first player rolls all six
dice to start his turn. Certain number combinations are worth game points. The player must play at least one scoring combination each time he rolls by setting the scoring die (or dice) to
the side. He then picks up the remaining dice and rolls them. Again, at least one scoring combination must be played and set aside, and the remaining dice rolled. This sequence
continues until the player can stop and keep his points for the turn, or zonks.

**Zonking:** If, after any roll (the number of die or dice depends on users decision), no scoring combinations turn up, the player zonks and his turn ends. He scores no points for the turn

**Keeping Points:** A player may stop his turn and keep all points accumulated during the roll if the following condition is met: The player has at least 350 points in this turn. Otherwise the player has to roll again.

**Scoring:** The following dice combinations are worth points:
1. Each 5 is worth 50 points.
2. Each 1 worth 100 points.
3. Any three-of-a-kind rolled at once is worth 100x the face value of a single die. (e.g. three two's are worth 200, three three’s are worth 300, three four’s are worth 400, three five’s are worth 500 and three six’s are worth 600), apart from three one’s which worth
1000 (Note: they don’t have to be consecutive).
4. Six of a kind (e.g. 4 4 4 4 4 4 , 5,5,5,5,5,5,,…) are worth 1000 points.
5. A straight (1,2,3,4,5,6) is worth 1500 points (they do not need to be in that order, for example, it could be 3, 2, 1, 6, 5, 4).

When dices are rolled, only one of the above can be used for scoring. Depending on the number of dices kept, one of the strategies will be for scoring. For example, if the user rolls “1 1 1 1 1 1” and they decide to keep 1 of those, and roll again the rest, they will get 100 points. If they decide to keep 3 of those and roll again the other three, they will get 1000 points. If they decide to keep all, then they will get 1000 points. Please see “computer_strategy_decider” function definition below for how computer will decide which strategy to use.

## How to play Zonk?
You will write the program that will allow a player play the Zonk game against the computer. Your program will allow the players play the game for as many rounds as they specify at the beginning of the game and who ever has the highest score at the end, will win the game. Your game will start with rolling the dice for the computer player and then asking the other player if they are ready to play.
