// PROJECT BY
//   AYUSH GATLA
//  T RAM SAI
//   PANKAJ MAULEKHI
//  ABHILASH KUMAR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

#define RED "\033[31m"    // Red text
#define GREEN "\033[32m"  // Green text
#define RESET "\033[0m"   // Reset to default color
#define YELLOW "\033[33m" // Yellow text
#define BLUE "\033[34m"   // Blue text
#define CYAN "\033[35m"   // Cyan text

int roll;
int snakeHead[] = {99, 90, 30, 35, 60};   // snake heads
int snakeTail[] = {77, 68, 10, 3, 38};    // snake tails
int ladderBottom[] = {73, 62, 46, 50, 5}; // ladder bottoms
int ladderTop[] = {95, 80, 64, 52, 27};   // ladder tops
int snake_len = 5;                        // number of snakes
int ladder_len = 5;                       // number of ladders
char a = '\0';                            // to print blank spaces

void drawDice(int num); // for the Dice animation
void clearScreen();
void animation();                                                                                // function to print the loading screen animation
void store(char arr[10][10]);                                                                    // initializes the array arr, from 1-100 in alternate pattern
void horizontal(char arr[10][10], int j, int player1Pos, int player2Pos);                        // receiving arr,row number, positions of p1 and p2
void alternatepatternfornumbers(char arr[10][10], int j, int k, int player1Pos, int player2Pos); // to print the numbers,players,snakes and ladders in the board
void printnum(int i, int j, int u, char arr[10][10], int player1Pos, int player2Pos);
void hori(int i, int j);                                      // to print pattern in board
void start();                                                 // Function to display the start menu with options
void welcome(int num, int j);                                 // function for animated loading screen
int rollDice();                                               // picks a random number for a dice from 1-6
int checkPosition(int position);                              // to update the current postion after encountering a snake or a ladder
void board(char arr[10][10], int player1Pos, int player2Pos); // function call the respective other function required to display the board,along with updated player positions
int rollDiceAnimation();                                      // animation for dice
void playGame(char arr[10][10]);                              // logic of the game
void rules();                                                 // display rules

// MAIN FUNCTION
int main()
{
    animation();
again:
    clearScreen();
    start();
    int o;
    printf("%68c", a);

    scanf("%d", &o);
    getchar();
    clearScreen();
    char arr[10][10];

    store(arr);
    srand(time(0));
    if (o == 1)
    {
        playGame(arr);
    }
    else if (o == 2)
    {
        rules();
        printf(RESET "\nEnter 4 to go to the main menu or 5 to end :\n");
        scanf("%d", &o);

        if (o == 4)
        {
            goto again;
        }
    }
    else if (o == 3)
    {
        printf(RED "Game Quitted" RESET);
    }
    else
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n%58c", a);

        printf(RED "Invalid Input Please [ENTER] To Try Again" RESET);
        getchar();
        goto again;
    }
}

// function for the Dice animation
void drawDice(int num)
{
    clearScreen(); // function to clear the screen
    printf("Rolling Dice...\n\n");

    switch (num)
    {
    case 1:
        printf(" ------- \n");
        printf("|       |\n");
        printf("|   *   |\n");
        printf("|       |\n");
        printf(" ------- \n");
        break;
    case 2:
        printf(" ------- \n");
        printf("| *     |\n");
        printf("|       |\n");
        printf("|     * |\n");
        printf(" ------- \n");
        break;
    case 3:
        printf(" ------- \n");
        printf("| *     |\n");
        printf("|   *   |\n");
        printf("|     * |\n");
        printf(" ------- \n");
        break;
    case 4:
        printf(" ------- \n");
        printf("| *   * |\n");
        printf("|       |\n");
        printf("| *   * |\n");
        printf(" ------- \n");
        break;
    case 5:
        printf(" ------- \n");
        printf("| *   * |\n");
        printf("|   *   |\n");
        printf("| *   * |\n");
        printf(" ------- \n");
        break;
    case 6:
        printf(" ------- \n");
        printf("| *   * |\n");
        printf("| *   * |\n");
        printf("| *   * |\n");
        printf(" ------- \n");
        break;
    }
    Sleep(100); // small delay
}

// function to display rules
void rules()
{
    printf(BLUE "RULES :\n\n");
    printf(GREEN " Players take turns rolling a die and moving their counter forward the number of spaces shown on the dice\n\n");
    printf(YELLOW " If a player lands on the bottom of a ladder, they can move up to the top. \n\n");
    printf(GREEN " If a player lands on the head of a snake, they must slide down to the bottom of the snake\n\n");
    printf(YELLOW " The first player to land on square 100 wins\n\n");
    printf(GREEN " If a player rolls a 6, they get an extra roll \n\n");
    printf(YELLOW " There is no limitations for the number of time 6 rolled\n\n");
}

// function for logic for game
void playGame(char arr[10][10])
{
    int player1Pos = 0, player2Pos = 0; // initial players positions
    int diceRoll;
    int currentPlayer = 1;
    int startRolling = 0; // To check if the player has started the game

    while (player1Pos < 100 && player2Pos < 100)
    {
        board(arr, player1Pos, player2Pos);

        if (currentPlayer == 1)
        {
            printf("\nPlayer 1's turn.\n");
            while (1) // Loop until the player rolls a valid start
            {
                printf("Press Enter to roll the dice...");
                getchar();

                diceRoll = rollDice();
                rollDiceAnimation();

                drawDice(diceRoll);
                // printf("Press Enter to continue...\n ");
                printf("\nPlayer 1 rolled a %d!\n", diceRoll);
                getchar();
                clearScreen();
                if (diceRoll == 6 && !startRolling) // Start game on rolling 6
                {
                    startRolling = 1; // Set flag to indicate game has started
                    player1Pos += diceRoll;
                    printf("Player 1's new position: %d\n", player1Pos);
                    break; // Exit loop after valid move
                }
                else if (diceRoll == 6 && startRolling) // Extra turn on rolling 6
                {
                    player1Pos += diceRoll; // Move player
                    if (player1Pos > 100)
                    {
                        player1Pos -= diceRoll; // Don't move if it exceeds 100
                        printf("Player 1 cannot move past 100 and stays at position: %d\n", player1Pos);
                    }
                    else
                        printf("Player 1's new position: %d\n", player1Pos);
                    printf("Player 1 rolled a 6! Roll again.\n");
                }
                else
                {
                    if (startRolling)
                    {
                        player1Pos += diceRoll; // Move player
                        if (player1Pos > 100)
                        {
                            player1Pos -= diceRoll; // Don't move if it exceeds 100
                            printf("Player 1 cannot move past 100 and stays at position: %d\n", player1Pos);
                        }
                        else
                            printf("Player 1's new position: %d\n", player1Pos);
                    }
                    else
                    {
                        printf("Player 1 must roll a 6 to start!\n");
                    }
                    break; // Exit loop after valid move
                }
            }

            player1Pos = checkPosition(player1Pos);
            if (player1Pos == 100)
            {
                printf(GREEN "Congratulations! Player 1 reached 100 and won the game!\n" RESET);
                break;
            }

            currentPlayer = 2; // Switch to Player 2
        }
        else
        {
            printf("\nPlayer 2's turn.\n");
            while (1) // Loop until the player rolls a valid start
            {
                printf("Press Enter to roll the dice...");
                getchar();

                diceRoll = rollDice();
                rollDiceAnimation();
                drawDice(diceRoll);
                printf("\nPlayer 2 rolled a %d!\n", diceRoll);
                // printf("Press Enter to continue...\n ");
                getchar();
                clearScreen();
                if (diceRoll == 6 && !startRolling) // Start game on rolling 6
                {
                    startRolling = 1; // Set flag to indicate game has started
                    player2Pos += diceRoll;
                    printf("Player 2's new position: %d\n", player2Pos);
                    break; // Exit loop after valid move
                }
                else if (diceRoll == 6 && startRolling) // Extra turn on rolling 6
                {
                    player2Pos += diceRoll; // Move player
                    if (player2Pos > 100)
                    {
                        player2Pos -= diceRoll; // Don't move if it exceeds 100
                        printf("Player 2 cannot move past 100 and stays at position: %d\n", player2Pos);
                    }
                    else
                        printf("Player 2's new position: %d\n", player2Pos);
                    printf("Player 2 rolled a 6! Roll again.\n");
                }
                else
                {
                    if (startRolling)
                    {
                        player2Pos += diceRoll; // Move player
                        if (player2Pos > 100)
                        {
                            player2Pos -= diceRoll; // Don't move if it exceeds 100
                            printf("Player 2 cannot move past 100 and stays at position: %d\n", player2Pos);
                        }
                        else
                            printf("Player 2's new position: %d\n", player2Pos);
                    }
                    else
                    {
                        printf("Player 2 must roll a 6 to start!\n");
                    }

                    break; // Exit loop after valid move
                }
            }

            player2Pos = checkPosition(player2Pos);
            if (player2Pos == 100)
            {
                printf(GREEN "Congratulations! Player 2 reached 100 and won the game!\n" RESET);
                break;
            }

            currentPlayer = 1; // Switch to Player 1
        }
    }
}

// animation for dice
int rollDiceAnimation()
{
    int diceRoll;
    for (int i = 0; i < 10; i++)
    {                                // Loop to create rolling effect
        diceRoll = (rand() % 6) + 1; // generated a random number between 1-6
        clearScreen();
        drawDice(diceRoll); // Display random dice face
        Sleep(50);          // Delay in microseconds (100ms)
    }
    return diceRoll; // return the rolled dice value
}

// to update the current postion after encountering a snake or a ladder
int checkPosition(int position)
{
    for (int i = 0; i < snake_len; i++)
    {
        if (snakeHead[i] == position) // condition to check for a snake head
        {
            printf(RED "Oh no! Snake at %d, sliding down to %d.\n" RESET, position, snakeTail[i]);
            return snakeTail[i]; // return the snake tail postion
        }
    }
    for (int i = 0; i < ladder_len; i++)
    {
        if (ladderBottom[i] == position) // condition to check for a ladder bottom
        {
            printf(GREEN "Great! Ladder at %d, climbing up to %d.\n" RESET, position, ladderTop[i]);
            return ladderTop[i]; // return the ladder bottom postion
        }
    }
    return position; // returning original position if above conditions doesn't satisfies
}

// function call the respective other function required to display the board,along with updated player positions
void board(char arr[10][10], int player1Pos, int player2Pos)
{
    for (int j = 0; j < 10; j++)
    {
        printf(RESET "");                           // resets the colour to default in terminal
        horizontal(arr, j, player1Pos, player2Pos); // passes the arr, row number,p1 and p2 postion
        printf("\n" RESET);                         // resets the colour to default in terminal
    }
}

// picks a random number for a dice from 1-6
int rollDice()
{
    return (rand() % 6) + 1;
}

// function to clear screen
void clearScreen()
{
    printf("\033[H\033[J"); // code to clear the screen
}

// function for animated loading screen
void welcome(int num, int j)
{
    clearScreen(); // calling function to clear screen

    switch (num)
    {
    case 1:
        printf("\n\n\n\n"); // for next line
        printf("%53c", a);  // for blank spaces
        printf(RED "WELCOME " RESET);
        printf(GREEN "TO " RESET);
        printf(YELLOW "SNAKES " RESET);
        printf(BLUE "AND " RESET);
        printf(CYAN "LADDERS " RESET);
        printf("\n\n");

        if (j != 20) // condition to loading prompt after animation
        {
            printf("%63c", a);
            printf("Loading");
        }
        break;
    case 2:
        printf("\n\n\n\n");
        printf("%53c", a); // for blank spaces
        printf(CYAN "WELCOME " RESET);
        printf(RED "TO " RESET);
        printf(GREEN "SNAKES " RESET);
        printf(YELLOW "AND " RESET);
        printf(BLUE "LADDERS " RESET);
        printf("\n\n");

        if (j != 20) // condition to loading prompt after animation
        {
            printf("%63c", a); // for blank spaces
            printf("Loading .");
        }
        break;
    case 3:
        printf("\n\n\n\n");
        printf("%53c", a); // for blank spaces
        printf(BLUE "WELCOME " RESET);
        printf(CYAN "TO " RESET);
        printf(RED "SNAKES " RESET);
        printf(GREEN "AND " RESET);
        printf(YELLOW "LADDERS " RESET);
        printf("\n\n");

        if (j != 20) // condition to loading prompt after animation
        {
            printf("%63c", a); // for blank spaces
            printf("Loading . .");
        }
        break;
    case 4:
        printf("\n\n\n\n");
        printf("%53c", a); // for blank spaces
        printf(YELLOW "WELCOME " RESET);
        printf(BLUE "TO " RESET);
        printf(CYAN "SNAKES " RESET);
        printf(RED "AND " RESET);
        printf(GREEN "LADDERS " RESET);
        printf("\n\n");

        if (j != 20) // condition to loading prompt after animation
        {
            printf("%63c", a); // for blank spaces
            printf("Loading . . .");
        }
        break;
    case 5:
        printf("\n\n\n\n");
        printf("%53c", a); // for blank spaces
        printf(GREEN "WELCOME " RESET);
        printf(YELLOW "TO " RESET);
        printf(BLUE "SNAKES " RESET);
        printf(CYAN "AND " RESET);
        printf(RED "LADDERS " RESET);
        printf("\n\n");

        if (j != 20) // condition to loading prompt after animation
        {

            printf("%63c", a); // for blank spaces

            printf("Loading . . . .");
        }
        break;
    }
    printf("\n\n");
    printf("%74c", a); // for blank spaces
}

// function to print the loading screen animation
void animation()
{
    srand(time(0)); // Seed random number generator
    int ani;
    for (int i = 1; i <= 20; i++)
    {
        ani = i % 5;     // repeating 5 color patterns
        welcome(ani, i); // Calling welcome function with loading animation
        Sleep(150);      // Small delay
    }
    clearScreen();
    printf("\n\n\n\n");
    printf("\033[38;5;202m%53cWELCOME TO SNAKES AND LADDERS\033[1m" RESET, a);
    printf("\n\n\n");
    printf("%61c", a);
    printf("Press [ENTER]");
    getchar(); // Wait for Enter key
}

// Function to display the start menu with options
void start()
{
    printf("\n\n\n\n"); // starting down spaces

    printf("%40c", a); // blank spaces
    for (int i = 0; i < 6; i++)
    {
        printf(BLUE "---------"); // Top border of menu
    }
    printf("\n");

    for (int i = 0; i < 8; i++)
    {

        printf("%40c", a);

        if (i == 0) // Menu title
        {
            printf(BLUE "|");

            printf("%11c", a);

            printf(BLUE "       SNAKES AND LADDERS        ");

            printf("%10c", a);

            printf("|\n");
        }
        else if (i == 2) // Start game option
        {
            printf(GREEN "|");
            printf(GREEN "     Start Game [ENTER 1]");
            printf("%28c", a);
            printf("|\n");
        }
        else if (i == 4) // Rules option
        {
            printf(YELLOW "|");
            printf(YELLOW "     Rules [ENTER 2]");
            printf("%33c", a);
            printf("|\n");
        }
        else if (i == 6) // Exit option
        {
            printf(RED "|");
            printf(RED "     Exit [ENTER 3]" RESET);
            printf("%34c", a);
            printf(RED "|\n");
        }
        else // Empty rows for spacing
        {
            printf("|");
            printf("%53c", a);
            printf("|\n");
        }
    }
    printf("%40c", a);           // blank spaces
    for (int i = 0; i < 54; i++) // Bottom border of menu
    {
        printf("-");
    }
    printf("\n");
}

// to print the top and bottom spaces in the board so it would seem like a square
void hori(int i, int j)
{
    if ((i + j) % 2 == 0) // for first colour sequence in the boxes
    {
        printf("\033[48;5;19m        \033[1m");
        printf(RESET "");
    }
    else // for alternate colour sequence in the boxes
    {
        printf("\033[48;5;21m        \033[1m");
        printf(RESET "");
    }
}

// functions to print numbers, snakes, ladders with colors
void printnum(int i, int j, int u, char arr[10][10], int player1Pos, int player2Pos)
{

    if (u == 1)
    {
        int pos = arr[i][j];
        if (pos == player1Pos && pos == player2Pos)
        {
            printf("\033[48;5;19m  \033[3m");
            printf("\033[38;5;7;48;5;40mP1\033[3m");
            printf("\033[38;5;7;48;5;214mP2\033[3m");
            printf("\033[48;5;19m  \033[3m" RESET);
        }
        else if (pos == player1Pos)
        {
            printf("\033[48;5;19m  \033[3m");
            printf("\033[38;5;7;48;5;40m P1 \033[3m");
            printf("\033[48;5;19m  \033[3m" RESET);
        }
        else if (pos == player2Pos)
        {
            printf("\033[48;5;19m  \033[3m");
            printf("\033[38;5;7;48;5;214m P2 \033[3m");
            printf("\033[48;5;19m  \033[3m" RESET);
        }
        else if ((i == 0 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 3) ||

                 (i == 4 && j == 0) || (i == 5 && j == 1) || (i == 6 && j == 2) ||
                 (i == 9 && j == 2) || (i == 8 && j == 3) || (i == 7 && j == 4) || (i == 6 && j == 5) ||
                 (i == 7 && j == 9) || (i == 8 && j == 9) || (i == 9 && j == 9) ||
                 (i == 3 && j == 7) || (i == 2 && j == 8) || (i == 1 && j == 9))
        {

            printf("\033[38;5;196;48;5;19m  %4d  \033[1m", arr[i][j]);
            printf(RESET "");
        }
        else if ((i == 2 && j == 0) || (i == 3 && j == 1) ||
                 (i == 3 && j == 3) || (i == 4 && j == 4) || (i == 5 && j == 5) ||
                 (i == 7 && j == 6) || (i == 8 && j == 5) || (i == 9 && j == 4) ||
                 (i == 4 && j == 8) || (i == 5 && j == 9) ||
                 (i == 0 && j == 5) || (i == 1 && j == 6) || (i == 2 && j == 7))
        {

            printf("\033[38;5;3;48;5;19m  %4d  \033[1m", arr[i][j]);
            printf(RESET "");
        }
        else
        {
            printf("\033[38;5;7;48;5;19m  %4d  \033[2m", arr[i][j]);
            printf(RESET "");
        }
    }
    else
    {
        int pos = arr[i][j];
        if (pos == player1Pos && pos == player2Pos)
        {
            printf("\033[48;5;21m  \033[3m");
            printf("\033[38;5;7;48;5;40mP1\033[3m");
            printf("\033[38;5;7;48;5;214mP2\033[3m");
            printf("\033[48;5;21m  \033[3m" RESET);
        }
        else if (pos == player1Pos)
        {
            printf("\033[48;5;21m  \033[3m");
            printf("\033[38;5;7;48;5;40m P1 \033[3m");
            printf("\033[48;5;21m  \033[3m" RESET);
        }
        else if (pos == player2Pos)
        {
            printf("\033[48;5;21m  \033[3m");
            printf("\033[38;5;7;48;5;214m P2 \033[3m");
            printf("\033[48;5;21m  \033[3m" RESET);
        }
        else if ((i == 0 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 3) ||
                 (i == 4 && j == 0) || (i == 5 && j == 1) || (i == 6 && j == 2) ||
                 (i == 9 && j == 2) || (i == 8 && j == 3) || (i == 7 && j == 4) || (i == 6 && j == 5) ||
                 (i == 7 && j == 9) || (i == 8 && j == 9) || (i == 9 && j == 9) ||
                 (i == 3 && j == 7) || (i == 2 && j == 8) || (i == 1 && j == 9))
        {

            printf("\033[38;5;196;48;5;21m  %4d  \033[1m", arr[i][j]);
            printf(RESET "");
        }
        else if ((i == 2 && j == 0) || (i == 3 && j == 1) ||
                 (i == 3 && j == 3) || (i == 4 && j == 4) || (i == 5 && j == 5) ||
                 (i == 7 && j == 6) || (i == 8 && j == 5) || (i == 9 && j == 4) ||
                 (i == 4 && j == 8) || (i == 5 && j == 9) ||
                 (i == 0 && j == 5) || (i == 1 && j == 6) || (i == 2 && j == 7))
        {

            printf("\033[38;5;3;48;5;21m  %4d  \033[1m", arr[i][j]);
            printf(RESET "");
        }
        else
        {
            printf("\033[38;5;7;48;5;21m  %4d  \033[2m", arr[i][j]);
            printf(RESET "");
        }
    }
}

// initializing alternate pattern in 2D array
void alternatepatternfornumbers(char arr[10][10], int j, int k, int player1Pos, int player2Pos)
{
    if ((j + k) % 2 == 0) //
    {
        printnum(j, k, 1, arr, player1Pos, player2Pos);
    }

    else
    {
        printnum(j, k, 2, arr, player1Pos, player2Pos);
    }
}

// this function prints the boxes in a single row with alternate colours
void horizontal(char arr[10][10], int j, int player1Pos, int player2Pos)
// receiving arr,row number, positions of p1 and p2
{
    for (int p = 0; p < 10; p++)
    {
        hori(j, p); // this function is used to print the blank spaces with alternate colours pattern
    }
    printf("\n");
    for (int p = 0; p < 10; p++)
    {
        alternatepatternfornumbers(arr, j, p, player1Pos, player2Pos); // this function is used to decide the alternate colur pattern with numbers inside
    }
    printf("\n");
    for (int p = 0; p < 10; p++)
    {
        hori(j, p); // this function is used to print the blank spaces with alternate colours pattern
    }
}

// initializes the array arr, from 1-100 in alternate pattern
void store(char arr[10][10])
{
    int a = 1; // starting with 1

    for (int i = 9; i >= 0; i--)
    {
        if (i % 2 != 0) // if the row number is odd
        {
            for (int j = 0; j <= 9; j++) // store in first order
            {
                arr[i][j] = a;
                a++; // incrementing the value of a
            }
        }

        else
        {
            for (int j = 9; j >= 0; j--)
            {
                arr[i][j] = a; // store in reverse order
                a++;           // incrementing the value of a
            }
        }
    }
}
